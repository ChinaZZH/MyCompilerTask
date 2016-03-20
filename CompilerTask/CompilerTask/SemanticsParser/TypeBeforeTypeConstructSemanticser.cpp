#include "TypeBeforeTypeConstructSemanticser.h"

TypeBeforeTypeConstructSemanticser::TypeBeforeTypeConstructSemanticser()
{

}

TypeBeforeTypeConstructSemanticser::~TypeBeforeTypeConstructSemanticser()
{

}

/*
类型		-> 015 基本类型 010
-> 015 函数类型 010
-> 015 构造类型 010
-> 015 指针类型 010
-> 015 字符串类型 010
-> 015 标识符 023 010
*/

eSemansticeParserTypeValue TypeBeforeTypeConstructSemanticser::returnSemanticserEnumValue()
{
	return eSPEV_TypeBeforeTypeConstruct;
}


bool TypeBeforeTypeConstructSemanticser::processSemanticsParser()
{
	bool bProcessSemanticsResult = false;


	bProcessSemanticsResult = true;
	return bProcessSemanticsResult;
}

