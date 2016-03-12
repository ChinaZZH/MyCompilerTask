#include "LabelStatmentSemanticser.h"
#include "../SymbolTable/LabelInfoTable.h"
#include "../SyntaxParser/SyntaxParser.h"
#include "../Log/LogFile.h"
#include "../GlobalData/WordStreamTable.h"
#include "../SymbolTable/SymbolTable.h"
#include "SemanticsParserMgr.h"

LabelStatementSemanticser::LabelStatementSemanticser()
{

}

LabelStatementSemanticser::~LabelStatementSemanticser()
{

}

// �����������--->  label ��ʶ�� 003 ��������б�
bool LabelStatementSemanticser::processSemanticsParser()
{
	bool bProcessResult = false;
	int nParserWordTableIndex = SyntaxParserInst::instance().getParserWordTableIndex();
	if (nParserWordTableIndex <= 0){
		LogFileInst::instance().logError("LabelStatementSemanticser::processSemanticsParser nParserWordTableIndex error", __FILE__, __LINE__);
		return bProcessResult;
	}

	// �ҵ�const�����ı�ʶ��
	int nLastParserWordIndex = nParserWordTableIndex - 1;
	if (nLastParserWordIndex <= 0){
		LogFileInst::instance().logError("LabelStatementSemanticser::processSemanticsParser nLastParserWordIndex error", __FILE__, __LINE__);
		return bProcessResult;
	}
	
	const CToken* pParserWord = WordStreamTableInst::instance().getWordTokenByTableIndex(nLastParserWordIndex);
	if(NULL == pParserWord){
		LogFileInst::instance().logError("LabelStatementSemanticser::processSemanticsParser pParserWord null", __FILE__, __LINE__);
		return bProcessResult;
	}

	// �ʼ�Ĺ���Id
	ProcStackParserHandler& procStackParserHandler = SemanticsParserMgrInst::instance().getProcStackParserHandler();
	int nStackTopProcId = procStackParserHandler.getTopProcStackProcAddress();
	if(nStackTopProcId < 0){
		LogFileInst::instance().logError("LabelStatementSemanticser::processSemanticsParser getProcStackTop error", __FILE__, __LINE__);
		return bProcessResult;
	}

	// ���ܸ�����������
	bool bCompareProcName = SymbolTableInst::instance().compareToProcName(nStackTopProcId, pParserWord->m_szContentValue);
	if(true == bCompareProcName){
		LogFileInst::instance().logError("LabelStatementSemanticser::processSemanticsParser compareToProcName error", __FILE__, __LINE__);
		return bProcessResult;
	}

	// ��ʼ�������Ϣ
	LabelInfo newLableInfo;
	newLableInfo.initStrName(pParserWord->m_szContentValue);
	newLableInfo.initDefValue(false);
	newLableInfo.initUseValue(false);
	newLableInfo.m_nProcIndex = nStackTopProcId;

	// �Ƿ��Ѿ����ڸñ��(�ӷ��ű�������)
	int nLabelTableIndex = SymbolTableInst::instance().searchLableInfoTable(nStackTopProcId, pParserWord->m_szContentValue);
	if(nLabelTableIndex >= 0){
		LogFileInst::instance().logError("LabelStatementSemanticser::processSemanticsParser searchLableInfoTable error", __FILE__, __LINE__);
		return bProcessResult;
	}

	// �ж���� ������ű���
	SymbolTableInst::instance().addLabelInfo(newLableInfo);
	bProcessResult = true;
	return bProcessResult;
}

eSemansticeParserTypeValue LabelStatementSemanticser::returnSemanticserEnumValue()
{
	return eSemansticeParserTypeValue::eSPEV_LabelStatmentParser;
}
