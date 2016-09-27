/** 
 *  ==============================================================================
 * 
 *          \file   ul_pack_help.h
 *
 *        \author   chenghuige  
 *          
 *          \date   2011-04-01 18:47:27.295054
 *  
 *  \Description:
 *  ==============================================================================
 */

#ifndef UL_PACK_HELP_H_
#define UL_PACK_HELP_H_

#include <stdio.h>
#include <stdlib.h>

#include "ul_net.h"
#include "ul_pack.h"
#include "ul_log.h"
#include "ul_log_help.h"

#define C_TIMEOUT 2000
#define RW_TIMEOUT 10000



/**
 * @brief 带超时的connect 与ul_net2.cpp中的ul_tcpconnecto_ms类似。
 *        详细说明参考ul_net_demo.cpp中的proxy_connect。
 *
 * @param [in] 域名或ip
 * @param [in] port端口
 * @param [in] msecs 超时时间(ms)
 * @return int 成功返回sockfd；失败返回-1。
 **/
inline int my_connect(char* host, int port, int msecs)
{
    int fd;
    struct sockaddr_in sin;
    char buf[8192];

    // param invalid
    if (host[0] == 0 || port <= 0 || port > 65535)
    {
        ul_writelog(UL_LOG_FATAL, "find invalid host %s or port %d while connecting",
                host, port);
    }

    if ((fd = ul_socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        ul_writelog(UL_LOG_FATAL, "create sockfd fail return %d when connecting to host %s",
                fd, host);
        return -1;
    }

    bzero(&sin, sizeof (sin));
    sin.sin_addr.s_addr = inet_addr(host);
    if (sin.sin_addr.s_addr == INADDR_NONE)
    { // domain
        struct hostent he, *p;
        int err, ret;
        if ((ret = ul_gethostbyname_r(host, &he, buf, sizeof (buf), &p, &err) < 0))
        {
            ul_sclose(fd);
            ul_writelog(UL_LOG_FATAL, "get host ip fail while connecting to host %s", host);
            return -1;
        }
        memcpy(&sin.sin_addr.s_addr, he.h_addr, sizeof (sin.sin_addr.s_addr));
    }

    sin.sin_family = AF_INET;
    sin.sin_port = htons(port);

    // connect
    // 函数的优点是在不成功的情况下关闭该句柄
    if (ul_connecto_sclose_ms(fd, (struct sockaddr*) &sin, sizeof (sin), msecs) < 0)
    {
        if (errno == ETIMEDOUT)
        { // timeout
            ul_writelog(UL_LOG_FATAL, "connect to host %s port %d timeout", host, port);
        }
        else
        {
            ul_writelog(UL_LOG_FATAL, "connect to host %s port %d fail", host, port);
        }
        return -1;
    }
    return fd;
}
/**
 * @brief 关闭socket并置为-1
 *
 * @param [in] sock句柄
 * @return
 **/
inline int my_close(int* sock)
{
    if (*sock > 0)
    {
        //@brief close()的包装函数，参数和返回值和close()相同
        ul_sclose(*sock);
        *sock = -1;
    }
    return 0;
}
/**
 * 登录webinfodb。协议细节请查看webinfodb使用手册。
 *
 * @param [in] webinfodb的sock句柄
 * @return 成功时返回0；失败时返回-1。
 **/
inline int login_webinfodb(int sock)
{
    int flag = -1;

    // ul_pack_init
    // @brief 分配pack空间
    ul_package* pack = ul_pack_init();
    // ul_pack_putvalue
    // @brief 向包中添加名字和值，<名字，值>对的条数不能超过50，每个名字或者值
    //		  的长度不能超过256，且名字中不能包含空格。
    ul_pack_putvalue(pack, "Sender", "Rparser");
    ul_pack_putvalue(pack, "Request", "LOGIN");

    // ul_pack_writeo_ms
    // @brief 向sock写pack，支持毫秒级超时
    flag = ul_pack_writeo_ms(sock, pack, RW_TIMEOUT);

    if (flag < 0)
    {
        // ul_pack_free
        // @brief 释放pack空间，如果使用了ul_pack_putbuf设置pack包中的body部分，
        //		  body buffer需要另外释放
        ul_pack_free(pack);
        return -1;
    }

    // ul_pack_cleanhead
    // @brief 清空pack包的头，即pack包中的名字和值
    ul_pack_cleanhead(pack);

    // ul_pack_reado_ms
    // 从指定的句柄读取pack包，支持毫秒级超时
    flag = ul_pack_reado_ms(sock, pack, RW_TIMEOUT);

    if (flag < 0)
    {
        ul_pack_free(pack);
        return -1;
    }

    flag = -1;
    for (int i = 0; i < pack->pairnum; ++i)
    {
        // 如果有 Response : OK， 则登录成功
        if (!strcmp(pack->name[i], "Response"))
        {
            if (!strcmp(pack->value[i], "OK"))
            {
                flag = 0;
            }
            break;
        }
    }

    ul_pack_free(pack);

    return flag;
}

template<typename ReadFunc>
int read_url_flow(char* host, int port, int num, ReadFunc read_url)
{
    int sock = -1;
    int flag = -1;

    if ((sock = my_connect(host, port, C_TIMEOUT)) < 0)
    {
        return 1;
    }
    else
    {
        ul_writelog(UL_LOG_TRACE, "successfully connected to host %s port %d", host, port);
    }

    ul_writelog(UL_LOG_TRACE, "Login webinfodb using RP");
    flag = login_webinfodb(sock);
    if (flag < 0)
    {
        ul_writelog(UL_LOG_FATAL, "Login webinfodb failed");
        my_close(&sock);
        return 1;
    }
    ul_writelog(UL_LOG_TRACE, "Login webinfodb success");

    flag = read_url(sock, num);
    if (flag < 0)
    {
        ul_writelog(UL_LOG_FATAL, "read url failure");
        my_close(&sock);
        return 1;
    }
    ul_writelog(UL_LOG_TRACE, "read url success");

    my_close(&sock);
    return 0;
}
template<typename Func>
int read_url(int sock, int num, Func treat_url_func)
{
    ul_package* ppack = ul_pack_init();
    int flag = -1;

    ul_pack_putvalue(ppack, "Sender", "Rparser");
    ul_pack_putvalue(ppack, "Method", "GET_BY_TIME");
    ul_pack_putvalue(ppack, "DataIDs", "TITL");
    ul_pack_putbuf(ppack, NULL, 0);

    flag = ul_pack_writeo_ms(sock, ppack, RW_TIMEOUT);
    if (flag < 0)
    {
        ul_pack_free(ppack);
        return -1;
    }

    ul_pack_cleanall(ppack);

    int body_size = 128000; // 128000为webinfodb中网页信息的最大长度
    char* body_buf = (char*) malloc(body_size * sizeof (char));
    for (int i = 0; i < num; i++)
    {
        ul_pack_putbuf(ppack, body_buf, body_size);

        flag = ul_pack_reado_ms(sock, ppack, RW_TIMEOUT);
        if (flag < 0)
        {
            ul_pack_free(ppack);
            free(body_buf);
            return -1;
        }

        printf("%s\n", body_buf);

        char ack[20];
        if (!ul_pack_getvalue(ppack, "ACK", ack) || strcmp("OK", ack))
        {
            ul_writelog(UL_LOG_WARNING, "retrieve url failure");
            ul_pack_free(ppack);
            free(body_buf);
            return -1;
        }

        char result_url[1024];
        if (ul_pack_getvalue(ppack, "Url", result_url))
        {
            treat_url_func(result_url);
        }

        if (ul_pack_getvalue(ppack, "Titlelength", result_url))
        {
            treat_url_func(result_url);
        }
        else
        {
            LOG_WARNING("Fail Titlelength");
        }


        char result_url2[10240];
         if (ul_pack_getvalue(ppack, "Content", result_url2))
        {
            treat_url_func(result_url2);
        }
        else
        {
            LOG_WARNING("Fail Contentlength");
        }

    }
    ul_pack_free(ppack);
    free(body_buf);
    return 0;
}

#endif  //----end of UL_PACK_HELP_H_
