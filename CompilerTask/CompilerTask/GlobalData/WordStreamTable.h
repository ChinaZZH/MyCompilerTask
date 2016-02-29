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