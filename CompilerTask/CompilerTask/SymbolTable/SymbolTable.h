
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



class SymbolTable
{
public:
	SymbolTable();

	~SymbolTable();

public:
	int SymbolTable::RecConstTbl(const std::string& szValue, int iType);
}; 

typedef Singleton<SymbolTable> SymbolTableInst;

