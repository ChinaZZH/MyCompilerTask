#include "VarDefineBeforeListSemanticser.h"
#include "SemanticsParserMgr.h"


VarDefineBeforeListSemanticser::VarDefineBeforeListSemanticser()
{

}

VarDefineBeforeListSemanticser::~VarDefineBeforeListSemanticser()
{

}

// �������� (��������-->013 ��ʶ���б� 040������)
eSemansticeParserEnumValue VarDefineBeforeListSemanticser::returnSemanticserEnumValue()
{
	return eSPEV_VarDefineBeforeList;
}

// �������� (��������-->013 ��ʶ���б� 040������)
bool VarDefineBeforeListSemanticser::processSemanticsParser()
{
	bool bProcessSemanticser = false;
	SemanticsParserIdFlag& semanticsParserFlagStack = SemanticsParserMgrInst::instance().getSemanticsParserIdFlag();
	semanticsParserFlagStack.startNewSemanticserParserFlag(eSPIF_VarIdentifierListStart);
	
	bProcessSemanticser = true;
	return bProcessSemanticser;
}

