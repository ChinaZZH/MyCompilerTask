#include "FieldVarTypeAfterEndStatusSemanticser.h"
#include "SemanticsParserMgr.h"

FieldVarTypeAfterEndStatusSemanticser::FieldVarTypeAfterEndStatusSemanticser()
{

}

FieldVarTypeAfterEndStatusSemanticser::~FieldVarTypeAfterEndStatusSemanticser()
{

}

bool FieldVarTypeAfterEndStatusSemanticser::processSemanticsParser()
{
	bool bProcessResult = false;

	FieldOfRecordParserHandler& fieldOfRecordHandler = SemanticsParserMgrInst::instance().getFieldOfRecordParserHandler();
	fieldOfRecordHandler.popFlagFieldStack();

	bProcessResult = true;
	return bProcessResult;
}

eSemansticeParserTypeValue FieldVarTypeAfterEndStatusSemanticser::returnSemanticserEnumValue()
{
	return eSemansticeParserTypeValue::eSPEV_FieldVarTypeAfterEndStatus;
}
