#include "ConstStatmentSemanticser.h"
#include "../SyntaxParser/SyntaxParser.h"
#include "../Log/LogFile.h"
#include "../SymbolTable/SymbolTable.h"
#include "../GlobalData/WordStreamTable.h"

ConstStatementSemanticser::ConstStatementSemanticser()
{

}

ConstStatementSemanticser::~ConstStatementSemanticser()
{

}

// ��������--->  ��ʾ��=���� 004
bool ConstStatementSemanticser::processSemanticsParser()
{
	bool bProcessResult = false;
	int nParserWordTableIndex = SyntaxParserInst::instance().getParserWordTableIndex();
	if(nParserWordTableIndex <= 0){
		LogFileInst::instance().logError("ConstStatementSemanticser::processSemanticsParser nParserWordTableIndex error", __FILE__, __LINE__);
		return bProcessResult;
	}

	// �ҵ�const�����ı�ʶ��
	int nLastParserWordIndex = nParserWordTableIndex - 3;
	if(nLastParserWordIndex <= 0){
		LogFileInst::instance().logError("ConstStatementSemanticser::processSemanticsParser nLastParserWordIndex error", __FILE__, __LINE__);
		return bProcessResult;
	}

	const CToken* pParserWord = WordStreamTableInst::instance().getWordTokenByTableIndex(nLastParserWordIndex);
	if(NULL == pParserWord){
		LogFileInst::instance().logError("ConstStatementSemanticser::processSemanticsParser pParserWord null", __FILE__, __LINE__);
		return bProcessResult;
	}

	// �ҳ���ǰ����ִ�еĺ���
	int nProcStackId = SymbolTableInst::instance().getProcStackTop();
	if(nProcStackId < 0){
		LogFileInst::instance().logError("ConstStatementSemanticser::processSemanticsParser getProcStackTop error", __FILE__, __LINE__);
		return bProcessResult;
	}

	// label�����ҵ��� �����ظ�����
	int nLabelTableIndex = SymbolTableInst::instance().searchLableInfoTable(nProcStackId, pParserWord->m_szContentValue);
	if(nLabelTableIndex >= 0){
		LogFileInst::instance().logError("ConstStatementSemanticser::processSemanticsParser searchLableInfoTable error", __FILE__, __LINE__);
		return bProcessResult;
	}

	// const��
	int nConstTableIndex = SymbolTableInst::instance().searchConstInfoTable(nProcStackId, pParserWord->m_szContentValue);
	if(nConstTableIndex >= 0){
		LogFileInst::instance().logError("ConstStatementSemanticser::processSemanticsParser searchConstInfoTable error", __FILE__, __LINE__);
		return bProcessResult;
	}

	// ���ܸ�����������
	bool bCompareProcName = SymbolTableInst::instance().compareToProcName(nProcStackId, pParserWord->m_szContentValue);
	if(true == bCompareProcName){
		LogFileInst::instance().logError("ConstStatementSemanticser::processSemanticsParser compareToProcName error", __FILE__, __LINE__);
		return bProcessResult;
	}

	// �жϸù����Ƿ��иó��� �ռ��Ѿ�������� �Ӷ�Ӧ��const�������ж�ȡ��Ӧ�Ŀռ�
	int nConstIndex = nParserWordTableIndex - 1;
	const CToken* pGetEmptyConstWord = WordStreamTableInst::instance().getWordTokenByTableIndex(nConstIndex);
	if(NULL == pGetEmptyConstWord){
		LogFileInst::instance().logError("ConstStatementSemanticser::processSemanticsParser pGetEmptyConstWord null", __FILE__, __LINE__);
		return bProcessResult;
	}

	ConstInfo* pConstInfo = SymbolTableInst::instance().getEmptyConstInfoByName(pGetEmptyConstWord->m_szContentValue);
	if(NULL == pConstInfo){
		LogFileInst::instance().logError("ConstStatementSemanticser::processSemanticsParser createEmptyNewConstInfoByName error", __FILE__, __LINE__);
		return bProcessResult;
	}

	pConstInfo->initStrName(pParserWord->m_szContentValue);
	pConstInfo->initProcIndex(nProcStackId);

	bProcessResult = true;
	return bProcessResult;
}


eSemansticeParserEnumValue ConstStatementSemanticser::returnSemanticserEnumValue()
{
	return eSPEV_ConstStatmentParser;
}
