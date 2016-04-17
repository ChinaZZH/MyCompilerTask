#include "FieldVarTypeBeforeEndStatusSemanticser.h"
#include "SemanticsParserMgr.h"

FieldVarTypeBeforeEndStatusSemanticser::FieldVarTypeBeforeEndStatusSemanticser()
{

}

FieldVarTypeBeforeEndStatusSemanticser::~FieldVarTypeBeforeEndStatusSemanticser()
{

}

bool FieldVarTypeBeforeEndStatusSemanticser::processSemanticsParser()
{
	bool bProcessResult = false;

	IdentifierListFlagHandler& identifierListHandler = SemanticsParserMgrInst::instance().getIdentifierListFlagHandler();
	identifierListHandler.endSemanticserParserFlag();

	bProcessResult = true;
	return bProcessResult;
}


eSemansticeParserTypeValue FieldVarTypeBeforeEndStatusSemanticser::returnSemanticserEnumValue()
{
	return eSemansticeParserTypeValue::eSPEV_FieldVarTypeBeforeEndStatus;
}
