#include "BeforeRecordTypeStatementSemanticser.h"
#include "SemanticsParserMgr.h"
#include "../Log/LogFile.h"
#include "../SymbolTable/SymbolTable.h"

BeforeRecordTypeStatementSemanticser::BeforeRecordTypeStatementSemanticser()
{

}

BeforeRecordTypeStatementSemanticser::~BeforeRecordTypeStatementSemanticser()
{

}

bool BeforeRecordTypeStatementSemanticser::processSemanticsParser()
{
	bool bProcessSemanticsResult = false;

	TypeInfo* pTypeInfoAddress = this->getTypeInfoByParsingTypePosition();
	if(NULL == pTypeInfoAddress){
		LogFileInst::instance().logError("BeforeRecordTypeStatementSemanticser::processSemanticsParser pTypeInfoValue null ", __FILE__, __LINE__);
		return bProcessSemanticsResult;
	}

	// ���ü�¼������
	pTypeInfoAddress->m_eDataType = eDataStoreEnumValue::eDSEV_Record;

	// ���ñ�־״̬
	TypeFlagHandler& typeFlagHandler = SemanticsParserMgrInst::instance().getTypeFlagHandler();
	typeFlagHandler.pushTypeFlagValueToStack(eTypeFlagEnumValue::eTFEV_RecordTypeValue);

	IdentifierListFlagHandler& identifierListHandler = SemanticsParserMgrInst::instance().getIdentifierListFlagHandler();
	identifierListHandler.startNewSemanticserParserFlag(eSemanticsStackIdFlag::eSPIF_RecordIdentifierListStart);

	bProcessSemanticsResult = true;
	return bProcessSemanticsResult;
}


eSemansticeParserTypeValue BeforeRecordTypeStatementSemanticser::returnSemanticserEnumValue()
{
	return eSPEV_BeforeRecordTypeStatement;
}
