#include "SyntaxParser.h"
#include "../GlobalData/LexParseGlobalDataDef.h"
#include "../GlobalData/WordStreamTable.h"
#include "../Log/LogFile.h"
#include "../GlobalData/SyntaxParserTable.h"
#include "../SemanticsParser/SemanticsParserMgr.h"



SyntaxParser::SyntaxParser()
:m_nParserWordTableIndex(0)
{
	// �쳣״̬
	SSyntaxParserHandler errorSymbol;
	errorSymbol.m_handleSyntaxParser = &SyntaxParser::handleErrorSymbolSyntaxParser;
	m_mapSyntaxParserHandler[eSPHT_ErrorSymbol] = errorSymbol;

	// ���ַ�
	SSyntaxParserHandler nullSymbol;
	nullSymbol.m_handleSyntaxParser = &SyntaxParser::handleNullSymbolSyntaxParser;
	m_mapSyntaxParserHandler[eSPHT_NullSymbol] = nullSymbol;

	// �ս��
	SSyntaxParserHandler terminalSymbol;
	terminalSymbol.m_handleSyntaxParser = &SyntaxParser::handleTerminalSymbolSyntaxParser;
	m_mapSyntaxParserHandler[eSPHT_TerminalSymbol] = terminalSymbol;

	// ���ս��
	SSyntaxParserHandler noTerminalSymbol;
	noTerminalSymbol.m_handleSyntaxParser = &SyntaxParser::handleNoTerminalSyntaxParser;
	m_mapSyntaxParserHandler[eSPHT_NoTerminalSymbol] = noTerminalSymbol;

	// ����
	SSyntaxParserHandler semanticSymbol;
	semanticSymbol.m_handleSyntaxParser = &SyntaxParser::handleSemanticsSyntaxParser;
	m_mapSyntaxParserHandler[eSPHT_Semantics] = semanticSymbol;
}

SyntaxParser::~SyntaxParser()
{

}

bool SyntaxParser::processSyntaxParse()
{
	bool bProcessResult = false;
	
	// �﷨
	this->clearSyntaxStack();
	m_nParserWordTableIndex = 0;
	m_stackSyntaxParser.push(eSLV_StartSyntaxParser);
	while(1){
		// ��������Ϊ��
		if(true == m_stackSyntaxParser.empty()){
			break;
		}

		// ��������ȡ����
		const CToken* pWordToken = WordStreamTableInst::instance().getWordTokenByTableIndex(m_nParserWordTableIndex);
		if(NULL == pWordToken){
			LogFileInst::instance().logError("SyntaxParser::processSyntaxParse pWordToken null", __FILE__, __LINE__);
			return bProcessResult;
		}

		int nStackElement = this->popTopValueParserStack();
		eSyntaxParserHandlerTag handlerTag = this->getSyntaxHandlerByValue(nStackElement);

		SyntaxParserHandlerMap::iterator itr = m_mapSyntaxParserHandler.find(handlerTag);
		if(itr == m_mapSyntaxParserHandler.end()){
			LogFileInst::instance().logError("SyntaxParser::processSyntaxParse handler error", __FILE__, __LINE__);
			return bProcessResult;
		}

		_HandleSyntaxParserStatus& handlerSyntaxParser = (itr->second).m_handleSyntaxParser;
		bool bProcessSyntax = (this->*handlerSyntaxParser)(nStackElement, pWordToken);
		if(false == bProcessSyntax){
			LogFileInst::instance().logError("SyntaxParser::processSyntaxParse parser error", __FILE__, __LINE__);
			return bProcessResult;
		}
	}

	// ���е������ĵ��ʻ�û�з�����
	int nMaxWordNum = WordStreamTableInst::instance().getMaxWordNumInTable();
	if(m_nParserWordTableIndex < nMaxWordNum){
		LogFileInst::instance().logError("SyntaxParser::processSyntaxParse SynataxParser error", __FILE__, __LINE__);
		return bProcessResult;
	}

	// �﷨������ȷ
	bProcessResult = false;
	return bProcessResult;
}

void SyntaxParser::clearSyntaxStack()
{
	while(false == m_stackSyntaxParser.empty()){
		m_stackSyntaxParser.pop();
	}
}


int SyntaxParser::popTopValueParserStack()
{
	int nElementValue = m_stackSyntaxParser.top();
	m_stackSyntaxParser.pop();
	return nElementValue;
}


bool SyntaxParser::pushValueToParserStack(const std::string& strProductValue)
{
	bool bPushValueResult = false;
	if(true == strProductValue.empty()){
		LogFileInst::instance().logError("SyntaxParser::pushValueToParserStack strProductValue null", __FILE__, __LINE__);
		return bPushValueResult;
	}

	for(int i = strProductValue.length() - 3; i >= 0; i = i -3){
		int nNewElementValue = atoi(strProductValue.substr(i, 3).c_str());
		m_stackSyntaxParser.push(nNewElementValue);
	}

	bPushValueResult = true;
	return bPushValueResult;
}

eSyntaxParserHandlerTag SyntaxParser::getSyntaxHandlerByValue(int nStackElementValue)
{
	if(nStackElementValue < 0){
		return eSPHT_ErrorSymbol;
	}

	if(0 == nStackElementValue){
		return eSPHT_NullSymbol;
	}

	if(nStackElementValue < eSLV_StartSyntaxParser){
		return eSPHT_TerminalSymbol;
	}

	if((nStackElementValue >= eSLV_StartSyntaxParser) && (nStackElementValue < eSLV_SemanticsParserStart)){
		return eSPHT_NoTerminalSymbol;
	}

	if(nStackElementValue >= eSLV_SemanticsParserStart){
		return eSPHT_Semantics;
	}

	return eSPHT_NullSymbol;
}


bool SyntaxParser::handleErrorSymbolSyntaxParser(int nStackElementValue, const CToken* pWordToken)
{
	bool bHandleProcess = false;
	if(nStackElementValue < 0){
		return bHandleProcess;
	}

	LogFileInst::instance().logError("SyntaxParser::handleErrorSymbolSyntaxParser �������߼����� ��Ӧ�õ��øú���", __FILE__, __LINE__);
	return bHandleProcess;
}

bool SyntaxParser::handleNullSymbolSyntaxParser(int nStackElementValue, const CToken* pWordToken)
{
	bool bHandleProcess = false;
	if(0 != nStackElementValue){
		LogFileInst::instance().logError("SyntaxParser::handleNullSymbolSyntaxParser �������߼����� ��Ӧ�õ��øú���", __FILE__, __LINE__);
		return bHandleProcess;
	}

	bHandleProcess = true;
	return bHandleProcess;
}

bool SyntaxParser::handleTerminalSymbolSyntaxParser(int nStackElementValue, const CToken* pWordToken)
{
	bool bHandleProcess = false;
	if((nStackElementValue >= eSLV_StartSyntaxParser) || (nStackElementValue <= 0)){
		LogFileInst::instance().logError("SyntaxParser::handleTerminalSymbolSyntaxParser �������߼����� ��Ӧ�õ��øú���", __FILE__, __LINE__);
		return bHandleProcess;
	}

	if(NULL == pWordToken){
		LogFileInst::instance().logError("SyntaxParser::handleTerminalSymbolSyntaxParser pWordToken null", __FILE__, __LINE__);
		return bHandleProcess;
	}

	if(pWordToken->m_nWordStatus != nStackElementValue){
		LogFileInst::instance().logError("SyntaxParser::processSyntaxParse Դ�����ս�� error", __FILE__, __LINE__);
		return bHandleProcess;
	}

	// ����
	m_nParserWordTableIndex = m_nParserWordTableIndex + 1;
	bHandleProcess = true;
	return bHandleProcess;
}

bool SyntaxParser::handleNoTerminalSyntaxParser(int nStackElementValue, const CToken* pWordToken)
{
	bool bHandleProcess = false;
	if((nStackElementValue < eSLV_StartSyntaxParser) || (nStackElementValue >= eSLV_SemanticsParserStart)){
		LogFileInst::instance().logError("SyntaxParser::handleNoTerminalSyntaxParser �������߼����� ��Ӧ�õ��øú���", __FILE__, __LINE__);
		return bHandleProcess;
	}

	if(NULL == pWordToken){
		LogFileInst::instance().logError("SyntaxParser::handleNoTerminalSyntaxParser pWordToken null", __FILE__, __LINE__);
		return bHandleProcess;
	}

	int nSynatxParserRow = nStackElementValue - eSLV_StartSyntaxParser;
	int nSynatxParserCol = pWordToken->m_nWordStatus;

	bool bCheckCorrectStatus = SyntaxParserTableInst::instance().checkIsCorrectProduct(nSynatxParserRow, nSynatxParserCol);
	if(false == bCheckCorrectStatus){
		LogFileInst::instance().logError("SyntaxParser::handleNoTerminalSyntaxParser ���ս������ error", __FILE__, __LINE__);
		return bHandleProcess;
	}
	
	int nProductId = SyntaxParserTableInst::instance().getProductFromParserTable(nSynatxParserRow, nSynatxParserCol);
	std::string strProductValue = SyntaxParserTableInst::instance().getProductById(nProductId);
	if(true == strProductValue.empty()){
		LogFileInst::instance().logError("SyntaxParser::handleNoTerminalSyntaxParser ���ս������ error strProductValue null", __FILE__, __LINE__);
		return bHandleProcess;
	}

	this->pushValueToParserStack(strProductValue);
	bHandleProcess = true;
	return bHandleProcess;
}

bool SyntaxParser::handleSemanticsSyntaxParser(int nStackElementValue, const CToken* pWordToken)
{
	bool bHandleProcess = false;
	if(nStackElementValue < eSLV_SemanticsParserStart){
		LogFileInst::instance().logError("SyntaxParser::handleSemanticsSyntaxParser �������߼����� ��Ӧ�õ��øú���", __FILE__, __LINE__);
		return bHandleProcess;
	}

	bHandleProcess = SemanticsParserMgrInst::instance().processSemanticsParser(nStackElementValue);
	if(false == bHandleProcess){
		LogFileInst::instance().logError("SyntaxParser::handleSemanticsSyntaxParser �����������", __FILE__, __LINE__);
		return bHandleProcess;
	}

	bHandleProcess = true;
	return bHandleProcess;
}