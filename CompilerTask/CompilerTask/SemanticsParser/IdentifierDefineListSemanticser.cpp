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
	case eSPIF_RecordIdentifierListStart:
		bProcessSemanticser = this->processRecordIdentifierList();
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

bool IdentifierDefineListSemanticser::processRecordIdentifierList()
{
	bool bProcessSemanticser = false;

	int nParserWordTableIndex = SyntaxParserInst::instance().getParserWordTableIndex();
	if(nParserWordTableIndex <= 0){
		LogFileInst::instance().logError("IdentifierDefineListSemanticser::processRecordIdentifierList nParserWordTableIndex error", __FILE__, __LINE__);
		return bProcessSemanticser;
	}

	// ��ʶ���б��ʶ��
	int nLastParserWordIndex = nParserWordTableIndex - 1;
	if(nLastParserWordIndex <= 0){
		LogFileInst::instance().logError("IdentifierDefineListSemanticser::processRecordIdentifierList nLastParserWordIndex error", __FILE__, __LINE__);
		return bProcessSemanticser;
	}

	// �Ӵʷ������еõ��� ���ʼ�  ��ȥ�� ��Ӧ�ĵ���
	const CToken* pParserWord = WordStreamTableInst::instance().getWordTokenByTableIndex(nLastParserWordIndex);
	if(NULL == pParserWord){
		LogFileInst::instance().logError("IdentifierDefineListSemanticser::processRecordIdentifierList pParserWord null", __FILE__, __LINE__);
		return bProcessSemanticser;
	}

	TypePositionParseHandler& typePositionHandler = SemanticsParserMgrInst::instance().getTypePositionParseHandler();
	TypeInfo* pUserDefineTypeInfo = SymbolTableInst::instance().getTypeInfoFromTableAddress(typePositionHandler.getProcessingTypeAddress());
	if(NULL == pUserDefineTypeInfo){
		LogFileInst::instance().logError("IdentifierDefineListSemanticser::processRecordIdentifierList pUserDefineTypeInfo null", __FILE__, __LINE__);
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

	// ��õ��ʵ��±�ֵ
	int nParserWordIndex = SyntaxParserInst::instance().getParserWordTableIndex();
	nParserWordIndex = nParserWordIndex - 1;
	if(nParserWordIndex < 0){
		LogFileInst::instance().logError("IdentifierDefineListSemanticser::processVarIdentifierList nParserWordIndex error", __FILE__, __LINE__);
		return bProcessSemanticser;
	}

	// �ӵ��������л�ȡ��Ӧ�ĵ���
	const CToken* pConstTokenWord = WordStreamTableInst::instance().getWordTokenByTableIndex(nParserWordIndex);
	if(NULL == pConstTokenWord){
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

	// ��õ��ʵ��±�ֵ
	int nParserWordIndex = SyntaxParserInst::instance().getParserWordTableIndex();
	nParserWordIndex = nParserWordIndex - 1;
	if(nParserWordIndex < 0){
		LogFileInst::instance().logError("IdentifierDefineListSemanticser::processFileIdentifierList nParserWordIndex error", __FILE__, __LINE__);
		return bProcessSemanticser;
	}

	// �ӵ��������л�ȡ��Ӧ�ĵ���
	const CToken* pConstTokenWord = WordStreamTableInst::instance().getWordTokenByTableIndex(nParserWordIndex);
	if(NULL == pConstTokenWord){
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
