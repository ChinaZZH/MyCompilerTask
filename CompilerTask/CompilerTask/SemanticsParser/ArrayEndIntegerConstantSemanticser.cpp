#include "ArrayEndIntegerConstantSemanticser.h"
#include "SemanticsParserMgr.h"
#include "../Log/LogFile.h"
#include "../Common/Structure.h"
#include "../SymbolTable/SymbolTable.h"
#include "../Common/ErrorProcess.h"

ArrayEndIntegerConstantSemanticser::ArrayEndIntegerConstantSemanticser()
{

}

ArrayEndIntegerConstantSemanticser::~ArrayEndIntegerConstantSemanticser()
{

}

bool ArrayEndIntegerConstantSemanticser::processSemanticsParser()
{
	bool bProcessResult = false;
	const CToken* pLastTokenWord = this->getTokenWordByLastWordIndex();
	if (NULL == pLastTokenWord){
		LogFileInst::instance().logError("ArrayEndIntegerConstantSemanticser::processSemanticsParser pLastTokenWord null", __FILE__, __LINE__);
		return bProcessResult;
	}

	const std::string& strLastWord = pLastTokenWord->m_szContentValue;
	int nConstDataAddressValue = atoi(strLastWord.c_str());
	if(nConstDataAddressValue < 0){
		LogFileInst::instance().logError("ArrayEndIntegerConstantSemanticser::processSemanticsParser nConstDataAddressValue error", __FILE__, __LINE__);
		return bProcessResult;
	}

	ConstInfo* pConstDataInfo = SymbolTableInst::instance().getConstDataByAddressValue(nConstDataAddressValue);
	if(NULL == pConstDataInfo){
		LogFileInst::instance().logError("ArrayEndIntegerConstantSemanticser::processSemanticsParser pConstDataInfo null", __FILE__, __LINE__);
		return bProcessResult;
	}

	
	TypeInfo* pTypeInfoAddress = this->getTypeInfoByParsingTypePosition();
	if(NULL == pTypeInfoAddress){
		LogFileInst::instance().logError("ArrayEndIntegerConstantSemanticser::processSemanticsParser pUserTypeInfo null", __FILE__, __LINE__);
		return bProcessResult;
	}

	ArrayInfoVec& vecArrayInfo = pTypeInfoAddress->m_ArrayInfo;
	int nArraySize = vecArrayInfo.size() - 1;
	ArrayInfo& arrayInfo = vecArrayInfo[nArraySize];

	const std::string& strArrayEndIndex = pConstDataInfo->m_strName;
	int nArrayEndIndex = atoi(strArrayEndIndex.c_str());
	if(nArrayEndIndex < arrayInfo.m_nStartIndexValue){
		std::string strErrorData("数组上限 小于 数组下限");
		EmitErrorFile::EmitError(strErrorData);
		return bProcessResult;
	}

	arrayInfo.m_nEndIndexValue = nArrayEndIndex;

	bProcessResult = true;
	return bProcessResult;
}


eSemansticeParserTypeValue ArrayEndIntegerConstantSemanticser::returnSemanticserEnumValue()
{
	return eSemansticeParserTypeValue::eSPEV_ArrayEndIntegerConstant;
}
