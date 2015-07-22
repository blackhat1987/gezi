/** 
 *  ==============================================================================
 * 
 *          \file   server_frame.h
 *
 *        \author   chenghuige  
 *          
 *          \date   2012-01-12 17:17:02.226004
 *  
 *  \Description:
 *  ==============================================================================
 */

#ifndef SERVER_FRAME_H_
#define SERVER_FRAME_H_
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include "common_help.h"
#include "mcpack_server.h"
#include "ul_log_help.h"
#include "protocol.idl.h"
#include "bsl/ResourcePool.h"
#include "compack/compack.h"
#include <sstream>

namespace gezi {

using namespace compack::buffer;
const int DEFAULT_MAXLEN = 1000000;
template<typename Worker, int MAXLEN = DEFAULT_MAXLEN >
        struct SeverFunc
{
    char result[MAXLEN]; ///返回的nshead+mcpack输出结果
    Worker _worker;

    bool init()
    {
        return _worker.init();
    }
    void write_result(const char* buf, const string & result_str)
    {
        nshead_t *head = (nshead_t*) buf;
        bsl::syspool pool;
        try
        {
            char* body = result + sizeof (nshead_t);
            nshead_t *head2 = (nshead_t*) result;
            idl::Res dd(&pool);
            idl::Res* d = &dd;
            head2->magic_num = head->magic_num;
            head2->body_len = 0;
            //            Pval(result_str);
            d->set_content(result_str.c_str(), result_str.length());
            buffer buffer(body, MAXLEN - sizeof (nshead_t));
            head2->body_len = d->save(&buffer);
        }
        catch (bsl::Exception &e)
        { //会抛异常
            LOG_WARNING("idl error %s", e.all()); //输出完整的异常
        }
        catch (std::exception &e)
        {
            LOG_WARNING("idl error %s", e.what());
        }
        catch (...)
        {
            LOG_WARNING("idl error Unknow");
        }
    }
    
    char* operator()(char* buf)
    {
        MicrosecTimer timer;
        string key;
        nshead_t *head = (nshead_t*) buf;
        char* body = buf + sizeof (nshead_t);
        buffer buffer(body, head->body_len);
        bsl::syspool pool;
        try
        {
            idl::Req dd(&pool);
            idl::Req* d = &dd;
            d->load(buffer);
            key = (char *) d->key();
        }
        catch (bsl::Exception &e)
        { //会抛异常
            LOG_WARNING("bsl excetpiton idl error %s", e.all()); //输出完整的异常
        }
        catch (std::exception &e)
        {
            LOG_WARNING("std excetpion idl error %s", e.what());
        }
        catch (...)
        {
            LOG_WARNING("idl error Unknow");
        }
        if (!key.empty())
        {
            stringstream os;
            //do work here
            _worker.deal(key, os);
            write_result(buf, os.str());
        }
        return result;
    }
};

}  //----end of namespace gezi

#endif  //----end of SERVER_FRAME_H_
