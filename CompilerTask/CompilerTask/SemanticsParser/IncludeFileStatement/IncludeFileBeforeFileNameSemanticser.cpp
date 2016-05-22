#include "IncludeFileBeforeFileNameSemanticser.h"
#include "../SemanticsParserMgr.h"

IncludeFileBeforeFileNameSemanticser::IncludeFileBeforeFileNameSemanticser()
{

}

IncludeFileBeforeFileNameSemanticser::~IncludeFileBeforeFileNameSemanticser()
{

}

bool IncludeFileBeforeFileNameSemanticser::processSemanticsParser()
{
	bool bProcessSemanticsResult = false;

	IdentifierListFlagHandler&  flagIdStack = SemanticsParserMgrInst::instance().getIdentifierListFlagHandler();
	flagIdStack.startNewSemanticserParserFlag(eSPIF_FileIdentifierListStart);

	bProcessSemanticsResult = true;
	return bProcessSemanticsResult;
}

eSemansticeParserTypeValue IncludeFileBeforeFileNameSemanticser::returnSemanticserEnumValue()
{
	return eSPEV_IncludeFileBeforeFileName;
}
