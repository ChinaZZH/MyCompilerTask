
#include "SymbolTable.h"

SymbolTable::SymbolTable()
:m_constInfoTable()
{

}

SymbolTable::~SymbolTable()
{

}

void SymbolTable::init()
{
	
}

// 符号表 还没有去写
int SymbolTable::RecConstTbl(const std::string& szValue, int iType)
{
	return m_constInfoTable.RecConstTbl(szValue, iType);
}


