#include "ArrayIntegerConstantSemanticser.h"
#include "SemanticsParserMgr.h"
#include "../SymbolTable/TypeInfoUserTable.h"
#include "../Log/LogFile.h"
#include "../Common/Structure.h"
#include "../SymbolTable/SymbolTable.h"
#include "../SymbolTable/ConstInfoTable.h"

ArrayIntegerConstantSemanticser::ArrayIntegerConstantSemanticser()
{

}

ArrayIntegerConstantSemanticser::~ArrayIntegerConstantSemanticser()
{

}

bool ArrayIntegerConstantSemanticser::processSemanticsParser()
{
	bool bProcessResult = false;

	const CToken* pLastTokenWord = this->getTokenWordByLastWordIndex();
	if(NULL == pLastTokenWord){
		LogFileInst::instance().logError("ArrayIntegerConstantSemanticser::processSemanticsParser pLastTokenWord null", __FILE__, __LINE__);
		return bProcessResult;
	}

	const std::string& strLastWord = pLastTokenWord->m_szContentValue;
	int nConstDataAddressValue = atoi(strLastWord.c_str());
	if(nConstDataAddressValue < 0){
		LogFileInst::instance().logError("ArrayIntegerConstantSemanticser::processSemanticsParser nConstDataAddressValue error", __FILE__, __LINE__);
		return bProcessResult;
	}

	ConstInfo* pConstDataInfo = SymbolTableInst::instance().getConstDataByAddressValue(nConstDataAddressValue);
	if(NULL == pConstDataInfo){
		LogFileInst::instance().logError("ArrayIntegerConstantSemanticser::processSemanticsParser pConstDataInfo null", __FILE__, __LINE__);
		return bProcessResult;
	}

	const std::string& strArrayBeginIndex = pConstDataInfo->m_strName;
	int nArrayBeginIndex = atoi(strArrayBeginIndex.c_str());

	ArrayInfo newArrayInfo;
	newArrayInfo.m_nStartIndexValue = nArrayBeginIndex;

	TypeInfo* pTypeInfoAddress = this->getTypeInfoByParsingTypePosition();
	if(NULL == pTypeInfoAddress){
		LogFileInst::instance().logError("ArrayIntegerConstantSemanticser::processSemanticsParser pUserTypeInfo null", __FILE__, __LINE__);
		return bProcessResult;
	}

	pTypeInfoAddress->m_ArrayInfo.push_back(newArrayInfo);

	bProcessResult = true;
	return bProcessResult;
}


eSemansticeParserTypeValue ArrayIntegerConstantSemanticser::returnSemanticserEnumValue()
{
	return eSemansticeParserTypeValue::eSPEV_ArrayIntegerConstant;
}
