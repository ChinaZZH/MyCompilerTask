#include "SetTypeBeforeSpecficTypeSemanticser.h"
#include "SemanticsParserMgr.h"
#include "../SymbolTable/SymbolTable.h"
#include "../Log/LogFile.h"

SetTypeBeforeSpecficTypeSemanticser::SetTypeBeforeSpecficTypeSemanticser()
{

}

SetTypeBeforeSpecficTypeSemanticser::~SetTypeBeforeSpecficTypeSemanticser()
{

}

bool SetTypeBeforeSpecficTypeSemanticser::processSemanticsParser()
{
	bool bProcessSemanticsResult = false;
	
	// ���ͽڵ����������
	TypePositionParseHandler& typeInfoPositionHandler = SemanticsParserMgrInst::instance().getTypePositionParseHandler();
	int nProcessTypeValue = typeInfoPositionHandler.getProcessingTypeAddress();

	TypeInfo* pUserTypeInfo = SymbolTableInst::instance().getTypeInfoFromTableAddress(nProcessTypeValue);
	if(NULL == pUserTypeInfo){
		LogFileInst::instance().logError("SetTypeBeforeSpecficTypeSemanticser::processSemanticsParser pUserTypeInfo null ", __FILE__, __LINE__);
		return bProcessSemanticsResult;
	}

	pUserTypeInfo->m_eDataType = eDataStoreEnumValue::eDSEV_Set;

	// ���÷�������
	TypeFlagHandler& typeFlagHandler = SemanticsParserMgrInst::instance().getTypeFlagHandler();
	typeFlagHandler.pushTypeFlagValueToStack(eTypeFlagEnumValue::eTFEV_SetTypeValue);

	bProcessSemanticsResult = true;
	return bProcessSemanticsResult;
}


eSemansticeParserTypeValue SetTypeBeforeSpecficTypeSemanticser::returnSemanticserEnumValue()
{
	return eSPEV_SetTypeBeforeSpecficType;
}
