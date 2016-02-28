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
#include "../Common/Singleton.h"

struct TypeSysInfo
{
	int  m_nOpSymbol;     // ������
	int  m_nOpNumType1;   // ������1
	int  m_nOpNumType2;   // ������2
	int  m_nResultType;   // ��������ͱ���

	int  m_nConstProcessId; // ����������
	int  m_nVarProcessId;   // ����������
	int  m_nIrOpSymbol;     // IR������
	int  m_nOpNum1Convert;  // ������1������ת��
	int  m_nOpNum2Convert;  // ������2������ת��

	TypeSysInfo()
		:m_nOpSymbol(0)
		, m_nOpNumType1(0)
		, m_nOpNumType2(0)
		, m_nResultType(0)

		, m_nConstProcessId(0)
		, m_nVarProcessId(0)
		, m_nIrOpSymbol(0)
		, m_nOpNum1Convert(0)
		, m_nOpNum2Convert(0)
	{ }
};

class TypeSystemConfig
{
public:
	TypeSystemConfig();
	~TypeSystemConfig();

public:
	void initTypeSysTbl();

private:
	const static int TYPE_TABLE_FIELD_NUM = 35;
};

typedef  Singleton<TypeSystemConfig> TypeSystemConfigInst;
