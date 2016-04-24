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

enum eSemanticsStackIdFlag
{
	eSPIF_MainProgramIdentifierListStart = 0,  // �������ײ� ��ʶ��
	eSPIF_EnumIdentifierListStart = 1, // ö�����ͱ�ʶ��
	eSPIF_RecordIdentifierListStart = 2, // ��¼���ͱ�ʶ��
	eSPIF_FieldOfRecordListStart = 3, // ��¼�����е��ֶα�ʶ��
	eSPIF_ParamOfProcListStart = 4,    // �����е��β�����
	eSPIF_ParamOfFunctionListStart = 5,    // �����е��β�����
	eSPIF_VarIdentifierListStart  = 6,   // ������ʶ��
	eSPIF_FileIdentifierListStart = 7,   // �ļ���ʶ��
};

typedef std::stack<eSemanticsStackIdFlag> SemanticserParserFlagStack;

// �﷨������ǰ��ʶ
class IdentifierListFlagHandler
{
public:
	IdentifierListFlagHandler();
	~IdentifierListFlagHandler();

public:
	void clearData();

public:
	void startNewSemanticserParserFlag(eSemanticsStackIdFlag newFlag);

	eSemanticsStackIdFlag getCurrentSemanticsParserId();

	void endSemanticserParserFlag();

private:
	SemanticserParserFlagStack m_stackSemanticserParserFlag;
};