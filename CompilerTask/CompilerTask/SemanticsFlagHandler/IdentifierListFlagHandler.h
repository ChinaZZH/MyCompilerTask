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
	eSPIF_VarIdentifierListStart  = 6,  // ������ʶ��
	eSPIF_FileIdentifierListStart = 7,  // �ļ���ʶ��
};

typedef std::stack<eSemanticsStackIdFlag> SemanticserParserFlagStack;

// �﷨������ǰ��ʶ
class IdentifierListFlagHandler
{
public:
	IdentifierListFlagHandler();
	~IdentifierListFlagHandler();

public:
	void startNewSemanticserParserFlag(eSemanticsStackIdFlag newFlag);

	eSemanticsStackIdFlag getCurrentSemanticsParserId();

	void endSemanticserParserFlag();

private:
	SemanticserParserFlagStack m_stackSemanticserParserFlag;
};