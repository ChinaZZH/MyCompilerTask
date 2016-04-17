#include "BeforeAllTypeConstructSemanticser.h"
#include "SemanticsParserMgr.h"
#include "../SemanticsFlagHandler/TypeFlagHandler.h"
#include "../SymbolTable/SymbolTable.h"
#include "../Common/IntStringConverter.h"
#include "../Log/LogFile.h"

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
	// ������Ҫ����������
	TypeInfo* pTypeInfoAddress = this->getTypeInfoByParsingTypePosition();
	if(NULL == pTypeInfoAddress){
		LogFileInst::instance().logError("BeforeAllTypeConstructSemanticser::helpProcessRecordType pUserTypeInfo null", __FILE__, __LINE__);
		return ;
	}

	// ����µ����͵�������Ϣ����
	ProcStackParserHandler& procParserHandler = SemanticsParserMgrInst::instance().getProcStackParserHandler();
	int nTopProcAddress = procParserHandler.getTopProcStackProcAddress();

	int nSerialIdValue = SymbolTableInst::instance().getSerialId();
	std::string strSerialValue = IntStringConverter::intValueConvertToString(nSerialIdValue);
	std::string strInitTypeName("_noname");
	strInitTypeName.append(strSerialValue);

	int nUserTypeAddressValue = SymbolTableInst::instance().addNewUserTypeInfoToTable(strInitTypeName, nTopProcAddress);
	TypePositionParseHandler& typePosHandler = SemanticsParserMgrInst::instance().getTypePositionParseHandler();
	typePosHandler.addProcessingTypeInfoAddress(nUserTypeAddressValue);
	

	// ���ü�¼�����ֶ����ֵ
	int nNewProcessAddress = typePosHandler.getProcessingTypeAddress();
	int nTotalFieldNum = pTypeInfoAddress->m_FieldInfo.size();
	for(int i = 0; i < nTotalFieldNum; ++i){
		if(0 == (pTypeInfoAddress->m_FieldInfo[i].m_nProcessState)){
			continue;
		}

		pTypeInfoAddress->m_FieldInfo[i].m_nAddressLink = nNewProcessAddress;
		pTypeInfoAddress->m_FieldInfo[i].m_nProcessState = 1;
	}
}


void BeforeAllTypeConstructSemanticser::helpProcessArrayType()
{
	ProcStackParserHandler& procParserHandler = SemanticsParserMgrInst::instance().getProcStackParserHandler();
	int nTopProcAddress = procParserHandler.getTopProcStackProcAddress();

	// ��ʼ��������
	int nSerialIdValue = SymbolTableInst::instance().getSerialId();
	std::string strSerialValue = IntStringConverter::intValueConvertToString(nSerialIdValue);
	std::string strInitTypeName("_noname");
	strInitTypeName.append(strSerialValue);

	
	TypeInfo* pTypeInfoUser = this->getTypeInfoByParsingTypePosition();
	if(NULL == pTypeInfoUser){
		LogFileInst::instance().logError("BeforeAllTypeConstructSemanticser::helpProcessArrayType pUserTypeInfo null", __FILE__, __LINE__);
		return;
	}

	int nUserTypeAddressValue = SymbolTableInst::instance().addNewUserTypeInfoToTable(strInitTypeName, nTopProcAddress);
	pTypeInfoUser->m_nAddressLink = nUserTypeAddressValue;

	TypePositionParseHandler& typePosHandler = SemanticsParserMgrInst::instance().getTypePositionParseHandler();
	typePosHandler.addProcessingTypeInfoAddress(nUserTypeAddressValue);
}


void BeforeAllTypeConstructSemanticser::helpProcessFunctionType()
{
	int nTopUserTypeAddress = SymbolTableInst::instance().getTopTypeUserInfoAddress();
	
	TypePositionParseHandler& typePosHandler = SemanticsParserMgrInst::instance().getTypePositionParseHandler();
	typePosHandler.addProcessingTypeInfoAddress(nTopUserTypeAddress);
}