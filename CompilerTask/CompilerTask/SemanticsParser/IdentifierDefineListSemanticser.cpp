#include "IdentifierDefineListSemanticser.h"
#include "SemanticsParserMgr.h"
#include "../SymbolTable/SymbolTable.h"
#include "../Log/LogFile.h"
#include "../SyntaxParser/SyntaxParser.h"
#include "../GlobalData/WordStreamTable.h"
#include "../Common/ErrorProcess.h"

IdentifierDefineListSemanticser::IdentifierDefineListSemanticser()
{

}

IdentifierDefineListSemanticser::~IdentifierDefineListSemanticser()
{

}

bool IdentifierDefineListSemanticser::processSemanticsParser()
{
	bool bProcessSemanticser = false;
	IdentifierListFlagHandler&  flagIdStack = SemanticsParserMgrInst::instance().getIdentifierListFlagHandler();
	eSemanticsStackIdFlag flagId = flagIdStack.getCurrentSemanticsParserId();
	switch(flagId){
	case eSPIF_EnumIdentifierListStart:
		bProcessSemanticser = this->processEnumTypeIdentifierList();
		break;

	case eSPIF_RecordIdentifierListStart:
		bProcessSemanticser = this->processRecordIdentifierList();
		break;

	case eSPIF_FieldOfRecordListStart:
		bProcessSemanticser = this->processFieldOfRecordList();
		break;

	case eSPIF_ParamOfProcListStart:
	case eSPIF_ParamOfFunctionListStart:
		bProcessSemanticser = this->processParamTypeOfFunction();
		break;

	case eSPIF_VarIdentifierListStart:
		bProcessSemanticser = this->processVarIdentifierList();
		break;

	case eSPIF_FileIdentifierListStart:
		bProcessSemanticser = this->processFileIdentifierList();
		break;

	default:
		bProcessSemanticser = true;
		break;
	}
	

	return bProcessSemanticser;
}

// ��ʶ���б�->��ʶ�� 012 ��ʶ���б�1    ��ʶ���б�1->, ��ʶ�� 012 ��ʶ���б�1
eSemansticeParserTypeValue IdentifierDefineListSemanticser::returnSemanticserEnumValue()
{
	return eSemansticeParserTypeValue::eSPEV_IdentifierTypeDefineList;
}


bool IdentifierDefineListSemanticser::processEnumTypeIdentifierList()
{
	bool bProcessSemanticser = false;
	const CToken* pConstTokenWord = this->getTokenWordByLastWordIndex();
	if(NULL == pConstTokenWord){
		LogFileInst::instance().logError("IdentifierDefineListSemanticser::processEnumTypeIdentifierList pConstTokenWord null", __FILE__, __LINE__);
		return bProcessSemanticser;
	}

	// ���ڷ����Ĺ���Id
	ProcStackParserHandler& procStackParserHandler = SemanticsParserMgrInst::instance().getProcStackParserHandler();
	int nStackTopProcId = procStackParserHandler.getTopProcStackProcAddress();
	if(nStackTopProcId < 0){
		LogFileInst::instance().logError("IdentifierDefineListSemanticser::processEnumTypeIdentifierList getProcStackTop error", __FILE__, __LINE__);
		return bProcessSemanticser;
	}

	// �Ƿ�ͬ��
	bool bCompareNameWithWord = checkCompareIsSameNameWithWord(nStackTopProcId, pConstTokenWord->m_szContentValue);
	if(true == bCompareNameWithWord){
		EmitErrorFile::EmitError("�ñ�ʶ���Ѿ�����");
		return bProcessSemanticser;
	}

	// �жϵ�ַ�Ƿ�Ϸ�
	int nNewlyEnumAddress = SymbolTableInst::instance().getEmptyOrNewEnumAddressValue();
	if(nNewlyEnumAddress < 0){
		LogFileInst::instance().logError("IdentifierDefineListSemanticser::processEnumTypeIdentifierList nNewlyEnumAddress error", __FILE__, __LINE__);
		return bProcessSemanticser;
	}

	int nNewlyBeginEnumAddress = SymbolTableInst::instance().getNewEnumBeginAddressValue();
	if((nNewlyEnumAddress - nNewlyBeginEnumAddress) > 256){
		EmitErrorFile::EmitError("ö�������Ѿ�������������������ƣ�256");
		return bProcessSemanticser;
	}

	// ��ʼ������
	EnumInfo* pEmptyEnumValue = SymbolTableInst::instance().getEnumInfoByEnumAddress(nNewlyEnumAddress);
	if(NULL == pEmptyEnumValue){
		LogFileInst::instance().logError("IdentifierDefineListSemanticser::processEnumTypeIdentifierList pEmptyEnumValue null", __FILE__, __LINE__);
		return bProcessSemanticser;
	}


	pEmptyEnumValue->initStrName(pConstTokenWord->m_szContentValue);
	pEmptyEnumValue->initProcIndex(nStackTopProcId);

	bProcessSemanticser = true;
	return bProcessSemanticser;
}


bool IdentifierDefineListSemanticser::processRecordIdentifierList()
{
	bool bProcessSemanticser = false;

	const CToken* pParserWord = this->getTokenWordByLastWordIndex();
	if(NULL == pParserWord){
		LogFileInst::instance().logError("IdentifierDefineListSemanticser::processRecordIdentifierList pParserWord null", __FILE__, __LINE__);
		return bProcessSemanticser;
	}

	TypeInfo* pUserDefineTypeInfo = this->getTypeInfoByParsingTypePosition();
	if(NULL == pUserDefineTypeInfo){
		LogFileInst::instance().logError("IdentifierDefineListSemanticser::processRecordIdentifierList pUserDefineTypeInfo null ", __FILE__, __LINE__);
		return bProcessSemanticser;
	}

	
	FieldInfo newFieldInfo;
	newFieldInfo.initStrName(pParserWord->m_szContentValue);
	ProcStackParserHandler& procStackHandler = SemanticsParserMgrInst::instance().getProcStackParserHandler();
	newFieldInfo.initProcIndex(procStackHandler.getTopProcStackProcAddress());
	newFieldInfo.m_nProcessState = 0;

	// ��֤�����Ƿ����
	FieldInfoVec& vecFieldInfo = pUserDefineTypeInfo->m_FieldInfo;
	for(unsigned int i = 0; i < vecFieldInfo.size(); ++i){
		const std::string& strFieldStringName = vecFieldInfo[i].m_strName;
		int nCompareResult = strFieldStringName.compare(newFieldInfo.m_strName);
		if(0 == nCompareResult){
			std::string strErrorData("�����Ѿ����ڣ��ظ����� �ֶ���:");
			strErrorData.append(newFieldInfo.m_strName);
			EmitErrorFile::EmitError(strErrorData);
			return bProcessSemanticser;
		}
	}

	vecFieldInfo.push_back(newFieldInfo);

	bProcessSemanticser = true;
	return bProcessSemanticser;
}

//�����б�ı�ʶ��
bool IdentifierDefineListSemanticser::processVarIdentifierList()
{
	bool bProcessSemanticser = false;

	const CToken* pConstTokenWord = this->getTokenWordByLastWordIndex();
	if (NULL == pConstTokenWord){
		LogFileInst::instance().logError("IdentifierDefineListSemanticser::processVarIdentifierList pConstTokenWord null", __FILE__, __LINE__);
		return bProcessSemanticser;
	}

	// ���ڷ����Ĺ���Id
	ProcStackParserHandler& procStackParserHandler = SemanticsParserMgrInst::instance().getProcStackParserHandler();
	int nStackTopProcId = procStackParserHandler.getTopProcStackProcAddress();
	if(nStackTopProcId < 0){
		LogFileInst::instance().logError("IdentifierDefineListSemanticser::processVarIdentifierList getProcStackTop error", __FILE__, __LINE__);
		return bProcessSemanticser;
	}

	// �Ƿ�ͬ��
	bool bCompareNameWithWord = checkCompareIsSameNameWithWord(nStackTopProcId, pConstTokenWord->m_szContentValue);
	if(true == bCompareNameWithWord){
		return bProcessSemanticser;
	}

	// ������ û�и��ñ�����ͬ���� �򽫸ñ������������(����,����ʧ��)
	VarInfo newVarInfo;
	newVarInfo.initStrName(pConstTokenWord->m_szContentValue);
	newVarInfo.initProcIndex(nStackTopProcId);
	newVarInfo.m_eRank = VarInfo::eR_Var;
	SymbolTableInst::instance().addNewVarToSpecficProcId(newVarInfo);

	bProcessSemanticser = true;
	return bProcessSemanticser;
}


//����USESģ���������
bool IdentifierDefineListSemanticser::processFileIdentifierList()
{
	bool bProcessSemanticser = false;

	const CToken* pConstTokenWord = this->getTokenWordByLastWordIndex();
	if (NULL == pConstTokenWord){
		LogFileInst::instance().logError("IdentifierDefineListSemanticser::processFileIdentifierList pConstTokenWord null", __FILE__, __LINE__);
		return bProcessSemanticser;
	}

	// ��ѯ���ű��Ƿ��Ѿ�������ʹ���ļ�
	int nUseFileAddressValue = SymbolTableInst::instance().searchUseFileTable(pConstTokenWord->m_szContentValue);
	if(nUseFileAddressValue > 0){
		LogFileInst::instance().logError("IdentifierDefineListSemanticser::processFileIdentifierList ģ���Ѿ������� null", __FILE__, __LINE__);
		return bProcessSemanticser;
	}

	// û�еĻ� ���ű���а���
	SymbolTableInst::instance().addNewUseFlieData(pConstTokenWord->m_szContentValue);

	bProcessSemanticser = true;
	return bProcessSemanticser;
}


bool IdentifierDefineListSemanticser::processFieldOfRecordList()
{
	bool bProcessSemanticser = false;

	const CToken* pParserWord = this->getTokenWordByLastWordIndex();
	if(NULL == pParserWord){
		LogFileInst::instance().logError("IdentifierDefineListSemanticser::processRecordIdentifierList pParserWord null", __FILE__, __LINE__);
		return bProcessSemanticser;
	}

	TypeInfo* pUserDefineTypeInfo = this->getTypeInfoByParsingTypePosition();
	if(NULL == pUserDefineTypeInfo){
		LogFileInst::instance().logError("IdentifierDefineListSemanticser::processRecordIdentifierList  pUserDefineTypeInfo null ", __FILE__, __LINE__);
		return bProcessSemanticser;
	}

	FieldOfRecordParserHandler& fieldOfRecordHandler = SemanticsParserMgrInst::instance().getFieldOfRecordParserHandler();

	FieldInfo newFieldInfo;
	newFieldInfo.initStrName(pParserWord->m_szContentValue);
	ProcStackParserHandler& procStackHandler = SemanticsParserMgrInst::instance().getProcStackParserHandler();
	newFieldInfo.initProcIndex(procStackHandler.getTopProcStackProcAddress());
	newFieldInfo.m_nProcessState = 0;
	newFieldInfo.m_strVarFieldConst = fieldOfRecordHandler.getConstFieldStackTop();
	newFieldInfo.m_strVarFieldFlag = fieldOfRecordHandler.getFlagFieldStackTop();

	// ��֤�����Ƿ����
	FieldInfoVec& vecFieldInfo = pUserDefineTypeInfo->m_FieldInfo;
	for (unsigned int i = 0; i < vecFieldInfo.size(); ++i){
		const std::string& strFieldStringName = vecFieldInfo[i].m_strName;
		int nCompareResult = strFieldStringName.compare(newFieldInfo.m_strName);
		if (0 == nCompareResult){
			std::string strErrorData("�����Ѿ����ڣ��ظ����� �ֶ���:");
			strErrorData.append(newFieldInfo.m_strName);
			EmitErrorFile::EmitError(strErrorData);
			return bProcessSemanticser;
		}
	}

	vecFieldInfo.push_back(newFieldInfo);

	bProcessSemanticser = true;
	return bProcessSemanticser;
}


bool IdentifierDefineListSemanticser::processParamTypeOfFunction()
{
	bool bProcessSemanticser = false;

	const CToken* pParserWord = this->getTokenWordByLastWordIndex();
	if(NULL == pParserWord){
		LogFileInst::instance().logError("IdentifierDefineListSemanticser::processParamTypeOfFunction pParserWord null", __FILE__, __LINE__);
		return bProcessSemanticser;
	}

	
	ProcInfo* pNewProcInfo = SymbolTableInst::instance().getRecenetlyProcIndex();
	if(NULL == pNewProcInfo){
		LogFileInst::instance().logError("IdentifierDefineListSemanticser::processParamTypeOfFunction pNewProcInfo null", __FILE__, __LINE__);
		return bProcessSemanticser;
	}

	// У��
	const ParaInfoVec& vecParamInfo = pNewProcInfo->m_ParaTable;
	for(int i = 0; i < vecParamInfo.size(); ++i){
		const ParaInfo& checkParamInfo = vecParamInfo[i];
		if(0 != checkParamInfo.m_strParamName.compare(pParserWord->m_szContentValue)){
			EmitErrorFile::EmitError("��ʶ�����Ѿ�����");
			return bProcessSemanticser;
		}
	}

	// ���µĲ�����������б�
	ParaInfo::AssignType assignType = ParaInfo::VAR;
	IdentifierListFlagHandler& identifierListHandler = SemanticsParserMgrInst::instance().getIdentifierListFlagHandler();
	eSemanticsStackIdFlag flagValueOfIdentifier = identifierListHandler.getCurrentSemanticsParserId();
	if(eSPIF_ParamOfProcListStart == flagValueOfIdentifier){
		assignType = ParaInfo::VAL;
	}

	
	ParaInfo newParamInfo;
	newParamInfo.m_strParamName = (pParserWord->m_szContentValue);
	newParamInfo.m_eAssignType = assignType;
	newParamInfo.m_nParamType = -1;

	pNewProcInfo->m_ParaTable.push_back(newParamInfo);

	bProcessSemanticser = true;
	return bProcessSemanticser;
}