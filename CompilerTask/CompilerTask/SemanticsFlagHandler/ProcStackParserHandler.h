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
#include <stack>

typedef std::stack<int> ProcStack;

class ProcStackParserHandler
{
public:
	ProcStackParserHandler();
	~ProcStackParserHandler();

public:
	void clearData();

public:
	int getTopProcStackProcAddress();

	bool newProcCallAddToStack(int nProcIdAddress);

private:
	ProcStack  m_stackProcParser;   //过程分析栈
};