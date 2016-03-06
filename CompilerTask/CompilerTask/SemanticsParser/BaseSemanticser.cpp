#include "BaseSemanticser.h"
#include <afx.h>

BaseSemanticser::BaseSemanticser()
{

}

BaseSemanticser::~BaseSemanticser()
{

}

bool BaseSemanticser::processSemanticsParser()
{
	return true;
}



eSemansticeParserEnumValue BaseSemanticser::returnSemanticserEnumValue()
{
	return eSPEV_NullParser;
}
