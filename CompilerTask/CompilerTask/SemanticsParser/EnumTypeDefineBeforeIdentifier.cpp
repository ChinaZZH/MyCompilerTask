#include "EnumTypeDefineBeforeIdentifier.h"
#include "SemanticsParserMgr.h"
#include "../Log/LogFile.h"
#include "../SymbolTable/SymbolTable.h"
#include "../Common/IntStringConverter.h"

EnumTypeDefineBeforeIdentifier::EnumTypeDefineBeforeIdentifier()
{

}

EnumTypeDefineBeforeIdentifier::~EnumTypeDefineBeforeIdentifier()
{

}

bool EnumTypeDefineBeforeIdentifier::processSemanticsParser()
{
	bool bProcessSemanticsResult = false;

	// �ҵ���Ӧ���͵ĵ�ַ
	TypePositionParseHandler& typePositionHandler = SemanticsParserMgrInst::instance().getTypePositionParseHandler();
	int nTopTypeAddress = typePositionHandler.getProcessingTypeAddress();
	if(nTopTypeAddress < 0){
		LogFileInst::instance().logError("EnumTypeDefineBeforeIdentifier::processSemanticsParser nTopTypeAddress error", __FILE__, __LINE__);
		return bProcessSemanticsResult;
	}

	// �ҵ���Ӧ���͵�ָ��
	TypeInfo* pTypeInfo = SymbolTableInst::instance().getTypeInfoFromTableAddress(nTopTypeAddress);
	if(NULL == pTypeInfo){
		LogFileInst::instance().logError("EnumTypeDefineBeforeIdentifier::processSemanticsParser pTypeInfo null", __FILE__, __LINE__);
		return bProcessSemanticsResult;
	}

	int nEmptyNewEnumAddress = SymbolTableInst::instance().createNewEnumUnitSpace();
	if(nEmptyNewEnumAddress < 0){
		LogFileInst::instance().logError("EnumTypeDefineBeforeIdentifier::processSemanticsParser nEmptyNewEnumAddress error", __FILE__, __LINE__);
		return bProcessSemanticsResult;
	}

	// ���ñ�ʶ��������״̬
	IdentifierListFlagHandler& identifierListHandler = SemanticsParserMgrInst::instance().getIdentifierListFlagHandler();
	identifierListHandler.startNewSemanticserParserFlag(eSPIF_EnumIdentifierListStart);


	// �������� ���⴦��
	TypeFlagHandler& typeFlagHandler = SemanticsParserMgrInst::instance().getTypeFlagHandler();
	eTypeFlagEnumValue enumValueTypeFlag = typeFlagHandler.getTopTypeFlagValue();
	if(eTFEV_SetTypeValue == enumValueTypeFlag){
		bProcessSemanticsResult = this->processSetOfEnumElementCondition(pTypeInfo, nEmptyNewEnumAddress);
		return bProcessSemanticsResult;
	}

	
	pTypeInfo->m_nAddressLink = nEmptyNewEnumAddress;
	pTypeInfo->m_eDataType = eDSEV_Enum;

	bProcessSemanticsResult = true;
	return bProcessSemanticsResult;
}

eSemansticeParserTypeValue EnumTypeDefineBeforeIdentifier::returnSemanticserEnumValue()
{
	return eSemansticeParserTypeValue::eSPEV_EnumTypeDefineBeforeIdentifier;
}


bool EnumTypeDefineBeforeIdentifier::processSetOfEnumElementCondition(TypeInfo* pTypeInfo, int nEmptyNewEnumAddress)
{
	bool bProcessSemanticsResult = false;

	if(NULL == pTypeInfo){
		LogFileInst::instance().logError("EnumTypeDefineBeforeIdentifier::processSemanticsParser pTypeInfo null", __FILE__, __LINE__);
		return bProcessSemanticsResult;
	}

	// ����id
	ProcStackParserHandler& procParserHandler = SemanticsParserMgrInst::instance().getProcStackParserHandler();
	int nTopProcAddress = procParserHandler.getTopProcStackProcAddress();

	// ��ʼ��������
	int nSerialIdValue = SymbolTableInst::instance().getSerialId();
	std::string strSerialValue = IntStringConverter::intValueConvertToString(nSerialIdValue);
	std::string strInitTypeName("_noname");
	strInitTypeName.append(strSerialValue);

	int nEnumValueAddressValue = SymbolTableInst::instance().addNewUserTypeInfoToTable(strInitTypeName, nTopProcAddress);
	if(nEnumValueAddressValue < 0){
		LogFileInst::instance().logError("EnumTypeDefineBeforeIdentifier::processSemanticsParser nEmptyNewEnumAddress error", __FILE__, __LINE__);
		return bProcessSemanticsResult;
	}

	
	TypeInfo* pEnumValueTypeInfo = SymbolTableInst::instance().getTypeInfoFromTableAddress(nEnumValueAddressValue);
	if (NULL == pEnumValueTypeInfo){
		LogFileInst::instance().logError("EnumTypeDefineBeforeIdentifier::processSemanticsParser pEnumValueTypeInfo null", __FILE__, __LINE__);
		return bProcessSemanticsResult;
	}

	// ����Ԫ�ص�type��ʼ��
	pEnumValueTypeInfo->m_nProcessState = 1;
	pEnumValueTypeInfo->m_eDataType = eDSEV_Enum;
	pEnumValueTypeInfo->m_nAddressLink = nEmptyNewEnumAddress;

	// ��Ӧ��set<enum>�е�set���ͳ�ʼ��
	pTypeInfo->m_nAddressLink = nEnumValueAddressValue;
	pTypeInfo->m_nProcessState = 1;

	bProcessSemanticsResult = true;
	return bProcessSemanticsResult;
}