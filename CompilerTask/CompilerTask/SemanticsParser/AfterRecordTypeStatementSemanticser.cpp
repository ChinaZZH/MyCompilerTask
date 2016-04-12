#include "AfterRecordTypeStatementSemanticser.h"
#include "SemanticsParserMgr.h"

AfterRecordTypeStatementSemanticser::AfterRecordTypeStatementSemanticser()
{

}

AfterRecordTypeStatementSemanticser::~AfterRecordTypeStatementSemanticser()
{

}

bool AfterRecordTypeStatementSemanticser::processSemanticsParser()
{
	TypeFlagHandler& typeFlagHandler = SemanticsParserMgrInst::instance().getTypeFlagHandler();
	typeFlagHandler.popTypeFlagValueFromStack();

	IdentifierListFlagHandler& identifierListHandler = SemanticsParserMgrInst::instance().getIdentifierListFlagHandler();
	identifierListHandler.endSemanticserParserFlag();

	return true;
}

eSemansticeParserTypeValue AfterRecordTypeStatementSemanticser::returnSemanticserEnumValue()
{
	return eSPEV_AfterRecordTypeStatement;
}
