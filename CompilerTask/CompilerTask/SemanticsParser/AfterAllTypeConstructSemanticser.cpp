#include "AfterAllTypeConstructSemanticser.h"
#include "SemanticsParserMgr.h"
#include "../SymbolTable/SymbolTable.h"
#include "../Log/LogFile.h"

AfterAllTypeConstructSemanticser::AfterAllTypeConstructSemanticser()
{

}

AfterAllTypeConstructSemanticser::~AfterAllTypeConstructSemanticser()
{

}

/*
类型		-> 015 基本类型 010
-> 015 函数类型 010
-> 015 构造类型 010
-> 015 指针类型 010
-> 015 字符串类型 010
-> 015 标识符 023 010
*/

eSemansticeParserTypeValue AfterAllTypeConstructSemanticser::returnSemanticserEnumValue()
{
	return eSPEV_AfterAllTypeConstruct;
}


bool AfterAllTypeConstructSemanticser::processSemanticsParser()
{
	bool bProcessSemanticsResult = false;

	TypePositionParseHandler& typePositionParserHandler = SemanticsParserMgrInst::instance().getTypePositionParseHandler();
	bool bEmptyStatus = typePositionParserHandler.isEmptyStatus();
	if(true == bEmptyStatus){
		bProcessSemanticsResult = true;
		return bProcessSemanticsResult;
	}
	
	int nTypeAddressValue = typePositionParserHandler.getProcessingTypeAddress();
	if(-1 == nTypeAddressValue){
		bProcessSemanticsResult = true;
		return bProcessSemanticsResult;
	}

	TypeInfo* pTypeInfoAddress = SymbolTableInst::instance().getTypeInfoFromTableAddress(nTypeAddressValue);
	if(NULL == pTypeInfoAddress){
		LogFileInst::instance().logError("AfterAllTypeConstructSemanticser::processSemanticsParser pTypeInfoAddress null ", __FILE__, __LINE__);
		return bProcessSemanticsResult;
	}

	pTypeInfoAddress->m_nProcessState = 1;
	typePositionParserHandler.popTypeAddressData();

	bProcessSemanticsResult = true;
	return bProcessSemanticsResult;
}

