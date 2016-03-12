#include "VarDefineBeforeListSemanticser.h"
#include "SemanticsParserMgr.h"
#include "SemanticsEnumDef.h"


VarDefineBeforeListSemanticser::VarDefineBeforeListSemanticser()
{

}

VarDefineBeforeListSemanticser::~VarDefineBeforeListSemanticser()
{

}

// �������� (��������-->013 ��ʶ���б� 040������)
eSemansticeParserTypeValue VarDefineBeforeListSemanticser::returnSemanticserEnumValue()
{
	return eSemansticeParserTypeValue::eSPEV_VarDefineBeforeList;
}

// �������� (��������-->013 ��ʶ���б� 040������)
bool VarDefineBeforeListSemanticser::processSemanticsParser()
{
	bool bProcessSemanticser = false;
	IdentifierListFlagHandler& semanticsParserFlagStack = SemanticsParserMgrInst::instance().getIdentifierListFlagHandler();
	semanticsParserFlagStack.startNewSemanticserParserFlag(eSPIF_VarIdentifierListStart);
	
	bProcessSemanticser = true;
	return bProcessSemanticser;
}

