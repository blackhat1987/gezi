#ifndef IPYNOTATION_H
#define IPYNOTATION_H

#include <vector>
#include <string>

using namespace std;

namespace NLP
{
	namespace Pinyin
	{
		class IPYNotation
		{
			public:
           /**
			* @brief ���ض������ִʵ�       
			* @return : �Ƿ�ɹ�
			**/
			virtual bool  loadDyzDict(const char* path) = 0;
			/**
			* @brief �����������ϴʵ�       
			* @return : �Ƿ�ɹ�
			**/
			virtual bool loadDYDict(const char* path) = 0;
			/**
			* @brief ����BMEƵ�ʴʵ�       
			* @return : �Ƿ�ɹ�
			**/
			virtual bool loadBMEDict(const char* path) = 0;
			/**
			* @brief ���ش������������ִʵ�       
			* @return : �Ƿ�ɹ�
			**/
			virtual bool loadToneDyzDict(const char* path) = 0 ;
			/**
			* @brief ���ɴʵ�   
			* @oriPath[in] ���Ĵʱ���\tƴ�����������������У���ȥ�أ���������Ӣ�Ļ�ϴ����������������ң������зǷ��ַ�����������ģ��磺�ʺŵȣ���������С��CHARACTERS_MAX_LENGTH 150
			* @binaryPath[out] ���ɵĶ����ƴʵ�
			* @return : �Ƿ�ɹ�
			**/
			virtual bool generateDict(const char* oriPath,const char* binaryPath) = 0 ;
			/**
			* @brief ���شʵ�
			* @return : �Ƿ�ɹ�
			**/
			virtual bool loadDict(const char* path)= 0 ;
			/**
			* @brief ���ش������ʵ�
			* @return : �Ƿ�ɹ�
			**/
			virtual bool loadToneDict(const char* path) = 0;
			/**
			* @brief ��ȫƥ���ֵ�
			* @str[in]	������ַ���
			* @_result[out] ���ƴ����
			* @return : �Ƿ�ɹ�
			**/
			virtual bool exactToPY(const char* str,vector<string>* _result) = 0;
			/**
			* @brief ��ȫƥ��������ֵ�
			* @str[in]	������ַ���
			* @_result[out] ���ƴ����
			* @return : �Ƿ�ɹ�
			**/
			virtual bool exactToTonePY(const char* str,vector<string>* _result) = 0;
			/**
			* @brief ���ַ���ת��Ϊƴ��������ʶ����Ӣ�Ļ�ϴ���
			* @str[in]	������ַ���
			* @_result[out] ���ƴ����
			* @return : �Ƿ�ɹ�
			**/
			virtual bool convertToPY(const char* str,vector<string>* _result) = 0;
			/**
			* @brief ���ַ���ת��Ϊ��������ƴ��������ʶ����Ӣ�Ļ�ϴ���
			* @str[in]	������ַ���
			* @_result[out] ���ƴ����
			* @return : �Ƿ�ɹ�
			**/
			virtual bool convertToTonePY(const char* str,vector<string>* _result) = 0;
			/**
			* @brief ���ַ���ת��Ϊƴ��������ʶ����Ӣ�Ļ�ϴ���
			* @str[in]	��������ַ���
			* @_result[out] ���ÿ���ַ�����Ӧ��ƴ����
			* @return : �Ƿ�ȫ��ת���ɹ�����һ������false
			**/
			virtual bool convertToPY(const vector<string> strs,vector<vector<string>* >* _results) = 0;
			 /**
			* @brief �����������϶�������
			* @str[in]	������ַ���
			* @_result[out] ���ƴ����
			* @return : �Ƿ�ɹ�
			**/
			virtual bool perNameCorrection(const char*,vector<string>* _result) = 0;  
			virtual ~IPYNotation(){};
        };
	}
}

#endif

