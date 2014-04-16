/**
 *  ==============================================================================
 *
 *          \file   word_seg.h
 *
 *        \author   chenghuige
 *
 *          \date   2013-11-03 19:04:42.478788
 *
 *  \Description:  @TODO ���Ƿ��� Ŀǰ������� �Ƽ�ʹ�� SharedSegmentor::Instance()->segment
 *  ==============================================================================
 */

#ifndef WORD_SEG_H_
#define WORD_SEG_H_
#include <string> 
#include <vector>
#include "isegment.h"
#include "Segmentor.h"
namespace gezi
{
	using std::string;
	using std::vector;

//���̳߳�ʼ
bool seg_init(string dict_dir = "./data/wordseg", int type = 0,
				string conf_path = "./conf/scw.conf");

//���̵߳ĳ�ʼ��
bool seg_init2(string dict_dir = "./data/wordseg", int type = 0,
	string conf_path = "./conf/scw.conf");

//�̰߳�ȫ
bool segment(string input, SegHandle& handle, int type = SCW_OUT_WPCOMP);

//���� ��Ҫ����
SegHandle segment_(string input, int type = SCW_OUT_WPCOMP);

bool segment(string input, vector<string>& result, SegHandle& handle, int type = SCW_OUT_WPCOMP);

//��ݽӿ� �̰߳�ȫ
bool segment(string input, vector<string>& result, int type = SCW_OUT_WPCOMP);

vector<string> segment(string input, int type = SCW_OUT_WPCOMP);

string segment(string input, string sep, int type = SCW_OUT_WPCOMP);

//������������ݵķ�ʽ Ĭ�ϵ��̷߳�ʽ Ҳ���Ǹ����ⲿһ�����ÿռ�handle ��֤���߳��ٶ� 
bool segment2(string input, vector<string>& result, int type = SCW_OUT_WPCOMP);

vector<string> segment2(string input, int type = SCW_OUT_WPCOMP);

string segment2(string input, string sep, int type = SCW_OUT_WPCOMP);

void seg_set_bufsize(int max_len);

}

#endif  //----end of WORD_SEG_H_
