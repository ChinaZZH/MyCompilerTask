#include "TypeBeforeTypeConstructSemanticser.h"

TypeBeforeTypeConstructSemanticser::TypeBeforeTypeConstructSemanticser()
{

}

TypeBeforeTypeConstructSemanticser::~TypeBeforeTypeConstructSemanticser()
{

}

/*
����		-> 015 �������� 010
-> 015 �������� 010
-> 015 �������� 010
-> 015 ָ������ 010
-> 015 �ַ������� 010
-> 015 ��ʶ�� 023 010
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

