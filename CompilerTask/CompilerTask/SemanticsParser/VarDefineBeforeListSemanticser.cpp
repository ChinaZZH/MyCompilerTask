#include "VarDefineBeforeListSemanticser.h"
#include "SemanticsParserMgr.h"


VarDefineBeforeListSemanticser::VarDefineBeforeListSemanticser()
{

}

VarDefineBeforeListSemanticser::~VarDefineBeforeListSemanticser()
{

}

// 变量定义 (变量定义-->013 标识符列表 040：类型)
eSemansticeParserEnumValue VarDefineBeforeListSemanticser::returnSemanticserEnumValue()
{
	return eSPEV_VarDefineBeforeList;
}

// 变量定义 (变量定义-->013 标识符列表 040：类型)
bool VarDefineBeforeListSemanticser::processSemanticsParser()
{
	bool bProcessSemanticser = false;
	SemanticsParserIdFlag& semanticsParserFlagStack = SemanticsParserMgrInst::instance().getSemanticsParserIdFlag();
	semanticsParserFlagStack.startNewSemanticserParserFlag(eSPIF_VarIdentifierListStart);
	
	bProcessSemanticser = true;
	return bProcessSemanticser;
}

