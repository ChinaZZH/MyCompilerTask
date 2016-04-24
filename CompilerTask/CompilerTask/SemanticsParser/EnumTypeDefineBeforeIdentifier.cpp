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

	// 找到对应类型的地址
	TypePositionParseHandler& typePositionHandler = SemanticsParserMgrInst::instance().getTypePositionParseHandler();
	int nTopTypeAddress = typePositionHandler.getProcessingTypeAddress();
	if(nTopTypeAddress < 0){
		LogFileInst::instance().logError("EnumTypeDefineBeforeIdentifier::processSemanticsParser nTopTypeAddress error", __FILE__, __LINE__);
		return bProcessSemanticsResult;
	}

	// 找到对应类型的指针
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

	// 设置标识符处理器状态
	IdentifierListFlagHandler& identifierListHandler = SemanticsParserMgrInst::instance().getIdentifierListFlagHandler();
	identifierListHandler.startNewSemanticserParserFlag(eSPIF_EnumIdentifierListStart);


	// 集合类型 特殊处理
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

	// 过程id
	ProcStackParserHandler& procParserHandler = SemanticsParserMgrInst::instance().getProcStackParserHandler();
	int nTopProcAddress = procParserHandler.getTopProcStackProcAddress();

	// 初始化类型名
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

	// 集合元素的type初始化
	pEnumValueTypeInfo->m_nProcessState = 1;
	pEnumValueTypeInfo->m_eDataType = eDSEV_Enum;
	pEnumValueTypeInfo->m_nAddressLink = nEmptyNewEnumAddress;

	// 对应的set<enum>中的set类型初始化
	pTypeInfo->m_nAddressLink = nEnumValueAddressValue;
	pTypeInfo->m_nProcessState = 1;

	bProcessSemanticsResult = true;
	return bProcessSemanticsResult;
}