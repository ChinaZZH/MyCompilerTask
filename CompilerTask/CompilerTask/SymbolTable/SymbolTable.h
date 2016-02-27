
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



class SymbolTable
{
public:
	SymbolTable();

	~SymbolTable();

public:
	int SymbolTable::RecConstTbl(const std::string& szValue, int iType);
}; 

typedef Singleton<SymbolTable> SymbolTableInst;

