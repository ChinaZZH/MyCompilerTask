#include "MainProgramHeaderStatementSemanticser.h"
#include "../SymbolTable/ProcInfoTable.h"
#include "../Log/LogFile.h"
#include "../SyntaxParser/SyntaxParser.h"
#include "../GlobalData/WordStreamTable.h"
#include "../SymbolTable/SymbolTable.h"
#include "SemanticsParserMgr.h"

MainProgramHeaderStatementSemanticser::MainProgramHeaderStatementSemanticser()
{

}

MainProgramHeaderStatementSemanticser::~MainProgramHeaderStatementSemanticser()
{

}

// ����ͷ---> program ��ʶ�� 001(��ʶ���б�)
bool MainProgramHeaderStatementSemanticser::processSemanticsParser()
{
	bool bProcessParserResult = false;
	bool bInitSemanticserResult = this->initBeforeSemanticserStart();
	if(false == bInitSemanticserResult){
		LogFileInst::instance().logError("MainProgramHeaderStatementSemanticser::processSemanticsParser initBeforeSemanticserStart error", __FILE__, __LINE__);
		return bProcessParserResult;
	}

	// �ҵ�ǰһ����ʶ��
	int nParserWordTableIndex = SyntaxParserInst::instance().getParserWordTableIndex();
	if(nParserWordTableIndex <= 0){
		LogFileInst::instance().logError("MainProgramHeaderStatementSemanticser::processSemanticsParser nParserWordTableIndex error", __FILE__, __LINE__);
		return bProcessParserResult;
	}

	// �ҵ�const�����ı�ʶ��
	int nLastParserWordIndex = nParserWordTableIndex - 1;
	if(nLastParserWordIndex <= 0){
		LogFileInst::instance().logError("MainProgramHeaderStatementSemanticser::processSemanticsParser nLastParserWordIndex error", __FILE__, __LINE__);
		return bProcessParserResult;
	}

	// �Ӵʷ������еõ��� ���ʼ�  ��ȥ�� ��Ӧ�ĵ���
	const CToken* pParserWord = WordStreamTableInst::instance().getWordTokenByTableIndex(nLastParserWordIndex);
	if(NULL == pParserWord){
		LogFileInst::instance().logError("MainProgramHeaderStatementSemanticser::processSemanticsParser pParserWord null", __FILE__, __LINE__);
		return bProcessParserResult;
	}

	SemanticsParserMgrInst::instance().clearAllData();

	// �����µ�һ������
	ProcInfo newProcInfo;
	newProcInfo.m_strProcName = pParserWord->m_szContentValue;
	newProcInfo.m_eRankValue = ProcInfo::Rank::Main;
	newProcInfo.m_eType = ProcInfo::Type::Procedure;
	newProcInfo.m_ParaTable.clear();

	// ���ù��̷�����ű���
	int nProcIndexAddress = SymbolTableInst::instance().addNewProcInfo(newProcInfo);

	// �������ջ��
	ProcStackParserHandler& procStackParserHandler = SemanticsParserMgrInst::instance().getProcStackParserHandler();
	procStackParserHandler.newProcCallAddToStack(nProcIndexAddress);

	// ��ʶ����ʶ ������
	IdentifierListFlagHandler& identifierListHandler = SemanticsParserMgrInst::instance().getIdentifierListFlagHandler();
	identifierListHandler.startNewSemanticserParserFlag(eSPIF_MainProgramIdentifierListStart);

	// ���ͱ�־ ������
	TypeFlagHandler& typeFlagHandler = SemanticsParserMgrInst::instance().getTypeFlagHandler();
	typeFlagHandler.pushTypeFlagValueToStack(eTFEV_MainTypeValue);

	bProcessParserResult = true;
	return bProcessParserResult;
}

eSemansticeParserTypeValue MainProgramHeaderStatementSemanticser::returnSemanticserEnumValue()
{
	return eSemansticeParserTypeValue::eSPEV_MainProgramHeaderStatementParser;
}


bool MainProgramHeaderStatementSemanticser::initBeforeSemanticserStart()
{
	return true;
}