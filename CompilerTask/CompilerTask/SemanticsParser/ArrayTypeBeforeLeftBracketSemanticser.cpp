#include "ArrayTypeBeforeLeftBracketSemanticser.h"
#include "SemanticsParserMgr.h"
#include "../SymbolTable/TypeInfoUserTable.h"
#include "../SymbolTable/SymbolTable.h"
#include "../Log/LogFile.h"

ArrayTypeBeforeLeftBracketSemanticser::ArrayTypeBeforeLeftBracketSemanticser()
{

}

ArrayTypeBeforeLeftBracketSemanticser::~ArrayTypeBeforeLeftBracketSemanticser()
{

}

bool ArrayTypeBeforeLeftBracketSemanticser::processSemanticsParser()
{
	bool bProcessParserResult = false;
	
	TypeInfo* pUserTypeInfo = getTypeInfoByParsingTypePosition();
	if(NULL == pUserTypeInfo){
		LogFileInst::instance().logError("ArrayTypeBeforeLeftBracketSemanticser::processSemanticsParser pUserTypeInfo null", __FILE__, __LINE__);
		return bProcessParserResult;
	}

	// ÉèÖÃ×´Ì¬
	pUserTypeInfo->m_eDataType = eDataStoreEnumValue::eDSEV_Array;
	
	TypeFlagHandler& typeFlagHandler = SemanticsParserMgrInst::instance().getTypeFlagHandler();
	typeFlagHandler.pushTypeFlagValueToStack(eTypeFlagEnumValue::eTFEV_ArrayTypeValue);
	
	bProcessParserResult = true;
	return bProcessParserResult;
}

eSemansticeParserTypeValue ArrayTypeBeforeLeftBracketSemanticser::returnSemanticserEnumValue()
{
	return eSemansticeParserTypeValue::eSPEV_ArrayTypeBeforeLeftBrackets;
}
