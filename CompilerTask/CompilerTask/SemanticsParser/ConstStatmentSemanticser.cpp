#include "ConstStatmentSemanticser.h"
#include "../SyntaxParser/SyntaxParser.h"
#include "../Log/LogFile.h"
#include "../SymbolTable/SymbolTable.h"
#include "../GlobalData/WordStreamTable.h"
#include "SemanticsParserMgr.h"

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

	const CToken* pConstWord = this->getTokenWordByLastSomeWordIndex(1);
	if(NULL == pConstWord){
		LogFileInst::instance().logError("ConstStatementSemanticser::processSemanticsParser pConstWord null", __FILE__, __LINE__);
		return bProcessResult;
	}

	const CToken* pIdentifierWord = this->getTokenWordByLastSomeWordIndex(3);
	if(NULL == pIdentifierWord){
		LogFileInst::instance().logError("ConstStatementSemanticser::processSemanticsParser pIdentifierWord null", __FILE__, __LINE__);
		return bProcessResult;
	}

	// �ҳ���ǰ����ִ�еĺ���
	ProcStackParserHandler& procStackParserHandler = SemanticsParserMgrInst::instance().getProcStackParserHandler();
	int nProcStackId = procStackParserHandler.getTopProcStackProcAddress();
	if(nProcStackId < 0){
		LogFileInst::instance().logError("ConstStatementSemanticser::processSemanticsParser getProcStackTop error", __FILE__, __LINE__);
		return bProcessResult;
	}

	// label�����ҵ��� �����ظ�����
	int nLabelTableIndex = SymbolTableInst::instance().searchLableInfoTable(nProcStackId, pIdentifierWord->m_szContentValue);
	if(nLabelTableIndex >= 0){
		LogFileInst::instance().logError("ConstStatementSemanticser::processSemanticsParser searchLableInfoTable error", __FILE__, __LINE__);
		return bProcessResult;
	}

	// const��
	int nConstTableIndex = SymbolTableInst::instance().searchConstInfoTable(nProcStackId, pIdentifierWord->m_szContentValue);
	if(nConstTableIndex >= 0){
		LogFileInst::instance().logError("ConstStatementSemanticser::processSemanticsParser searchConstInfoTable error", __FILE__, __LINE__);
		return bProcessResult;
	}

	// ���ܸ�����������
	bool bCompareProcName = SymbolTableInst::instance().compareToProcName(nProcStackId, pIdentifierWord->m_szContentValue);
	if(true == bCompareProcName){
		LogFileInst::instance().logError("ConstStatementSemanticser::processSemanticsParser compareToProcName error", __FILE__, __LINE__);
		return bProcessResult;
	}


	ConstInfo* pConstInfo = SymbolTableInst::instance().getEmptyConstInfoByName(pConstWord->m_szContentValue);
	if(NULL == pConstInfo){
		LogFileInst::instance().logError("ConstStatementSemanticser::processSemanticsParser createEmptyNewConstInfoByName error", __FILE__, __LINE__);
		return bProcessResult;
	}

	pConstInfo->initStrName(pIdentifierWord->m_szContentValue);
	pConstInfo->initProcIndex(nProcStackId);

	bProcessResult = true;
	return bProcessResult;
}


eSemansticeParserTypeValue ConstStatementSemanticser::returnSemanticserEnumValue()
{
	return eSemansticeParserTypeValue::eSPEV_ConstStatmentParser;
}
