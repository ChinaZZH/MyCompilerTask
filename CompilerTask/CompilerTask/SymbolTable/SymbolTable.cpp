
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

// ���ű� ��û��ȥд
int SymbolTable::RecConstTbl(const std::string& szValue, int iType)
{
	return m_constInfoTable.RecConstTbl(szValue, iType);
}


