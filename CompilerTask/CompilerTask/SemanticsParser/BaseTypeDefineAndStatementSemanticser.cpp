#include "BaseTypeDefineAndStatementSemanticser.h"
#include "SemanticsParserMgr.h"
#include "../SymbolTable/TypeInfoUserTable.h"
#include "../Log/LogFile.h"
#include "../SymbolTable/SymbolTable.h"
#include "../Common/IntStringConverter.h"
#include "TypeEnumConverter.h"
#include "../Common/Structure.h"
#include "../Common/ErrorProcess.h"

BaseTypeDefineAndStatementSemanticser::BaseTypeDefineAndStatementSemanticser()
{

}

BaseTypeDefineAndStatementSemanticser::~BaseTypeDefineAndStatementSemanticser()
{

}

bool BaseTypeDefineAndStatementSemanticser::processSemanticsParser()
{
	bool bProcessSemanticsResult = false;
	
	TypeFlagHandler& typeFlagHandler = SemanticsParserMgrInst::instance().getTypeFlagHandler();
	eTypeFlagEnumValue typeEnumValue = typeFlagHandler.getTopTypeFlagValue();
	switch(typeEnumValue)
	{
	case eTFEV_SetTypeValue:
		bProcessSemanticsResult = this->processSetTypeOfSemanticsParser();
 		break;

	case eTFEV_ProcTypeValue:
	case eTFEV_FunctionTypeValue:
		bProcessSemanticsResult = this->processFunctionParamOfSemanticsParser();
		break;

	case eTFEV_FunctionRetTypeValue:
		bProcessSemanticsResult = this->processRetOfFunctionOfSemanticsParser();
		break;
	
	case eTFEV_MainTypeValue:
	case eTFEV_RecordTypeValue:
	case eTFEV_ArrayTypeValue:
	case eTFEV_FileTypeValue:
		bProcessSemanticsResult = this->processSpecficOtherTypeOfSemanticsParser();
		break;

	default:
		bProcessSemanticsResult = false;
		break;
	}

	return bProcessSemanticsResult;
}


eSemansticeParserTypeValue BaseTypeDefineAndStatementSemanticser::returnSemanticserEnumValue()
{
	return eSemansticeParserTypeValue::eSPEV_BaseTypeDefineAndStatement;
}


bool BaseTypeDefineAndStatementSemanticser::processSetTypeOfSemanticsParser()
{
	bool bProcessSemanticsResult = false;
	
	// �жϻ�����
	const CToken* pTokenWord= this->getTokenWordByLastWordIndex();
	if(NULL == pTokenWord){
		LogFileInst::instance().logError("BaseTypeDefineAndStatementSemanticser::processSetTypeOfSemanticsParser pTokenWord null", __FILE__, __LINE__);
		return bProcessSemanticsResult;
	}

	eDataStoreEnumValue storeEnumValue = TypeEnumConverter::wordStatusToDataStoreType(pTokenWord->m_nWordStatus);
	if((eDataStoreEnumValue::eDSEV_Boolean != storeEnumValue) && (eDataStoreEnumValue::eDSEV_Byte != storeEnumValue) && (eDataStoreEnumValue::eDSEV_Char != storeEnumValue) && (eDataStoreEnumValue::eDSEV_ShortInt != storeEnumValue)){
		std::string strErrorData("�������͵Ļ����Ͳ���ȷ ����:");
		strErrorData.append(pTokenWord->m_szContentValue);
		EmitErrorFile::EmitError(strErrorData);
		return bProcessSemanticsResult;
	}

	// ����һ����У��
	TypeInfo* pUserTypeInfo = this->getTypeInfoByParsingTypePosition();
	if(NULL == pUserTypeInfo){
		LogFileInst::instance().logError("BaseTypeDefineAndStatementSemanticser::processSetTypeOfSemanticsParser pUserTypeInfo null", __FILE__, __LINE__);
		return bProcessSemanticsResult;
	}

	ProcStackParserHandler& procParserHandler = SemanticsParserMgrInst::instance().getProcStackParserHandler();
	int nTopProcAddress = procParserHandler.getTopProcStackProcAddress();

	// ��ʼ��������
	int nSerialIdValue = SymbolTableInst::instance().getSerialId();
	std::string strSerialValue = IntStringConverter::intValueConvertToString(nSerialIdValue);
	std::string strInitTypeName("_noname");
	strInitTypeName.append(strSerialValue);

	// ��Ӧ�ļ������� �ĵ�ַ
	int nSetTypeAddressValue = SymbolTableInst::instance().addNewUserTypeInfoToTable(strInitTypeName, nTopProcAddress);
	if(nSetTypeAddressValue < 0){
		LogFileInst::instance().logError("BaseTypeDefineAndStatementSemanticser::processSetTypeOfSemanticsParser nSetTypeAddressValue error", __FILE__, __LINE__);
		return bProcessSemanticsResult;
	}

	// ���ü��ϵ�link��ַ
	pUserTypeInfo->m_nAddressLink = nSetTypeAddressValue;
	pUserTypeInfo->m_nProcessState = 1;

	// ȡ����Ӧ�ļ��ϵľ������͵�TypeInfo
	TypeInfo* pSetTypeAddressTypeInfo = SymbolTableInst::instance().getTypeInfoFromTableAddress(nSetTypeAddressValue);
	if(NULL == pSetTypeAddressTypeInfo){
		LogFileInst::instance().logError("BaseTypeDefineAndStatementSemanticser::processSetTypeOfSemanticsParser pSetTypeAddressTypeInfo null", __FILE__, __LINE__);
		return bProcessSemanticsResult;
	}

	pSetTypeAddressTypeInfo->m_nProcessState = 1;
	pSetTypeAddressTypeInfo->m_eBaseType = storeEnumValue;
	pSetTypeAddressTypeInfo->m_eDataType = storeEnumValue;

	bProcessSemanticsResult = true;
	return bProcessSemanticsResult;
}


bool BaseTypeDefineAndStatementSemanticser::processFunctionParamOfSemanticsParser()
{
	bool bProcessSemanticsResult = false;

	// �жϻ�����
	const CToken* pTokenWord = this->getTokenWordByLastWordIndex();
	if (NULL == pTokenWord){
		LogFileInst::instance().logError("BaseTypeDefineAndStatementSemanticser::processFunctionTypeOfSemanticsParser pTokenWord null", __FILE__, __LINE__);
		return bProcessSemanticsResult;
	}

	// ����ջ������
	ProcStackParserHandler& procParserHandler = SemanticsParserMgrInst::instance().getProcStackParserHandler();
	int nTopProcAddress = procParserHandler.getTopProcStackProcAddress();

	// ��ʼ��������
	int nSerialIdValue = SymbolTableInst::instance().getSerialId();
	std::string strSerialValue = IntStringConverter::intValueConvertToString(nSerialIdValue);
	std::string strInitTypeName("_noname");
	strInitTypeName.append(strSerialValue);

	// ��Ӧ�ļ������� �ĵ�ַ
	int nFunctionAddressValue = SymbolTableInst::instance().addNewUserTypeInfoToTable(strInitTypeName, nTopProcAddress);
	if(nFunctionAddressValue < 0){
		LogFileInst::instance().logError("BaseTypeDefineAndStatementSemanticser::processFunctionTypeOfSemanticsParse nFunctionAddressValue error", __FILE__, __LINE__);
		return bProcessSemanticsResult;
	}

	// ȡ����Ӧ�ļ��ϵľ������͵�TypeInfo
	TypeInfo* pFunctionAddressType = SymbolTableInst::instance().getTypeInfoFromTableAddress(nFunctionAddressValue);
	if(NULL == pFunctionAddressType){
		LogFileInst::instance().logError("BaseTypeDefineAndStatementSemanticser::processFunctionTypeOfSemanticsParse pFunctionAddressType null", __FILE__, __LINE__);
		return bProcessSemanticsResult;
	}

	eDataStoreEnumValue storeEnumValue = TypeEnumConverter::wordStatusToDataStoreType(pTokenWord->m_nWordStatus);
	pFunctionAddressType->m_nProcessState = 1;
	pFunctionAddressType->m_eBaseType = storeEnumValue;
	pFunctionAddressType->m_eDataType = storeEnumValue;

	// ���ò����б�
	ProcInfo* pNewlyProcData= SymbolTableInst::instance().getRecenetlyProcIndex();
	if(NULL == pNewlyProcData){
		LogFileInst::instance().logError("BaseTypeDefineAndStatementSemanticser::processFunctionTypeOfSemanticsParse pNewlyProcData null", __FILE__, __LINE__);
		return bProcessSemanticsResult;
	}

	ParaInfoVec& vecParamInfo = pNewlyProcData->m_ParaTable;
	for(unsigned int i = 0; i < vecParamInfo.size(); i++){
		ParaInfo& initParamInfo = vecParamInfo[i];
		if(-1 != initParamInfo.m_nParamType){
			continue;
		}
		
		initParamInfo.m_nParamType = nFunctionAddressValue;
	}
	

	bProcessSemanticsResult = true;
	return bProcessSemanticsResult;
}


bool BaseTypeDefineAndStatementSemanticser::processRetOfFunctionOfSemanticsParser()
{
	bool bProcessSemanticsResult = false;

	// �жϻ�����
	const CToken* pTokenWord = this->getTokenWordByLastWordIndex();
	if(NULL == pTokenWord){
		LogFileInst::instance().logError("BaseTypeDefineAndStatementSemanticser::processRetOfFunctionOfSemanticsParser pTokenWord null", __FILE__, __LINE__);
		return bProcessSemanticsResult;
	}

	// ����ջ������
	ProcStackParserHandler& procParserHandler = SemanticsParserMgrInst::instance().getProcStackParserHandler();
	int nTopProcAddress = procParserHandler.getTopProcStackProcAddress();

	// ��ʼ��������
	int nSerialIdValue = SymbolTableInst::instance().getSerialId();
	std::string strSerialValue = IntStringConverter::intValueConvertToString(nSerialIdValue);
	std::string strInitTypeName("_noname");
	strInitTypeName.append(strSerialValue);

	// ��Ӧ�ļ������� �ĵ�ַ
	int nFunctionRetValueAddress = SymbolTableInst::instance().addNewUserTypeInfoToTable(strInitTypeName, nTopProcAddress);
	if(nFunctionRetValueAddress < 0){
		LogFileInst::instance().logError("BaseTypeDefineAndStatementSemanticser::processRetOfFunctionOfSemanticsParser nFunctionAddressValue error", __FILE__, __LINE__);
		return bProcessSemanticsResult;
	}

	// ȡ����Ӧ�ļ��ϵľ������͵�TypeInfo
	TypeInfo* pFunctionAddressType = SymbolTableInst::instance().getTypeInfoFromTableAddress(nFunctionRetValueAddress);
	if(NULL == pFunctionAddressType){
		LogFileInst::instance().logError("BaseTypeDefineAndStatementSemanticser::processRetOfFunctionOfSemanticsParser pFunctionAddressType null", __FILE__, __LINE__);
		return bProcessSemanticsResult;
	}

	// ��������
	eDataStoreEnumValue enumValueDataStore = TypeEnumConverter::wordStatusToDataStoreType(pTokenWord->m_nWordStatus);
	pFunctionAddressType->m_nProcessState = 1;
	pFunctionAddressType->m_eBaseType = enumValueDataStore;
	pFunctionAddressType->m_eDataType = enumValueDataStore;

	ProcInfo* pLastProcInfo = SymbolTableInst::instance().getRecenetlyProcIndex();
	if(NULL == pLastProcInfo){
		LogFileInst::instance().logError("BaseTypeDefineAndStatementSemanticser::processRetOfFunctionOfSemanticsParser pLastProcInfo null", __FILE__, __LINE__);
		return bProcessSemanticsResult;
	}

	pLastProcInfo->m_nReturnType = nFunctionRetValueAddress;

	bProcessSemanticsResult = true;
	return bProcessSemanticsResult;
}


bool BaseTypeDefineAndStatementSemanticser::processSpecficOtherTypeOfSemanticsParser()
{
	bool bProcessSemanticsResult = false;
	// �жϻ�����
	const CToken* pTokenWord = this->getTokenWordByLastWordIndex();
	if(NULL == pTokenWord){
		LogFileInst::instance().logError("BaseTypeDefineAndStatementSemanticser::processSpecficOtherTypeOfSemanticsParser pTokenWord null", __FILE__, __LINE__);
		return bProcessSemanticsResult;
	}

	TypePositionParseHandler& typePositionHandler = SemanticsParserMgrInst::instance().getTypePositionParseHandler();
	if(true == typePositionHandler.isEmptyStatus()){
		bProcessSemanticsResult = true;
		return bProcessSemanticsResult;
	}
	
	int nTypeAddressValue = typePositionHandler.getProcessingTypeAddress();
	if(nTypeAddressValue < 0){
		bProcessSemanticsResult = true;
		return bProcessSemanticsResult;
	}

	// ȡ����Ӧ�ļ��ϵľ������͵�TypeInfo
	TypeInfo* pFunctionAddressType = SymbolTableInst::instance().getTypeInfoFromTableAddress(nTypeAddressValue);
	if(NULL == pFunctionAddressType){
		LogFileInst::instance().logError("BaseTypeDefineAndStatementSemanticser::processSpecficOtherTypeOfSemanticsParser pFunctionAddressType null", __FILE__, __LINE__);
		return bProcessSemanticsResult;
	}

	if(eDSEV_Null != pFunctionAddressType->m_eDataType){
		bProcessSemanticsResult = true;
		return bProcessSemanticsResult;
	}

	
	eDataStoreEnumValue enumValueDataStore = TypeEnumConverter::wordStatusToDataStoreType(pTokenWord->m_nWordStatus);
	pFunctionAddressType->m_eBaseType = enumValueDataStore;
	pFunctionAddressType->m_eDataType = enumValueDataStore;
	pFunctionAddressType->m_nProcessState = 1;

	bProcessSemanticsResult = true;
	return bProcessSemanticsResult;
}
