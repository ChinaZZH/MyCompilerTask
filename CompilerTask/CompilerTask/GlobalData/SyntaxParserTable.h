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

public:
	bool checkIsCorrectProduct(int nTableRowIndex, int nTableColIndex);

	int getProductFromParserTable(int nTableRowIndex, int nTableColIndex);

	std::string getProductById(int nProductId);

private:
	bool initSyntaxParserTable();

	bool initProductTable();

	// 判断数组是否越界（行）
	bool checkRowIndexValue(int nRowIndexValue);

	// 判断数组是否越界(列）
	bool checkColIndexValue(int nColIndexValue);

private:
	int m_arrayParseTbl[g_s_ParseTableNum][g_s_ParseTableNum];
	ProductListVec m_vecStringProductList;

	const static int S_N_InvalidProduct = -1;
	const static int S_N_ParserTableRow = 99;
	const static int S_N_ParserTableCol = 100;
};

typedef  Singleton<SyntaxParserTable> SyntaxParserTableInst;