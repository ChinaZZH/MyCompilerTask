#include "IdentifierDefineListSemanticser.h"
#include "SemanticsParserMgr.h"

IdentifierDefineListSemanticser::IdentifierDefineListSemanticser()
{

}

IdentifierDefineListSemanticser::~IdentifierDefineListSemanticser()
{

}

bool IdentifierDefineListSemanticser::processSemanticsParser()
{
	bool bProcessSemanticser = false;
	SemanticsParserIdFlag&  flagIdStack = SemanticsParserMgrInst::instance().getSemanticsParserIdFlag();
	eSemanticsStackIdFlag flagId = flagIdStack.getCurrentSemanticsParserId();
	switch(flagId){
	case eSPIF_VarIdentifierListStart:
		bProcessSemanticser = this->processVarIdentifierList();
		break;

	default:
		bProcessSemanticser = true;
		break;
	}
	

	return bProcessSemanticser;
}


eSemansticeParserEnumValue IdentifierDefineListSemanticser::returnSemanticserEnumValue()
{
	return eSPEV_VarIdentifierDefineList;
}


bool IdentifierDefineListSemanticser::processVarIdentifierList()
{
	bool bProcessSemanticser = false;


	bProcessSemanticser = true;
	return bProcessSemanticser;
}
