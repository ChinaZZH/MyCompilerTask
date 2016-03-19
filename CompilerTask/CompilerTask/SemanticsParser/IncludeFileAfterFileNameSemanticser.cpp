#include "IncludeFileAfterFileNameSemanticser.h"
#include "SemanticsParserMgr.h"

IncludeFileAfterFileNameSemanticser::IncludeFileAfterFileNameSemanticser()
{

}

IncludeFileAfterFileNameSemanticser::~IncludeFileAfterFileNameSemanticser()
{

}

bool IncludeFileAfterFileNameSemanticser::processSemanticsParser()
{
	bool bProcessSemanticsResult = false;

	IdentifierListFlagHandler&  flagIdStack = SemanticsParserMgrInst::instance().getIdentifierListFlagHandler();
	flagIdStack.endSemanticserParserFlag();

	bProcessSemanticsResult = true;
	return bProcessSemanticsResult;
}

eSemansticeParserTypeValue IncludeFileAfterFileNameSemanticser::returnSemanticserEnumValue()
{
	return eSPEV_IncludeFileAfterFileName;
}
