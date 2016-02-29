
#include "SymbolTable.h"
#include "../GlobalData/TypeSystemConfig.h"

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

void SymbolTable::initTypeInfoByString(const std::string& szTypeInfoString)
{
	TypeSysInfo tempTypeSysInfo;
	tempTypeSysInfo.m_nOpSymbol = atoi(szTypeInfoString.substr(1, 2).c_str());
	tempTypeSysInfo.m_nOpNumType1 = atoi(szTypeInfoString.substr(4, 2).c_str());
	tempTypeSysInfo.m_nOpNumType2 = atoi(szTypeInfoString.substr(7, 2).c_str());
	tempTypeSysInfo.m_nResultType = atoi(szTypeInfoString.substr(10, 2).c_str());

	tempTypeSysInfo.m_nVarProcessId = atoi(szTypeInfoString.substr(13, 4).c_str());
	tempTypeSysInfo.m_nConstProcessId = atoi(szTypeInfoString.substr(18, 4).c_str());
	tempTypeSysInfo.m_nIrOpSymbol = atoi(szTypeInfoString.substr(23, 3).c_str());

	tempTypeSysInfo.m_nOpNum1Convert = atoi(szTypeInfoString.substr(27, 3).c_str());
	tempTypeSysInfo.m_nOpNum2Convert = atoi(szTypeInfoString.substr(31, 3).c_str());

	// 放入类型系统表中
	m_typeSysTable.addNewTypeSysUnit(tempTypeSysInfo);
}


// 符号表 还没有去写
int SymbolTable::recConstTbl(const std::string& szValue, int iType)
{
	return m_constInfoTable.RecConstTbl(szValue, iType);
}


