
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
	return m_constInfoTable.recConstTbl(szValue, iType);
}


int SymbolTable::searchConstInfoTable(const int nProcId, const std::string& strConstName)
{
	return m_constInfoTable.searchConstInfoTable(nProcId, strConstName);
}



ConstInfo* SymbolTable::getEmptyConstInfoByName(const std::string& strConstName)
{
	return m_constInfoTable.getEmptyConstInfoByName(strConstName);
}


int SymbolTable::searchLableInfoTable(const int nProcId, const std::string& strLableName)
{
	return m_labelInfoTable.searchLableInfoTable(nProcId, strLableName);
}

bool SymbolTable::addLabelInfo(LabelInfo newLabelInfo)
{
	return m_labelInfoTable.addLabelInfo(newLabelInfo);
}

int SymbolTable::addNewProcInfo(ProcInfo newProcInfo)
{
	return m_procInfoTable.addNewProcInfo(newProcInfo);
}

bool SymbolTable::compareToProcName(int nStackTopProcId, const std::string& strCompareValue)
{
	bool bCompareResult = false;
	ProcInfo* pProcInfoValue = m_procInfoTable.getProcInfoByIndex(nStackTopProcId);
	if(NULL == pProcInfoValue){
		return bCompareResult;
	}

	int nCompareResult = pProcInfoValue->m_strProcName.compare(strCompareValue);
	if(0 != nCompareResult){
		return bCompareResult;
	}

	bCompareResult = true;
	return bCompareResult;
}

bool SymbolTable::compareProcNameIsSame(const std::string& strCompareValu)
{
	bool bCompareNameResult = m_procInfoTable.compareProcNameIsSame(strCompareValu);
	return bCompareNameResult;
}

int SymbolTable::getProcStackTop()
{
	int nTopProcAddress = m_procParserStack.getTopProcStackProcAddress();
	return nTopProcAddress;
}


bool SymbolTable::newProcCallAddToStack(int nProcIdAddress)
{
	return m_procParserStack.newProcCallAddToStack(nProcIdAddress);
}

void SymbolTable::addNewVarToSpecficProcId(VarInfo newVarInfo)
{
	m_varInfoTable.addNewVarToSpecficProcId(newVarInfo);
}


int SymbolTable::searchVarInfoTable(int nStackTopProcId, const std::string& strCompareValue)
{
	int nVarAddressValue = m_varInfoTable.searchVarInfoTable(nStackTopProcId, strCompareValue);
	return nVarAddressValue;
}
