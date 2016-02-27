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
#include "../Common/Singleton.h"
#include <string>

#ifndef g_s_LexStateMaxNum
#define g_s_LexStateMaxNum 50
#endif

#ifndef g_s_AsciiCharNum
#define g_s_AsciiCharNum 129
#endif



class LexStateTable
{
public:
	LexStateTable();
	~LexStateTable();

public:
	void initData();

	int  getLexStateTableRowCount() { return g_s_LexStateMaxNum; }

	int  getLexStateTableColumnCount() { return g_s_AsciiCharNum; }

	int  searchStateByInputChar(int nSpecficState, int nInputChar);

private:
	void parseInitDataToStateTable(const std::string& strInitStateData);

private:
	int  m_arrayLexStateTable[g_s_LexStateMaxNum][g_s_AsciiCharNum];
};

typedef Singleton<LexStateTable> LexStateTableInst;