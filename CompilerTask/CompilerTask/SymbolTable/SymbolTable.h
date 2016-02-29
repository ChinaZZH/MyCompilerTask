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
#include "ConstInfoTable.h"
#include "TypeSysTable.h"



class SymbolTable
{
public:
	SymbolTable();

	~SymbolTable();

public:
	void init();

	void initTypeInfoByString(const std::string& szTypeInfoString);

public:
	int recConstTbl(const std::string& szValue, int iType);

private:
	ConstInfoTable  m_constInfoTable;
	TypeSysTable    m_typeSysTable;
}; 

typedef Singleton<SymbolTable> SymbolTableInst;

