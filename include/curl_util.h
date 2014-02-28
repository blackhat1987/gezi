/***************************************************************************
 * 
 * Copyright (c) 2013 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/



/**
 * @file include/EasyCurl.h
 * @author xiaoguangyu(com@baidu.com)
 * @date 2013/05/30 14:32:50
 * @brief 
 *  
 **/
#ifndef  __INCLUDE_CURLUTIL_H_
#define  __INCLUDE_CURLUTIL_H_
#include <string>
#include <iostream>
#include <curl/curl.h> //gcc3 has curl

#include "common_util.h"

using namespace std;

class CurlUtil
{
public:

  CurlUtil()
  {
    _curl = curl_easy_init();

  }

  ~CurlUtil()
  {
    curl_easy_cleanup(_curl);
  }

  void setTimeout(int timeout)
  {
    curl_easy_setopt(_curl, CURLOPT_TIMEOUT_MS, timeout);
  }

  struct Chunk
  {
    char *memory;
    size_t size;
  };

  static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp)
  {

    size_t realsize = size * nmemb;
    struct Chunk *mem = (struct Chunk *) userp;

    mem->memory = (char*) realloc(mem->memory, mem->size + realsize + 1);
    if (mem->memory == NULL)
    {
      /* out of memory! */
      ul_writelog(UL_LOG_WARNING, "can not malloc memory");
      exit(1);
    }

    memcpy(&(mem->memory[mem->size]), contents, realsize);
    mem->size += realsize;
    mem->memory[mem->size] = 0;

    return realsize;

  }

  char* easy_escape(const char * url)
  {
    return curl_easy_escape(_curl, url, 0);
  }

  CURLcode post(const char* url, char* data, string& resStr)
  {
    gezi::Timer timer;
    Chunk chunk;
    chunk.memory = (char*) malloc(1);
    chunk.size = 0;
    curl_easy_setopt(_curl, CURLOPT_URL, url);
    curl_easy_setopt(_curl, CURLOPT_POST, 1);
    curl_easy_setopt(_curl, CURLOPT_POSTFIELDS, data);
    curl_easy_setopt(_curl, CURLOPT_WRITEDATA, (void*) &chunk);
    curl_easy_setopt(_curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
    curl_easy_setopt(_curl, CURLOPT_NOSIGNAL, 1L);
    curl_easy_setopt(_curl, CURLOPT_FORBID_REUSE, 1);
    CURLcode res = curl_easy_perform(_curl);
    if (res != CURLE_OK)
    {
      UB_LOG_WARNING(" curl_easy_perform err[%d]", res);
    }
    else
    {
      resStr = string(chunk.memory);
      ul_writelog(UL_LOG_DEBUG, "[EasyCurl] resp: %s", resStr.c_str());
    }

    if (chunk.memory)
    {
      free(chunk.memory);
    }

    ul_writelog(UL_LOG_TRACE, "[EasyCurl]within time [%d]ms code[%d]  post[%s] [%s]", timer.elapsed_ms(), res, url, data);
    return res;
  }

	string get(const string& url)
	{
		string result;
		get(url, result);
		return result;
	}
	CURLcode get(const string& url, string& resStr)
	{
		return get(url.c_str(), resStr);
	}
  CURLcode get(const char* url, string&resStr)
  {
    //		MicrosecTimer timer;
    Chunk chunk;

    chunk.memory = (char*) malloc(1);
    chunk.size = 0;
    curl_easy_setopt(_curl, CURLOPT_URL, url);
    curl_easy_setopt(_curl, CURLOPT_WRITEDATA, (void*) &chunk);
    curl_easy_setopt(_curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
    curl_easy_setopt(_curl, CURLOPT_NOSIGNAL, 1L);
    curl_easy_setopt(_curl, CURLOPT_FORBID_REUSE, 1);
    CURLcode res = curl_easy_perform(_curl);
    if (res != CURLE_OK)
    {
      UB_LOG_WARNING(" curl_easy_perform err[%d]", res);
    }
    else
    {
      resStr = string(chunk.memory);
    }

    if (chunk.memory)
    {
      free(chunk.memory);
    }

    //ul_writelog(UL_LOG_TRACE,"[EasyCurl]  within time [%d]s code[%d] get [%s]",timer.elapsed_ms(),res,url);
    return res;
  }
private:
  CURL* _curl;

};


#endif  

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
