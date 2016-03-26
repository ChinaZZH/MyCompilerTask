#include "SetTypeAfterSpecficTypeSemanticser.h"
#include "SemanticsParserMgr.h"

SetTypeAfterSpecficTypeSemanticser::SetTypeAfterSpecficTypeSemanticser()
{

}

SetTypeAfterSpecficTypeSemanticser::~SetTypeAfterSpecficTypeSemanticser()
{

}

bool SetTypeAfterSpecficTypeSemanticser::processSemanticsParser()
{
	bool bProcessSemanticsResult = false;

	TypeFlagHandler& typeFlagHandler = SemanticsParserMgrInst::instance().getTypeFlagHandler();
	typeFlagHandler.popTypeFlagValueFromStack();

	bProcessSemanticsResult = true;
	return bProcessSemanticsResult;
}

eSemansticeParserTypeValue SetTypeAfterSpecficTypeSemanticser::returnSemanticserEnumValue()
{
	return eSPEV_SetTypeAfterSpecficType;
}
