#include "BeforeAllTypeConstructSemanticser.h"
#include "SemanticsParserMgr.h"
#include "../SemanticsFlagHandler/TypeFlagHandler.h"

BeforeAllTypeConstructSemanticser::BeforeAllTypeConstructSemanticser()
{

}

BeforeAllTypeConstructSemanticser::~BeforeAllTypeConstructSemanticser()
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

eSemansticeParserTypeValue BeforeAllTypeConstructSemanticser::returnSemanticserEnumValue()
{
	return eSPEV_BeforeAllTypeConstruct;
}


bool BeforeAllTypeConstructSemanticser::processSemanticsParser()
{
	bool bProcessSemanticsResult = false;

	TypeFlagHandler& typeFlagHandler = SemanticsParserMgrInst::instance().getTypeFlagHandler();
	eTypeFlagEnumValue typeflagEnumValue = typeFlagHandler.getTopTypeFlagValue();
	switch(typeflagEnumValue)
	{
	case eTFEV_RecordTypeValue:
		this->helpProcessRecordType();
		break;

	case eTFEV_ArrayTypeValue:
	case eTFEV_FileTypeValue:
		this->helpProcessArrayType();
		break;

	case eTFEV_SetTypeValue:
	case eTFEV_ProcTypeValue:
	case eTFEV_FunctionTypeValue:
	case eTFEV_FunctionRetTypeValue:
		this->helpProcessFunctionType();
		break;

	default:
		break;
	}

	bProcessSemanticsResult = true;
	return bProcessSemanticsResult;
}


void BeforeAllTypeConstructSemanticser::helpProcessRecordType()
{

}


void BeforeAllTypeConstructSemanticser::helpProcessArrayType()
{

}


void BeforeAllTypeConstructSemanticser::helpProcessFunctionType()
{

}