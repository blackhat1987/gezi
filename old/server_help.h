/** 
 *  ==============================================================================
 * 
 *          \file   server_help.h
 *
 *        \author   chenghuige 
 *          
 *          \date   2010-04-28 16:40:53.144899
 *  
 *  \Description:
 *  ==============================================================================
 */

#ifndef SERVER_HELP_H_
#define SERVER_HELP_H_

#include "search_frame/gen_server/i_server.h"
#include "search_frame/gen_server/i_server_controller.h"
#include "search_frame/gen_server/i_data_mgr.h"
#include "search_frame/gen_server/i_server_controller_adapter.h"
#include "search_frame/gen_server/i_server_frame.h"
#include "search_frame/gen_server/t_gen_server_main.h"
#include "url_help.h"
using namespace gen_server;

class TestDataManager : public I_DataMgr
{
public:
    string data1;
    int data2;
};

class TestController : public I_ServerController
{
public:

    TestController(
                   const string& workPath,
                   const string& setting,
                   I_Server *refServer)
    : I_ServerController(workPath, setting, refServer)
    {
    }

    virtual I_DataMgr* buildDataMgr()
    {
        return new TestDataManager;
    }

    virtual bool work(const string& in, string& out)
    {
        if (in == "info")
        {
            out = "there is no info";
        }
        if (in == "update")
        {
            {
                printf("error\n");
                return false;
            }

        }

        return true;
    }
};

/**
 * 使用一个路径构造
 */
template<class _Server>
class TestServerFrame
: public I_ServerFrame
{
private:

    virtual I_Server* buildServer(
                                  IN const string& setting,
                                  IN const string& workPath)
    {
        LOG(INFO) << "setting is  " << setting << "\n";
        LOG(INFO) << "work path is " << workPath << "\n";
        string data_folder = clsGlobal::GetStringInSettingFile("DATA", "data_folder", "data", setting);
        data_folder = workPath + "/" + data_folder;
        return new _Server(data_folder);
    }

    virtual I_ServerController* buildControl(
                                             IN const string& setting,
                                             IN const string& workPath,
                                             IN I_Server*& serverRef)
    {
        return new TestController(workPath, setting, serverRef);
    }
};

/**
 * 使用两个路径构造
 */
template<class _Server>
class TestServerFrame2
: public I_ServerFrame
{
private:

    virtual I_Server* buildServer(
                                  IN const string& setting,
                                  IN const string& workPath)
    {
        LOG(INFO) << "setting is  " << setting << "\n";
        LOG(INFO) << "work path is " << workPath << "\n";
        string data_folder = clsGlobal::GetStringInSettingFile("DATA", "data_folder", "data", setting);
        data_folder = workPath + "/" + data_folder;
        string static_data_folder = clsGlobal::GetStringInSettingFile("DATA", "static_data_folder", "static_data", setting);
        static_data_folder = workPath + "/" + static_data_folder;
        return new _Server(data_folder, static_data_folder);
    }

    virtual I_ServerController* buildControl(
                                             IN const string& setting,
                                             IN const string& workPath,
                                             IN I_Server*& serverRef)
    {
        return new TestController(workPath, setting, serverRef);
    }
};
#endif  //----end of SERVER_HELP_H_
