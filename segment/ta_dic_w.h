#ifndef TA_DIC_W_NEW_H
#define TA_DIC_W_NEW_H

#include "dic_common.h"
#include "ini_config.h"

namespace segment
{


	//***********�ִ��Զ�����********************//
	class CDic_w
	{

	public:
		CDic_w(void);
		~CDic_w(void);
		void ClearData();

	public:
		//Entrances
		bool AmbKeyFilter(const VEC_PAIR_STR_INT&, const std::string&, const std::string&);//���崮����
		bool CreateLexIdx(const VEC_PAIR_STR_INT&, const VEC_STR&);		//�½��ʵ�����
		bool Load(const std::string&, const std::string&);			//���شʵ�����
		bool OmniSegment(const char*, const char*, std::vector<Term>&, char *buff, int);//ȫ�з�
		bool MaxSegment(const char*, const char*, std::vector<Term>&, char *buff, int);	//����з�
		bool MinSegment(const char*, const char*, std::vector<Term>&, char *buff, int);	//��С�з�		
		void WordSegment(const char*, const char*, std::vector<Term>&);	//�����з�
		void MaxSegment(const char *, const char*, std::vector<Term>&);

	private:
		void BuildTrie(const std::vector<TERM_CODE>&);//����Trie��
		bool BuildDATrie();			//����˫����������
		bool GetKeyCode(std::vector<short>&, const PAIR_STR_INT&); //��ȡ�ʵ�ʵ����루����
		bool LoadChineseTable(); 	//������ӳ�������
		bool LoadLexicon(const PAIR_STR_INT& lexicon, MAP_STR_INT& mKey2W); //���ش����ļ�
		bool NormalizeCHKey(std::string&);	//���������׼��
		bool NormalizeEnKey(std::string&);	//�Ǻ��������׼��
		char* NormalizeString(char*); //�ַ���Сд�������ּ��廯����ǻ�����	
		void SegHalfWidth(int, short[], int, int, std::vector<Term>&, int);	//���ֽڴ��з�		
		void SegMaxCH(int, short [], int, int, std::vector<Term>&);				//���ﴮ����з�
		void SegMinCH(int, short [], int, int, std::vector<Term>&);				//���ﴮ��С�з�
		void SegOmniCH(int, short[], int, int, std::vector<Term>&);				//���ﴮȫ�з�
		
		inline short GetCHCode(unsigned char, unsigned char);	//��ȡ���ֵ����루��ѯ��
		inline short GetENCode(char);												//��ȡ�Ǻ��ֵ����루��ѯ��
		inline bool IsGB2312(unsigned char, unsigned char); //�ж��ֽ��Ƿ�Ϊgb2312����
		inline bool IsGBKCH(unsigned char, unsigned char); //�ж��ֽ��Ƿ�Ϊgbk����
		inline bool SegBoundCheck(short, short); 						//��Ǵʱ߽���
		inline void SegByPunc(int, short[], short, short, std::vector<Term>&, bool); //����ַ��з�
		inline bool SegInside(int, const short [], short, short, std::vector<Term>&);	//�������зּ��
		
	private:
		//***********˫������λ���************
		//������������Ϊ8000������λ��95��ascii����λ[32-126]��1-6768λΪGB2312���֣�����1232��λΪ��չ������λ����
		//ǰ6768λ��GB2312����ӳ����ټ�1��Ϊ��ţ���1232λ��hash�洢���룬������+6769Ϊ��ţ����hash����ļ�
		//���崮�з���Ϣ��int��С�Ķ���������¼�������ֽ�Ϊ0�������ֽ�Ϊ�з���Ϣ
		
		static const short AMBOFFSET = 16;					//���崮�зִ洢ƫ��
		static const short FRST_OFFSET = 8095;			//�������򳤶�
		static const short FRST_OFFSET_CH = 8000;		//���ֲ����������򳤶�
		static const short GB2312_OFFSET = 6768;		//GB2312���򳤶�
		static const short KEYCNTMAX = 8;						//������������ɴ�������ȼ���ƥ�䣩
		static const int KEYTYPEBIT = 0xffff;				//���崮�зֵ��ֽ���Ϣλ
		static const short WORDCNTMAX_CH = 15;			//���������ֳ�
		static const short WORDCNTMAX_EN = 30;			//�Ǻ��������ֳ�
		static const short WORDCNTMAX = 
			WORDCNTMAX_CH > WORDCNTMAX_EN ? WORDCNTMAX_CH : WORDCNTMAX_EN;	//����Trie��
                static const short SHOUTIBAOENCODE = 0x7fff; //"�����"���͵���崮����
	private:		
		enum lex_type{ambiguity, common, special, english}; //�ʵ����ͣ�����/����/��ר/Ӣר
		enum seg_type{omniSeg, maxSeg, minSeg};	//�з�����
	
		//Double-Array Trie
		VEC_INT m_viBase;			//ֱ���ӽ��ת�������Ƿ�ɴ�
		VEC_INT m_viCheck;		//ǰ������š��Ƿ�Ϊ���崮
		VEC_INT m_viWeight;		//ǰ���ֽڴ�����崮�з֡������ֽڴ�Ŵʵ�Ȩ�ر�ʶ
		std::vector<std::vector<TRIE_NODE>* > Trie;		//Trie��
		hash_map<std::string, std::string> hmChinese;	//�����庺��ӳ��
		hash_map<unsigned short, short> hmCode2Idx;		//GBK��չ������ӳ��
	};
}
#endif
