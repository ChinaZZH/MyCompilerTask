/********************************************************************
            Copyright (c) 2015
                   All rights reserved
         
    创建日期：  2016年 月 日 时 分
    文件名称：  
    说    明：       
    
    当前版本：  
    作    者：  郑祖煌
    概    述：      

*********************************************************************/

#pragma once
#include <string>
#include <map>
#include "CommonObjectInfo.h"
#include "../GlobalData/LexParseGlobalDataDef.h"
#include "../GlobalData/SyntaxParserGlobalDataDef.h"

// 常量信息
using namespace std;
struct ConstInfo: public CommonObjectInfo
{
	eConstantEnumValue   m_eConstBaseValue; // 常量基本类型
	eDataStoreEnumValue  m_eDataStoreValue; // 常量存储类型
	
	// 实际类型
	std::string m_strConstStringValue;
	bool m_bConstBoolValue;
	int  m_nConstIntValue;
	
	double m_dConstDoubleValue;
	long long m_lConstLongLongValue;
	std::string m_strConstSetsValue;

	int  m_nEnumTypeLinkAddr; // 枚举类型描述指针
	bool m_bUsedAlready;      // 是否已经使用过

	// 构造函数
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