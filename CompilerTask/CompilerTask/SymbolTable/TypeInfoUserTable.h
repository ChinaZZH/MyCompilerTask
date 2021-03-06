/********************************************************************
            Copyright (c) 2015
                   All rights reserved
         
    创建日期：  2015年 月 日 时 分
    文件名称：  
    说    明：       
    
    当前版本：  
    作    者：  郑祖煌
    概    述：      

*********************************************************************/

#pragma once
#include <map>
#include <vector>
#include <string>
#include "CommonObjectInfo.h"
#include "../GlobalData/SyntaxParserGlobalDataDef.h"


struct FieldInfo: CommonObjectInfo
{
	int  m_nAddressLink;
	int  m_nSize;

	std::string  m_strVarFieldFlag;
	std::string  m_strVarFieldConst;

	int  m_nProcessState;
	int  m_nOffsetPosition;

	FieldInfo()
		:CommonObjectInfo()
		, m_nAddressLink(-1)
		, m_nSize(0)
		, m_strVarFieldFlag("")
		, m_strVarFieldConst("")
		, m_nProcessState(0)
		, m_nOffsetPosition(0)
	{ }
};

struct ArrayInfo
{
	int  m_nStartIndexValue;
	int  m_nEndIndexValue;

	ArrayInfo()
		:m_nStartIndexValue(-1)
		, m_nEndIndexValue(-1)
	{ }
};

typedef std::vector<FieldInfo> FieldInfoVec;
typedef std::vector<ArrayInfo> ArrayInfoVec;

struct TypeInfo :CommonObjectInfo
{
	eDataStoreEnumValue m_eDataType;	  //数据类型
	int m_nAddressLink;					  //复杂类型指针
	FieldInfoVec m_FieldInfo;	          //记录类型字段域
	ArrayInfoVec m_ArrayInfo;	          //数组类型的维度域
	eDataStoreEnumValue m_eBaseType;	  //基本类型
	std::string m_strContentValue;		  //备注
	int m_nProcessState;				  //处理状态
	int m_nsSize;                         //长度

	TypeInfo()
		:CommonObjectInfo()
		, m_eDataType(eDSEV_Null)
		, m_nAddressLink(-1)
		, m_eBaseType(eDSEV_Null)
		, m_strContentValue("")
		, m_nProcessState(0)
		, m_nsSize(0)
	{  }

	void nullLinkAddressValue()
	{
		m_nAddressLink = -1;
	}
};

typedef std::map<int, TypeInfo> TypeInfoMap;			//类型信息表

class TypeInfoUserTable
{
public:
	TypeInfoUserTable();
	~TypeInfoUserTable();

public:
	int searchTypeInfoTable(int nStackTopProcId, const std::string& strCompareValue);

	int addNewUserTypeInfoToTable(TypeInfo newUserTypeInfo);

	TypeInfo* getTypeInfoFromTableAddress(int nTypeAddressValue);

	int getTopTypeUserInfoAddress();

private:
	TypeInfoMap  m_mapTypeUserInfoTable;
};