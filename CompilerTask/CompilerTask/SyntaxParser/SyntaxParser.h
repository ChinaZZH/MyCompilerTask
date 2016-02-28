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
#include "../Common/Singleton.h"
#include <stack>


class SyntaxParser
{
public:
	SyntaxParser();
	~SyntaxParser();

public:
	bool processSyntaxParse();

private:
	int enParserStack();

private:
	std::stack<int> m_stackSyntaxParser;
};

typedef Singleton<SyntaxParser> SyntaxParserInst;