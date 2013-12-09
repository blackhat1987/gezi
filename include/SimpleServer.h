/** 
 *  ==============================================================================
 * 
 *          \file   SimpleServer.h
 *
 *        \author   chenghuige  
 *          
 *          \date   2011-05-04
 *  
 *  \Description:  接口传递符合mcpack规则，修改query server传string的方法
 *                 TODO using ub_server?
 *  ==============================================================================
 */

#ifndef SIMPLE_SERVER_H_
#define SIMPLE_SERVER_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/wait.h>
#include <unistd.h> //fork close
#include <memory.h> //memset
#include "log_util.h"
#include "ul_net.h"
#include "nshead.h"
template<typename _Func, int MAXLEN = 204800 >
        class SimpleServer
{
private:
    int _listenfd; //存在写操作
    int _port;
    _Func& _func; //多线程不安全的。。。 因为存在result可写
    enum
    {
        OVERTIME = 100,
        LISTENQ = 5,
    };
public:
    SimpleServer(int port, _Func& func)
    : _port(port), _func(func)
    {

    }
    int init()
    {
        struct sockaddr_in saddr;

        //socket()
        if ((_listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        {
            LOG_ERROR("Error creating socket");
            return -1;
        }

        memset(&saddr, '\0', sizeof (saddr));
        saddr.sin_family = AF_INET; //match socket() call
        saddr.sin_addr.s_addr = htonl(INADDR_ANY); //bind to andy local address
        saddr.sin_port = htons(_port); //specify which port to listen

        int opt = 1;
        setsockopt(_listenfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof (opt)); //防止ctrl+c后端口还被占用
        //bind()
        if (::bind(_listenfd, (struct sockaddr *) &saddr, sizeof (saddr)) < 0)
        {
            LOG_ERROR("Error binding");
            return -1;
        }

        //listen()
        if (listen(_listenfd, LISTENQ) < 0)
        {
            LOG_ERROR("Error listening");
            return -1;
        }
        LOG_INFO("Server init sucessful");
        return 0; //成功
    }
    int process_request(int connfd)
    {
        //---------------read query
        char query[MAXLEN];
        memset(query, 0, sizeof (query));
        int ret = nshead_read(connfd, (void *) query, MAXLEN, OVERTIME);
        if (ret < 0)
        {
            LOG_WARNING("Nshead read fail error code %d", ret);
            return -1;
        }

        //----------------process query
        char* result = _func(query);

        //----------------write query
        ret = ul_send(connfd, result, sizeof (nshead_t) + ((nshead_t*) result)->body_len, 0);
        //        ret = ul_send(connfd, query, sizeof (nshead_t) + ((nshead_t*) query)->body_len, 0);
        if (ret < 0)
        {
            LOG_WARNING("Ul send fail error code %d", ret);
            return -1;
        }

        return 0;
    }
    int work()
    { //TODO 多线程，多进程?
        int connfd;
        pid_t childpid;
        socklen_t clen;
        struct sockaddr_in caddr;

        while (1)
        {
            //accept()
            clen = sizeof (caddr);
            connfd = accept(_listenfd, (struct sockaddr *) &caddr, &clen);

            if (connfd < 0)
            {
                LOG_ERROR("Error accpeting");
                return -1;
            }

            process_request(connfd);
            close(connfd); //parent close connfd
        }
        return 0;
    }
    int run()
    {
        if (init() < 0)
            return -1;
        if (work() < 0)
            return -1;
        return 0;
    }
};

#endif  //----end of SIMPLE_SERVER_H_
