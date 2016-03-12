#include "BaseSemanticser.h"


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



eSemansticeParserTypeValue BaseSemanticser::returnSemanticserEnumValue()
{
	return eSPEV_NullParser;
}
