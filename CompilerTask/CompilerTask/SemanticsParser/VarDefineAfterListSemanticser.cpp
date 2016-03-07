#include "VarDefineAfterListSemanticser.h"

VarDefineAfterListSemanticser::VarDefineAfterListSemanticser()
{

}

VarDefineAfterListSemanticser::~VarDefineAfterListSemanticser()
{

}

bool VarDefineAfterListSemanticser::processSemanticsParser()
{
	bool bProcessSemanticser = false;

	bProcessSemanticser = true;
	return bProcessSemanticser;
}

eSemansticeParserEnumValue VarDefineAfterListSemanticser::returnSemanticserEnumValue()
{
	return eSPEV_VarDefineAfterList;
}
