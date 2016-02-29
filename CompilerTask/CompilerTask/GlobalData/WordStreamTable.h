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
#include <vector>
#include "../Common/Structure.h"


class WordStreamTable
{
public:
	WordStreamTable();
	~WordStreamTable();

public:
	void pushNewWordToTable(int nWordStatus, int nSymbolAddress, int nRowIndex);

	void pushNewWordToTable(int nWordStatus, std::string strContentValue, int nRowIndex);

public:
	const CToken* getWordTokenByTableIndex(int nTableIndex);

	int getMaxWordNumInTable();

private:
	bool checkWordTableIndexIsCorrect(int nIndexValue);

private:
	std::vector<CToken> m_vecWordsStreamTable;
};

typedef Singleton<WordStreamTable> WordStreamTableInst;