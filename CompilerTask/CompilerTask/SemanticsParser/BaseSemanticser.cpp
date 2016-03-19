#include "BaseSemanticser.h"
#include <string>
#include "../SymbolTable/SymbolTable.h"


BaseSemanticser::BaseSemanticser()
{

}

BaseSemanticser::~BaseSemanticser()
{

}

bool BaseSemanticser::processSemanticsParser()
{
	return true;
}



eSemansticeParserTypeValue BaseSemanticser::returnSemanticserEnumValue()
{
	return eSPEV_NullParser;
}

bool BaseSemanticser::checkCompareIsSameNameWithWord(int nStackTopProcId, const std::string& strWordValue)
{
	bool bSameName = true;

	// 是否跟类型表信息表中的类型同名
	int nTypeInfoAddressValue = SymbolTableInst::instance().searchTypeInfoTable(nStackTopProcId, strWordValue);
	if (nTypeInfoAddressValue >= 0){
		return bSameName;
	}

	// 在当前函数内 是否有常量跟其变量同名(存在,则定义失败)
	int nConstAddressValue = SymbolTableInst::instance().searchConstInfoTable(nStackTopProcId, strWordValue);
	if (nConstAddressValue >= 0){
		return bSameName;
	}

	// 在当前函数内 是否有标号 跟其变量同名(存在,则定义失败)
	int nLabelAddressValue = SymbolTableInst::instance().searchLableInfoTable(nStackTopProcId, strWordValue);
	if (nLabelAddressValue >= 0){
		return bSameName;
	}

	// 在当前函数内 是否有枚举 跟其变量同名(存在,则定义失败)
	int nEnumAddressValue = SymbolTableInst::instance().searchEnumInfoTable(nStackTopProcId, strWordValue);
	if (nEnumAddressValue >= 0){
		return bSameName;
	}

	// 在当前函数内 是否有变量 跟其变量同名(存在,则定义失败)
	int nVarAddressValue = SymbolTableInst::instance().searchVarInfoTable(nStackTopProcId, strWordValue);
	if (nVarAddressValue >= 0){
		return bSameName;
	}

	// 是否跟过程同名(存在,则定义失败)
	bool bIsSameNameProc = SymbolTableInst::instance().compareProcNameIsSame(strWordValue);
	if (true == bIsSameNameProc){
		return bSameName;
	}

	bSameName = false;
	return bSameName;
}
