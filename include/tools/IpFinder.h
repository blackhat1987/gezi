/**
 *  ==============================================================================
 *
 *          \file   tools/IpFinder.h
 *
 *        \author   chenghuige
 *
 *          \date   2014-02-21 20:22:09.229775
 *
 *  \Description:  ��ԭ����CIpFinder Ǩ�ƹ���
 * @TODO ��ǰ��ʹ���ļ�ָ�� ���ļ� �̲߳���ȫ ÿ���߳���Ҫ��������һ�� Ҳ��Ӱ���ٶ�
 *  ʵ�����ļ�����ֱ�Ӽ����ڴ�
 *  ==============================================================================
 */

#ifndef TOOLS_IPFINDER_H_
#define TOOLS_IPFINDER_H_

#include <string.h>
#include <string>
#include "common_util.h"
namespace gezi {
	class IpFinder
	{
	public:
		IpFinder()
		{
		}
		IpFinder(string file)
		{
			this->Open(file.c_str());
		}
		IpFinder(const char* pszFileName)
		{
			this->Open(pszFileName);
		}
		~IpFinder()
		{
			if (_fpIpDataFile)
				fclose(_fpIpDataFile);
		}
		const static int INDEX_LENGTH = 7;        // һ����������4�ֽڵ���ʼIP��3�ֽڵ�IP��¼ƫ�ƣ���7�ֽ�
		const static int IP_LENGTH = 4;
		const static int OFFSET_LENGTH = 3;

		enum {
			REDIRECT_MODE_1 = 0x01,    // �ض���ģʽ1 ƫ�������޵�����
			REDIRECT_MODE_2 = 0x02,    // �ض���ģʽ2 ƫ�������е�����
		};
		//����ʮ������ip��ȡ������������
		void GetAddressByIp(unsigned long ipValue, std::string& strCountry, std::string& strLocation) const
		{
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			unsigned long ulIndexOffset = this->SearchIp(ipValue);
			unsigned long ulRecordOffset = this->GetValue3(ulIndexOffset + IP_LENGTH);
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

			this->GetAddressByOffset(ulRecordOffset, strCountry, strLocation);
		}

		//����ip�ַ�����ȡ������������
		void GetAddressByIp(const char* pszIp, std::string& strCountry, std::string& strLocation) const
		{
			if (!this->IsRightIpString(pszIp)) {
				return;
			}
			this->GetAddressByIp(this->IpString2IpValue(pszIp), strCountry, strLocation);
		}

		inline void GetAddressByIp(const std::string& ip, std::string& strCountry, std::string& strLocation) const
		{
			GetAddressByIp(ip.c_str(), strCountry, strLocation);
		}
		//ͨ��ָ����ƫ��������ȡip��¼�еĹ������͵�������ƫ��������������ȡ
		//ulOffsetΪIp��¼ƫ����
		void GetAddressByOffset(unsigned long ulOffset, std::string& strCountry, std::string& strLocation) const
		{
			if (!_fpIpDataFile) {
				return;
			}

			// ��ȥ4�ֽ�Ip��ַ
			ulOffset += IP_LENGTH;
			fseek(_fpIpDataFile, ulOffset, SEEK_SET);

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			// ��ȡ�׵�ַ��ֵ
			int nVal = (fgetc(_fpIpDataFile) & 0x000000FF);
			unsigned long ulCountryOffset = 0;    // ��ʵ������ƫ��
			unsigned long ulLocationOffset = 0; // ��ʵ������ƫ��
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

			// Ϊ�˽�ʡ�ռ䣬��ͬ�ַ���ʹ���ض��򣬶����Ƕ�ݿ���
			if (REDIRECT_MODE_1 == nVal) {

				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				// �ض���1����
				unsigned long ulRedirect = this->GetValue3(ulOffset + 1); // �ض���ƫ��
				///
				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

				fseek(_fpIpDataFile, ulRedirect, SEEK_SET);

				if ((fgetc(_fpIpDataFile) & 0x000000FF) == REDIRECT_MODE_2) {

					// �������1���ض���1���ͽ���������ض���2���� 
					// 0x01 1�ֽ�
					// ƫ���� 3�ֽ� -----> 0x02 1�ֽ� 
					//                     ƫ���� 3�ֽ� -----> ������
					//                     ������
					ulCountryOffset = this->GetValue3(ulRedirect + 1);
					this->GetString(strCountry, ulCountryOffset);
					ulLocationOffset = ulRedirect + 4;
				}
				else {

					// �������ض���ģʽ1
					// 0x01 1�ֽ�
					// ƫ���� 3�ֽ� ------> ������
					//                      ������
					ulCountryOffset = ulRedirect;
					ulLocationOffset = ulRedirect + this->GetString(strCountry,
						ulCountryOffset);
				}
			}
			else if (REDIRECT_MODE_2 == nVal) {

				// �ض���2����
				// 0x02 1�ֽ�
				// ����ƫ�� 3�ֽ� -----> ������
				// ������
				ulCountryOffset = this->GetValue3(ulOffset + 1);
				this->GetString(strCountry, ulCountryOffset);

				ulLocationOffset = ulOffset + 4;
			}
			else {

				// ��򵥵���� û���ض���
				// ������
				// ������
				ulCountryOffset = ulOffset;
				ulLocationOffset = ulCountryOffset + this->GetString(strCountry,
					ulCountryOffset);
			}

			// ��ȡ����
			fseek(_fpIpDataFile, ulLocationOffset, SEEK_SET);
			if ((fgetc(_fpIpDataFile) & 0x000000FF) == REDIRECT_MODE_2
				|| (fgetc(_fpIpDataFile) & 0x000000FF) == REDIRECT_MODE_1) {

				// �������2(��ӵ����Σ�����Ҳ�ض���)
				// 0x01 1�ֽ�
				// ƫ���� 3�ֽ� ------> 0x02 1�ֽ�
				//                      ƫ���� 3�ֽ� -----> ������
				//                      0x01 or 0x02 1�ֽ�
				//                      ƫ���� 3�ֽ� ----> ������ ƫ����Ϊ0��ʾδ֪����
				ulLocationOffset = this->GetValue3(ulLocationOffset + 1);
			}

			this->GetString(strLocation, ulLocationOffset);
		}

		//��ָ��λ�û�ȡ�ַ���
		unsigned long GetString(std::string& str, unsigned long indexStart) const
		{
			if (!_fpIpDataFile) {
				return 0;
			}

			str.erase(0, str.size());

			fseek(_fpIpDataFile, indexStart, SEEK_SET);
			//~~~~~~~~~~~~~~~~~~~~~~
			int nChar = fgetc(_fpIpDataFile);
			unsigned long ulCount = 1;
			// ��ȡ�ַ�����ֱ������0x00Ϊֹ
			while (nChar != 0x00) {

				// ���η��������洢���ַ����ռ���
				str += static_cast<char>(nChar);
				++ulCount;
				nChar = fgetc(_fpIpDataFile);
			}

			// �����ַ�������
			return ulCount;
		}

		//��ָ��λ�û�ȡһ��ʮ�����Ƶ��� (��ȡ3���ֽڣ� ��Ҫ���ڻ�ȡƫ������ ��Ч�ʽ�����صĺ������������Ż���
		unsigned long GetValue3(unsigned long indexStart) const
		{
			if (!_fpIpDataFile) {
				return 0;
			}

			//~~~~~~~~~~~~~~~~~~~~
			int nVal[3];
			unsigned long ulValue = 0;
			//~~~~~~~~~~~~~~~~~~~~

			fseek(_fpIpDataFile, indexStart, SEEK_SET);
			for (int i = 0; i < 3; i++) {

				// ���˸�λ��һ�ζ�ȡһ���ַ�
				nVal[i] = fgetc(_fpIpDataFile) & 0x000000FF;
			}

			for (int j = 2; j >= 0; --j) {

				// ��Ϊ��ȡ���16�����ַ�������
				ulValue = ulValue * 0x100 + nVal[j];
			}
			return ulValue;
		}

		//��ָ��λ�û�ȡһ��ʮ�����Ƶ��� (��ȡ4���ֽڣ� ��Ҫ���ڻ�ȡIPֵ�� ��Ч�ʽ�����صĺ������������Ż���
		unsigned long GetValue4(unsigned long indexStart) const
		{
			if (!_fpIpDataFile) {
				return 0;
			}

			//~~~~~~~~~~~~~~~~~~~~
			int nVal[4];
			unsigned long ulValue = 0;
			//~~~~~~~~~~~~~~~~~~~~

			fseek(_fpIpDataFile, indexStart, SEEK_SET);
			for (int i = 0; i < 4; i++) {

				// ���˸�λ��һ�ζ�ȡһ���ַ�
				nVal[i] = fgetc(_fpIpDataFile) & 0x000000FF;
			}

			for (int j = 3; j >= 0; --j) {

				// ��Ϊ��ȡ���16�����ַ�������
				ulValue = ulValue * 0x100 + nVal[j];
			}
			return ulValue;
		}

		//ת�� ����IP��ַ�ַ���������ʮ������ֵ��4�ֽڣ�
		unsigned long IpString2IpValue(const char *pszIp) const
		{
			if (!this->IsRightIpString(pszIp)) {
				return 0;
			}
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			int nNum = 0;            // ÿ������ֵ
			const char *pBeg = pszIp;
			const char *pPos = NULL;
			unsigned long ulIp = 0; // ����IP��ֵ
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~

			pPos = strchr(pszIp, '.');
			while (pPos != NULL) {
				nNum = atoi(pBeg);
				ulIp += nNum;
				ulIp *= 0x100;
				pBeg = pPos + 1;
				pPos = strchr(pBeg, '.');
			}

			nNum = atoi(pBeg);
			ulIp += nNum;
			return ulIp;
		}

		//����ipֵ��ȡ�ַ������ɵ�ָ
		void IpValue2IpString(unsigned long ipValue, char* pszIpAddress, int nMaxCount) const
		{
			if (!pszIpAddress) {
				return;
			}

			snprintf(pszIpAddress, nMaxCount, "%d.%d.%d.%d", (ipValue & 0xFF000000) >> 24,
				(ipValue & 0x00FF0000) >> 16, (ipValue & 0x0000FF00) >> 8, ipValue & 0x000000FF);
			pszIpAddress[nMaxCount - 1] = 0;
		}
		//�жϸ���IP�ַ����Ƿ��ǺϷ���ip��ַ
		bool IsRightIpString(const char* pszIp) const
		{
			if (!pszIp) {
				return false;
			}

			int nLen = strlen(pszIp);
			if (nLen < 7) {

				// ���ٰ���7���ַ�"0.0.0.0"
				return false;
			}

			for (int i = 0; i < nLen; ++i) {
				if (!isdigit(pszIp[i]) && pszIp[i] != '.') {
					return false;
				}

				if (pszIp[i] == '.') {
					if (0 == i) {
						if (!isdigit(pszIp[i + 1])) {
							return false;
						}
					}
					else if (nLen - 1 == i) {
						if (!isdigit(pszIp[i - 1])) {
							return false;
						}
					}
					else {
						if (!isdigit(pszIp[i - 1]) || !isdigit(pszIp[i + 1])) {
							return false;
						}
					}
				}
			}
			return true;
		}

		//��ip���ݵ�����start��end�綨������Χ�� ��ͨ��SearchIp����ȡ
		unsigned long OutputData(const char* pszFileName, unsigned long indexStart = 0, unsigned long indexEnd = 0) const
		{
			if (!_fpIpDataFile || !pszFileName) {
				return 0;
			}

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			FILE *fpOut = fopen(pszFileName, "wb");
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

			if (!fpOut) {
				return 0;
			}

			if (0 == indexStart) {
				indexStart = _indexStart;
			}

			if (0 == indexEnd) {
				indexEnd = _indexEnd;
			}

			//~~~~~~~~~~~~~~~~~~~~~~~~
			char szEndIp[255];
			char szStartIp[255];
			std::string strCountry;
			std::string strLocation;
			unsigned long ulCount = 0;
			unsigned long ipValueEnd = 0;
			unsigned long ipValueStart = 0;
			//~~~~~~~~~~~~~~~~~~~~~~~~

			for (unsigned long i = indexStart; i < indexEnd; i += INDEX_LENGTH) {

				// ��ȡIP�ε���ʼIP�ͽ���IP�� ��ʼIPΪ�������ֵ�ǰ4λ16����
				// ����IP��IP��Ϣ���ֵ�ǰ4λ16�����У�����������ָ����ƫ������Ѱ
				ipValueStart = this->GetValue4(i);
				ipValueEnd = this->GetValue4(this->GetValue3(i + IP_LENGTH));

				// ����IP��Ϣ����ʽ�� ��ʼIP/t����IP/t����λ��/t����λ��/n
				this->IpValue2IpString(ipValueStart, szStartIp, sizeof(szStartIp));
				this->IpValue2IpString(ipValueEnd, szEndIp, sizeof(szEndIp));
				this->GetAddressByOffset(this->GetValue3(i + IP_LENGTH), strCountry,
					strLocation);
				fprintf(fpOut, "%s/t%s/t%s/t%s/n", szStartIp, szEndIp,
					strCountry.c_str(), strLocation.c_str());
				ulCount++;
			}

			fclose(fpOut);

			// ���ص���������
			return ulCount;
		}

		//ͨ��ipֵ�綨������Χ
		unsigned long OutputDataByIp(const char* pszFileName, unsigned long ipValueStart, unsigned long ipValueEnd) const
		{
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			unsigned long indexStart = this->SearchIp(ipValueStart);
			unsigned long indexEnd = this->SearchIp(ipValueEnd);
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

			return this->OutputData(pszFileName, indexStart, indexEnd);
		}
		unsigned long OutputDataByIp(const char* pszFileName, const char* pszStartIp, const char* pszEndIp) const;

		//����ָ��IP(ʮ������ֵ)�����������������е�λ��(����)
		//ulIndexStart��ulIndexEnd����ָ��������Χ ��Ϊ0��ʾ����ȫ��
		unsigned long SearchIp(unsigned long ipValue, unsigned long indexStart = 0, unsigned long indexEnd = 0) const
		{
			if (!_fpIpDataFile) {
				return 0;
			}

			if (0 == indexStart) {
				indexStart = _indexStart;
			}

			if (0 == indexEnd) {
				indexEnd = _indexEnd;
			}

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			unsigned long indexLeft = indexStart;
			unsigned long indexRight = indexEnd;

			// �ȳ������Ϊ�˱�֤midָ��һ��������ȷ������
			unsigned long indexMid = (indexRight - indexLeft) / INDEX_LENGTH / 2 * INDEX_LENGTH + indexLeft;

			// ��ʼIp��ַ(��172.23.0.0),����Ip��¼�е�Ip��ַ(��172.23.255.255)����һ��Ip��Χ���������Χ�ڵ�Ip��������������������ȡ���ҡ�����
			unsigned long ulIpHeader = 0;
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

			do
			{
				ulIpHeader = this->GetValue4(indexMid);
				if (ipValue < ulIpHeader) {
					indexRight = indexMid;
					indexMid = (indexRight - indexLeft) / INDEX_LENGTH / 2 * INDEX_LENGTH + indexLeft;
				}
				else {
					indexLeft = indexMid;
					indexMid = (indexRight - indexLeft) / INDEX_LENGTH / 2 * INDEX_LENGTH + indexLeft;
				}
			} while (indexLeft < indexMid);            // ע���Ǹ���mid�������ж�

			// ֻҪ���Ϸ�Χ�Ϳ��ԣ�����Ҫ��ȫ���
			return indexMid;
		}
		unsigned long SearchIp(const char* pszIp, unsigned long indexStart = 0, unsigned long indexEnd = 0) const
		{
			if (!this->IsRightIpString(pszIp)) {
				return 0;
			}
			return this->SearchIp(this->IpString2IpValue(pszIp), indexStart,
				indexEnd);
		}

		bool Open(string file)
		{
			PVAL(file);
			return Open(file.c_str());
		}

		bool Open(const char* pszFileName)
		{
			_fpIpDataFile = fopen(pszFileName, "rb");
			if (!_fpIpDataFile) {
				return false;
			}

			// IPͷ������ʮ������4�ֽ�ƫ�������ɣ��ֱ�Ϊ������ʼ������������
			_indexStart = this->GetValue4(0);
			_indexEnd = this->GetValue4(4);
			return true;
		}
	private:
		FILE *_fpIpDataFile = NULL;            // IP���ݿ��ļ�
		unsigned long _indexStart;    // ��ʼ����ƫ��
		unsigned long _indexEnd;        // ��������ƫ��
	};

}  //----end of namespace gezi

#endif  //----end of TOOLS_IPFINDER_H_
