#include "TypeDefineSemanticser.h"

TypeDefineSemanticser::TypeDefineSemanticser()
{

}

TypeDefineSemanticser::~TypeDefineSemanticser()
{

}

// 类型定义---> 标识符 006 = 类型
bool TypeDefineSemanticser::processSemanticsParser()
{
	bool bProcessSemantics = false;
	

	bProcessSemantics = true;
	return bProcessSemantics;
}


eSemansticeParserEnumValue TypeDefineSemanticser::returnSemanticserEnumValue()
{
	return eSPEV_TypeDefineParser;
}
