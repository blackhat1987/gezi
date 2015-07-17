/** 
 *  ==============================================================================
 * 
 *          \file   query_server.h
 *
 *        \author   chenghuige  
 *          
 *          \date   2011-04-17 21:40:03.399956
 *  
 *  \Description:   最简单的server基于linux socket API
 *                  仅仅需要接受query
 *                  返回结果 worker计算返回一个result
 *                  query较短，但是result可能较长
 *  ==============================================================================
 */

#ifndef QUERY_SERVER_H_
#define QUERY_SERVER_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/wait.h>
#include <unistd.h> //fork close
#include <memory.h> //memset
#include "ul_log_help.h"
//template<typename _Worker, int LISTENQ = 5 >
template<typename _Func>
class QueryServer
{
private:
    int _listenfd; //存在写操作
    int _port;
    _Func& _func;
    enum
    {
        LISTENQ = 5,
        MAXLEN = 1024,
        MAXCAPICTY = 10240
    };
public:
    QueryServer(int port, _Func& func)
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

        //bind()
        if (bind(_listenfd, (struct sockaddr *) &saddr, sizeof (saddr)) < 0)
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

        return 0; //成功
    }
    int sendn(const char* buf, int to_send_len, int connfd)
    {
        int has_send_len = 0;
        while (has_send_len < to_send_len)
        {
            int send_len = send(connfd, buf + has_send_len,
                    to_send_len - has_send_len, 0);
            if (send_len < 0)
            {
                LOG_ERROR("Fail to send");
                return -1;
            }
            has_send_len += send_len;
        }
        return 0;
    }
    int process_request(int connfd)
    {
        //---------------read query
        char query[MAXLEN];
        memset(query, 0, sizeof (query));
        int recive_bytes = recv(connfd, query, MAXLEN - 1, 0);
        if (recive_bytes < 0)
            return -1;

        LOG_INFO("query: %s", query);

        //----------------process query
        std::string result = _func(query);
        Pval(result.size());

        //----------------write query
        if (sendn(result.c_str(), result.size(), connfd) < 0)
            return -1;

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
#endif  //----end of QUERY_SERVER_H_
