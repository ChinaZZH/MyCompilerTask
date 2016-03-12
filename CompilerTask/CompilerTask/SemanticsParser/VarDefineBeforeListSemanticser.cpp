#include "VarDefineBeforeListSemanticser.h"
#include "SemanticsParserMgr.h"
#include "SemanticsEnumDef.h"


VarDefineBeforeListSemanticser::VarDefineBeforeListSemanticser()
{

}

VarDefineBeforeListSemanticser::~VarDefineBeforeListSemanticser()
{

}

// 变量定义 (变量定义-->013 标识符列表 040：类型)
eSemansticeParserTypeValue VarDefineBeforeListSemanticser::returnSemanticserEnumValue()
{
	return eSemansticeParserTypeValue::eSPEV_VarDefineBeforeList;
}

// 变量定义 (变量定义-->013 标识符列表 040：类型)
bool VarDefineBeforeListSemanticser::processSemanticsParser()
{
	bool bProcessSemanticser = false;
	IdentifierListFlagHandler& semanticsParserFlagStack = SemanticsParserMgrInst::instance().getIdentifierListFlagHandler();
	semanticsParserFlagStack.startNewSemanticserParserFlag(eSPIF_VarIdentifierListStart);
	
	bProcessSemanticser = true;
	return bProcessSemanticser;
}

