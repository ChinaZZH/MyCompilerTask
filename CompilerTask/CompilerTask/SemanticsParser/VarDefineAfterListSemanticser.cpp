#include "VarDefineAfterListSemanticser.h"
#include "SemanticsParserMgr.h"
#include "SemanticsEnumDef.h"


VarDefineAfterListSemanticser::VarDefineAfterListSemanticser()
{

}

VarDefineAfterListSemanticser::~VarDefineAfterListSemanticser()
{

}

bool VarDefineAfterListSemanticser::processSemanticsParser()
{
	bool bProcessSemanticser = false;

	// ����ջ����Ԫ��
	IdentifierListFlagHandler& semanticsParserFlagStack = SemanticsParserMgrInst::instance().getIdentifierListFlagHandler();
	semanticsParserFlagStack.endSemanticserParserFlag();

	bProcessSemanticser = true;
	return bProcessSemanticser;
}

eSemansticeParserTypeValue VarDefineAfterListSemanticser::returnSemanticserEnumValue()
{
	return eSemansticeParserTypeValue::eSPEV_VarDefineAfterList;
}
