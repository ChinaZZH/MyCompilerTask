#include "OneFieldVarTypeAfterListSemanticser.h"
#include "SemanticsParserMgr.h"

OneFieldVarTypeAfterListSemanticser::OneFieldVarTypeAfterListSemanticser()
{

}

OneFieldVarTypeAfterListSemanticser::~OneFieldVarTypeAfterListSemanticser()
{

}

bool OneFieldVarTypeAfterListSemanticser::processSemanticsParser()
{
	bool bProcessResult = false;

	FieldOfRecordParserHandler& fieldOfRecordHandler = SemanticsParserMgrInst::instance().getFieldOfRecordParserHandler();
	fieldOfRecordHandler.popConstFieldStack();

	bProcessResult = true;
	return bProcessResult;
}

eSemansticeParserTypeValue OneFieldVarTypeAfterListSemanticser::returnSemanticserEnumValue()
{
	return eSemansticeParserTypeValue::eSPEV_OneFieldVarTypeAfterList;
}
