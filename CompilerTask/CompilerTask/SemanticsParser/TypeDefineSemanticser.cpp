#include "TypeDefineSemanticser.h"

TypeDefineSemanticser::TypeDefineSemanticser()
{

}

TypeDefineSemanticser::~TypeDefineSemanticser()
{

}

// ���Ͷ���---> ��ʶ�� 006 = ����
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
