#include "IdentifierDefineListSemanticser.h"
#include "SemanticsParserMgr.h"
#include "../SymbolTable/SymbolTable.h"
#include "../Log/LogFile.h"
#include "../SyntaxParser/SyntaxParser.h"
#include "../GlobalData/WordStreamTable.h"

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

	// �Ƿ�����ͱ���Ϣ���е�����ͬ��
	int nTypeInfoAddressValue = SymbolTableInst::instance().searchTypeInfoTable(nStackTopProcId, pConstTokenWord->m_szContentValue);
	if(nTypeInfoAddressValue >= 0){
		return bProcessSemanticser;
	}

	// �ڵ�ǰ������ �Ƿ��г����������ͬ��(����,����ʧ��)
	int nConstAddressValue = SymbolTableInst::instance().searchConstInfoTable(nStackTopProcId, pConstTokenWord->m_szContentValue);
	if(nConstAddressValue >= 0){
		return bProcessSemanticser;
	}

	// �ڵ�ǰ������ �Ƿ��б�� �������ͬ��(����,����ʧ��)
	int nLabelAddressValue = SymbolTableInst::instance().searchLableInfoTable(nStackTopProcId, pConstTokenWord->m_szContentValue);
	if (nLabelAddressValue >= 0){
		return bProcessSemanticser;
	}

	// �ڵ�ǰ������ �Ƿ���ö�� �������ͬ��(����,����ʧ��)
	int nEnumAddressValue = SymbolTableInst::instance().searchEnumInfoTable(nStackTopProcId, pConstTokenWord->m_szContentValue);
	if(nEnumAddressValue >= 0){
		return bProcessSemanticser;
	}

	// �ڵ�ǰ������ �Ƿ��б��� �������ͬ��(����,����ʧ��)
	int nVarAddressValue = SymbolTableInst::instance().searchVarInfoTable(nStackTopProcId, pConstTokenWord->m_szContentValue);
	if(nVarAddressValue >= 0){
		return bProcessSemanticser;
	}

	// �Ƿ������ͬ��(����,����ʧ��)
	bool bIsSameNameProc = SymbolTableInst::instance().compareProcNameIsSame(pConstTokenWord->m_szContentValue);
	if(true == bIsSameNameProc){
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
