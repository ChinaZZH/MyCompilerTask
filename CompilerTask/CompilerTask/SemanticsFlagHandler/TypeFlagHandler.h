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
#include <stack>


// ���ͱ�־ ö��ֵ
enum eTypeFlagEnumValue
{
	eTFEV_MainTypeValue   = 0,
	eTFEV_RecordTypeValue = 1,  // ��¼����
	eTFEV_SetTypeValue    = 2,  // ��������
	eTFEV_ArrayTypeValue  = 3,  // ��������
	eTFEV_FileTypeValue   = 4,  // �ļ�����
	eTFEV_ProcTypeValue   = 5,  // ��������

	eTFEV_FunctionTypeValue    = 6,  // ��������
	eTFEV_FunctionRetTypeValue = 7,  // ��������ֵ����
};

typedef std::stack<int> TypeFlagStack;

class TypeFlagHandler
{
public:
	TypeFlagHandler();
	~TypeFlagHandler();

public:
	void clearData();

	void pushTypeFlagValueToStack(eTypeFlagEnumValue typeFlagEnum);

	eTypeFlagEnumValue getTopTypeFlagValue();

	eTypeFlagEnumValue popTypeFlagValueFromStack();

private:
	TypeFlagStack m_stackTypeFlag;
};

