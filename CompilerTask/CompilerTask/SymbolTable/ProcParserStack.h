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

typedef std::stack<int> ProcStack;

class ProcParserStack
{
public:
	ProcParserStack();
	~ProcParserStack();

public:
	int getTopProcStackProcAddress();

	bool newProcCallAddToStack(int nProcIdAddress);

private:
	ProcStack  m_stackProcParser;   //���̷���ջ
};