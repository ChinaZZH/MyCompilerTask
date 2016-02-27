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

#include <map>
#include "../Common/Singleton.h"

typedef std::map<std::string, int> KeyWordMap;

class KeyWordTable
{
public:
	KeyWordTable();

	~KeyWordTable();

public:
	void initData();

	int searchKeyWordOnTable(std::string strKeyWord) const;

private:
	void parseStringToKeyWordsTable(const std::string& strParseContent);

private:
	KeyWordMap m_mapKeywordTbl;				   //�����ֱ�
};

typedef Singleton<KeyWordTable> KeyWordTableInst;