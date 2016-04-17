#include "FieldVarTypeAfterTypeValueSemanticser.h"
#include "SemanticsParserMgr.h"


FieldVarTypeAfterTypeValueSemanticser::FieldVarTypeAfterTypeValueSemanticser()
{

}

FieldVarTypeAfterTypeValueSemanticser::~FieldVarTypeAfterTypeValueSemanticser()
{

}

bool FieldVarTypeAfterTypeValueSemanticser::processSemanticsParser()
{
	bool bProcessResult = false;

	IdentifierListFlagHandler& identifierListHandler = SemanticsParserMgrInst::instance().getIdentifierListFlagHandler();
	identifierListHandler.startNewSemanticserParserFlag(eSemanticsStackIdFlag::eSPIF_FieldOfRecordListStart);

	bProcessResult = true;
	return bProcessResult;
}

eSemansticeParserTypeValue FieldVarTypeAfterTypeValueSemanticser::returnSemanticserEnumValue()
{
	return eSemansticeParserTypeValue::eSPEV_FieldVarTypeAfterTypeValue;
}
