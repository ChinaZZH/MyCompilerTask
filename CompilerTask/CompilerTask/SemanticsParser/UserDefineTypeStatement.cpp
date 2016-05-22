#include "UserDefineTypeStatement.h"

#include "../Log/LogFile.h"
#include "SemanticsParserMgr.h"
#include "../SemanticsFlagHandler/ProcStackParserHandler.h"
#include "../SymbolTable/SymbolTable.h"
#include "../Common/Structure.h"
#include "../Common/ErrorProcess.h"
#include "../SemanticsFlagHandler/TypePositionParseHandler.h"
#include "IncludeFileStatement/IncludeFileBeforeFileNameSemanticser.h"

UserDefineTypeSemanticser::UserDefineTypeSemanticser()
{

}

UserDefineTypeSemanticser::~UserDefineTypeSemanticser()
{

}


bool UserDefineTypeSemanticser::processSemanticsParser()
{
	bool bProcessSemanticsResult = false;
	
	// �жϻ�����
	const CToken* pTokenWord = this->getTokenWordByLastWordIndex();
	if(NULL == pTokenWord){
		LogFileInst::instance().logError("UserDefineTypeSemanticser::processSemanticsParser pTokenWord null", __FILE__, __LINE__);
		return bProcessSemanticsResult;
	}

	ProcStackParserHandler& procParserHandler = SemanticsParserMgrInst::instance().getProcStackParserHandler();
	int nTopProcAddress = procParserHandler.getTopProcStackProcAddress();

	// �Ҷ�Ӧ���� �ĵ�ַ(������ǰ�������û��������������)
	const std::string& strTypeName = pTokenWord->m_szContentValue;
	int nTypeAddressValue = SymbolTableInst::instance().searchTypeInfoTable(nTopProcAddress, strTypeName);
	if(nTypeAddressValue < 0){
		int nMainProcAddress = 0;
		nTypeAddressValue = SymbolTableInst::instance().searchTypeInfoTable(nMainProcAddress, strTypeName);
	}

	// û���ҵ���Ӧ������
	if(nTypeAddressValue < 0){
		std::string strErrorData("����δ������岻����: ");
		strErrorData.append(pTokenWord->m_szContentValue);
		EmitErrorFile::EmitError(strErrorData);

		LogFileInst::instance().logError("UserDefineTypeSemanticser::processSemanticsParser û���ҵ���Ӧ������ ", __FILE__, __LINE__);
		return bProcessSemanticsResult;
	}

	TypeFlagHandler& typeFlagHandler = SemanticsParserMgrInst::instance().getTypeFlagHandler();
	eTypeFlagEnumValue enumValueTypeFlag= typeFlagHandler.getTopTypeFlagValue();
	switch(enumValueTypeFlag)
	{
	case eTFEV_SetTypeValue:
		bProcessSemanticsResult = this->processUserDefineOfSetType(nTypeAddressValue);
		break;

	// ��������, ��������
	case eTFEV_ProcTypeValue:
	case eTFEV_FunctionTypeValue:
		bProcessSemanticsResult = this->processUserDefineOfFunctionParam(nTypeAddressValue);
		break;

	case eTFEV_FunctionRetTypeValue:
		bProcessSemanticsResult = this->processUserDefineOfFunctionRetValue(nTypeAddressValue);
		break;

	// �Զ�������
	default:
		bProcessSemanticsResult = this->processUserDefine(nTypeAddressValue);
		break;
	}


	return bProcessSemanticsResult;
}


eSemansticeParserTypeValue UserDefineTypeSemanticser::returnSemanticserEnumValue()
{
	return eSPEV_UserDefineTypeStatement;
}


bool UserDefineTypeSemanticser::processUserDefineOfSetType(int nLinkTypeAddress)
{
	bool bProcessSemanticsResult = false;

	const CToken* pTokenWord = this->getTokenWordByLastWordIndex();
	if(NULL == pTokenWord){
		LogFileInst::instance().logError("UserDefineTypeSemanticser::processUserDefineOfSetType pTokenWord null", __FILE__, __LINE__);
		return bProcessSemanticsResult;
	}

	int nBaseTypeAddressValue = nLinkTypeAddress;
	while(1){
		TypeInfo* pTypeInfo = SymbolTableInst::instance().getTypeInfoFromTableAddress(nBaseTypeAddressValue);
		if(NULL == pTypeInfo){
			std::string strErrorData("�������͵Ļ����Ͳ���ȷ:");
			strErrorData.append(pTokenWord->m_szContentValue);
			EmitErrorFile::EmitError(strErrorData);
			return bProcessSemanticsResult;
		}

		if(eDataStoreEnumValue::eDSEV_User != pTypeInfo->m_eDataType){
			break;
		}
		
		// ǰ�����͵ĵ�ַ
		nBaseTypeAddressValue = pTypeInfo->m_nAddressLink;
	}


	TypeInfo* pTypeInfo = SymbolTableInst::instance().getTypeInfoFromTableAddress(nBaseTypeAddressValue);
	if(NULL == pTypeInfo){
		LogFileInst::instance().logError("UserDefineTypeSemanticser::processUserDefineOfSetType pTypeInfo null", __FILE__, __LINE__);
		return bProcessSemanticsResult;
	}
	
	eDataStoreEnumValue enumValueDataType = pTypeInfo->m_eDataType;
	if ((eDataStoreEnumValue::eDSEV_Boolean == enumValueDataType)
		|| (eDataStoreEnumValue::eDSEV_Byte == enumValueDataType)
		|| (eDataStoreEnumValue::eDSEV_Char == enumValueDataType)
		|| (eDataStoreEnumValue::eDSEV_ShortInt == enumValueDataType)
		|| (eDataStoreEnumValue::eDSEV_SmallInt == enumValueDataType)
		|| (eDataStoreEnumValue::eDSEV_Enum == enumValueDataType)
	   ){
		bProcessSemanticsResult = true;
		return bProcessSemanticsResult;
	}

	// ����
	std::string strErrorData("�������͵Ļ����Ͳ���ȷ:");
	strErrorData.append(pTokenWord->m_szContentValue);
	EmitErrorFile::EmitError(strErrorData);

	bProcessSemanticsResult = false;
	return bProcessSemanticsResult;
}


bool UserDefineTypeSemanticser::processUserDefineOfFunctionParam(int nLinkTypeAddress)
{
	bool bProcessSemanticsResult = false;
	ProcInfo* pNewlyProcInfo = SymbolTableInst::instance().getRecenetlyProcIndex();
	if(NULL == pNewlyProcInfo){
		LogFileInst::instance().logError("UserDefineTypeSemanticser::processUserDefineOfFunctionParam pNewlyProcInfo null", __FILE__, __LINE__);
		return bProcessSemanticsResult;
	}

	ParaInfoVec& vecParamInfo = pNewlyProcInfo->m_ParaTable;
	int nParamInfoSize = static_cast<int>(vecParamInfo.size());
	for(int i = 0; i < nParamInfoSize; ++i){
		ParaInfo& paramInfoData = vecParamInfo[i];
		if(paramInfoData.m_nParamType >= 0){
			continue;
		}

		paramInfoData.m_nParamType = nLinkTypeAddress;
	}

	bProcessSemanticsResult = true;
	return bProcessSemanticsResult;
}


bool UserDefineTypeSemanticser::processUserDefineOfFunctionRetValue(int nLinkTypeAddress)
{
	bool bProcessSemanticsResult = false;
	ProcInfo* pNewlyProcInfo = SymbolTableInst::instance().getRecenetlyProcIndex();
	if(NULL == pNewlyProcInfo){
		LogFileInst::instance().logError("UserDefineTypeSemanticser::processUserDefineOfFunctionRetValue pNewlyProcInfo null", __FILE__, __LINE__);
		return bProcessSemanticsResult;
	}

	pNewlyProcInfo->m_nReturnType = nLinkTypeAddress;

	bProcessSemanticsResult = true;
	return bProcessSemanticsResult;
}


bool UserDefineTypeSemanticser::processUserDefine(int nLinkTypeAddress)
{
	bool bProcessSemanticsResult = false;

	TypePositionParseHandler& typePositionHandler = SemanticsParserMgrInst::instance().getTypePositionParseHandler();
	int nTopTypeAddress = typePositionHandler.getProcessingTypeAddress();
	if(nTopTypeAddress < 0){
		LogFileInst::instance().logError("UserDefineTypeSemanticser::processUserDefine nTopTypeAddress error", __FILE__, __LINE__);
		return bProcessSemanticsResult;
	}

	TypeInfo* pTypeInfo = SymbolTableInst::instance().getTypeInfoFromTableAddress(nTopTypeAddress);
	if(NULL == pTypeInfo){
		LogFileInst::instance().logError("UserDefineTypeSemanticser::processUserDefine pTypeInfo null", __FILE__, __LINE__);
		return bProcessSemanticsResult;
	}

	pTypeInfo->m_nAddressLink = nLinkTypeAddress;
	pTypeInfo->m_eDataType = eDSEV_User;

	bProcessSemanticsResult = true;
	return bProcessSemanticsResult;
}

