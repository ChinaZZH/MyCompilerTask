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
	KeyWordMap m_mapKeywordTbl;				   //保留字表
};

typedef Singleton<KeyWordTable> KeyWordTableInst;