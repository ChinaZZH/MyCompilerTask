#include "VarDefineBeforeListSemanticser.h"

VarDefineBeforeListSemanticser::VarDefineBeforeListSemanticser()
{

}

VarDefineBeforeListSemanticser::~VarDefineBeforeListSemanticser()
{

}

bool VarDefineBeforeListSemanticser::processSemanticsParser()
{
	bool bProcessSemanticser = false;

	bProcessSemanticser = true;
	return bProcessSemanticser;
}

eSemansticeParserEnumValue VarDefineBeforeListSemanticser::returnSemanticserEnumValue()
{
	return eSPEV_VarDefineBeforeList;
}
