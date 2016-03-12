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
		, m_strVarFieldFlag(0)
		, m_strVarFieldConst(0)
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

struct TypeInfo :CommonObjectInfo
{
	eDataStoreEnumValue m_eDataType;	  //��������
	int m_nAddressLink;					  //��������ָ��
	std::vector<FieldInfo> m_FieldInfo;	  //��¼�����ֶ���
	std::vector<ArrayInfo> m_ArrayInfo;	  //�������͵�ά����
	eDataStoreEnumValue m_eBaseType;	  //��������
	std::string m_strContentValue;		  //��ע
	int m_nProcessState;				  //����״̬
	int m_nsSize;                         //����

	TypeInfo()
		:CommonObjectInfo()
		, m_eDataType(eDSEV_Null)
		, m_nAddressLink(-1)
		, m_eBaseType(eDSEV_Null)
		, m_strContentValue(0)
		, m_nProcessState(0)
		, m_nsSize(0)
	{  }

	void nullLinkAddressValue()
	{
		m_nAddressLink = -1;
	}
};

typedef std::map<int, TypeInfo> TypeInfoMap;			//������Ϣ��

class TypeInfoUserTable
{
public:
	TypeInfoUserTable();
	~TypeInfoUserTable();

public:
	int searchTypeInfoTable(int nStackTopProcId, const std::string& strCompareValue);

	int addNewUserTypeInfoToTable(TypeInfo newUserTypeInfo);

private:
	TypeInfoMap  m_mapTypeUserInfoTable;
};