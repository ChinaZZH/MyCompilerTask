/********************************************************************
            Copyright (c) 2015
                   All rights reserved
         
    �������ڣ�  2016�� �� �� ʱ ��
    �ļ����ƣ�  
    ˵    ����       
    
    ��ǰ�汾��  
    ��    �ߣ�  ֣���
    ��    ����      

*********************************************************************/

#pragma once
#include <string>
#include <map>
#include "CommonObjectInfo.h"
#include "../GlobalData/LexParseGlobalDataDef.h"
#include "../GlobalData/SyntaxParserGlobalDataDef.h"

// ������Ϣ
using namespace std;
struct ConstInfo: public CommonObjectInfo
{
	eConstantEnumValue   m_eConstBaseValue; // ������������
	eDataStoreEnumValue  m_eDataStoreValue; // �����洢����
	
	// ʵ������
	std::string m_strConstStringValue;
	bool m_bConstBoolValue;
	int  m_nConstIntValue;
	
	double m_dConstDoubleValue;
	long long m_lConstLongLongValue;
	std::string m_strConstSetsValue;

	int  m_nEnumTypeLinkAddr; // ö����������ָ��
	bool m_bUsedAlready;      // �Ƿ��Ѿ�ʹ�ù�

	// ���캯��
	ConstInfo();
};


typedef std::map<int, ConstInfo> ConstInfoMap;

class ConstInfoTable
{
public:
	ConstInfoTable();
	~ConstInfoTable();

public:
	int recConstTbl(const std::string& szValue, int iType);

	int searchConstInfoTable(const int nProcId, const std::string& strConstName);

	ConstInfo* getEmptyConstInfoByName(const std::string& strConstName);

	ConstInfo* getConstDataByAddressValue(int nAddressValue);

public:
	ConstInfoMap  m_mapConstInfoTable;

};