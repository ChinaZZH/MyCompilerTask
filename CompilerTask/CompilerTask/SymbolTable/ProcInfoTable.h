/********************************************************************
            Copyright (c) 2015
                   All rights reserved
         
    �������ڣ�  2015�� �� �� ʱ ��
    �ļ����ƣ�  
    ˵    ����       
    
    ��ǰ�汾��  
    ��    �ߣ�  ֣���
    ��    ����      

*********************************************************************/

#pragma once
#include <string>
#include <vector>
#include <set>

// �����б�ṹ��
struct ParaInfo
{
	std::string m_strParamName;  // �β���
	int  m_nParamType;           // �β����� 
	int  m_nParamValueAddress;   // �β���ָ��ĵ�ַ

	enum AssignType{NULLVALUE, VAL, VAR} m_eAssignType; // ��ֵ  ������

	// ���캯��
	ParaInfo()
		:m_strParamName(0)
		, m_nParamType(0)
		, m_nParamValueAddress(0)
		, m_eAssignType(NULLVALUE)
	{ }
};

struct IRCode
{
	// ��ʱ��ʵ��
};

struct ProcInfo
{
	std::string m_strProcName;           // ������   
	enum Rank{ Main, Sub } m_eRankValue; // ������ ���� �Ӻ���
	enum Type{ Procedure, Function, Type } m_eType;  // ��������(1.����  2.���� 3.����ָ��)
	
	std::vector<ParaInfo> m_ParaTable;  // �β��б�
	int  m_nReturnType;                 // ����ֵ���� 
	int  m_nReturnValueAddres;          // ����ֵ��ָ��ĵ�ַ

	enum Flag { Forward, Extern, None } m_eFlag;
	int  m_nExternStrValue;
	int  m_nProcDefToken;

	enum CallType{NoneCall, Stdcall, Fastcall} m_eCallType;
	std::vector<IRCode> m_vecIrCodeList;          // ���ɵĴ������б�
	std::set<int>  m_setTmpMemShareList;          // �ɹ���洢������ʱ�����ļ���
	
	int  m_nValSize;         // ��ؾֲ������Ŀռ��С
	int  m_nTmpLinkAddress;  // ��ʱ������ָ��
	bool m_bUsed;            // �� ����/���� �Ƿ��ѱ�ʹ��
	bool m_bTmpUsed;         // �Ƿ�ʹ���� ��ʱ����

	// ���캯��
	ProcInfo()
		:m_strProcName(0)
		, m_eRankValue(Main)
		, m_eType(Procedure)
		, m_nReturnType(0)
		, m_nReturnValueAddres(0)

		, m_eFlag(None)
		, m_nExternStrValue(0)
		, m_nProcDefToken(0)
		, m_eCallType(NoneCall)
		, m_nValSize(0)
		, m_nTmpLinkAddress(0)
		, m_bUsed(false)
		, m_bTmpUsed(false)
	{  }
};


class ProcInfoTable
{
public:
	ProcInfoTable();
	~ProcInfoTable();

private:
	std::vector<ProcInfo> m_vecProcInfoTbl;			//������Ϣ��
};