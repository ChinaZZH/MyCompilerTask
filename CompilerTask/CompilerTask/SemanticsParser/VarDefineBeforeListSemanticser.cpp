#include "VarDefineBeforeListSemanticser.h"
#include "SemanticsParserMgr.h"
#include "SemanticsEnumDef.h"

VarDefineBeforeListSemanticser::VarDefineBeforeListSemanticser()
{

}

VarDefineBeforeListSemanticser::~VarDefineBeforeListSemanticser()
{

}

bool VarDefineBeforeListSemanticser::processSemanticsParser()
{
	bool bProcessSemanticser = false;
	SemanticsParserIdFlag& semanticsParserFlagStack = SemanticsParserMgrInst::instance().getSemanticsParserIdFlag();
	semanticsParserFlagStack.startNewSemanticserParserFlag(eSPIF_VarIdentifierListStart);
	bProcessSemanticser = true;
	return bProcessSemanticser;
}

eSemansticeParserEnumValue VarDefineBeforeListSemanticser::returnSemanticserEnumValue()
{
	return eSPEV_VarDefineBeforeList;
}
