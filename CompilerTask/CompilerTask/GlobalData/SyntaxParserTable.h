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
#include <vector>
#include <string>
#include "../Common/Singleton.h"

#ifndef g_s_ParseTableNum 120
#define g_s_ParseTableNum 120
#endif

typedef std::vector<std::string> ProductListVec;

class SyntaxParserTable
{
public:
	SyntaxParserTable();
	~SyntaxParserTable();

public:
	void init();

private:
	bool initSyntaxParserTable();

	bool initProductTable();

private:
	int m_arrayParseTbl[g_s_ParseTableNum][g_s_ParseTableNum];
	ProductListVec m_vecStringProductList;

	const static int S_N_ParserTableRow = 99;
	const static int S_N_ParserTableCol = 100;
};

typedef  Singleton<SyntaxParserTable> SyntaxParserTableInst;