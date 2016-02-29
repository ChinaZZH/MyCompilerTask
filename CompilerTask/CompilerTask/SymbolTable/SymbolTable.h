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

