#include "SyntaxParser.h"
#include "../GlobalData/LexParseGlobalDataDef.h"
#include "../GlobalData/WordStreamTable.h"
#include "../Log/LogFile.h"
#include "../GlobalData/SyntaxParserTable.h"
#include "../SemanticsParser/SemanticsParserMgr.h"



SyntaxParser::SyntaxParser()
:m_nParserWordTableIndex(0)
{
	// 异常状态
	SSyntaxParserHandler errorSymbol;
	errorSymbol.m_handleSyntaxParser = &SyntaxParser::handleErrorSymbolSyntaxParser;
	m_mapSyntaxParserHandler[eSPHT_ErrorSymbol] = errorSymbol;

	// 空字符
	SSyntaxParserHandler nullSymbol;
	nullSymbol.m_handleSyntaxParser = &SyntaxParser::handleNullSymbolSyntaxParser;
	m_mapSyntaxParserHandler[eSPHT_NullSymbol] = nullSymbol;

	// 终结符
	SSyntaxParserHandler terminalSymbol;
	terminalSymbol.m_handleSyntaxParser = &SyntaxParser::handleTerminalSymbolSyntaxParser;
	m_mapSyntaxParserHandler[eSPHT_TerminalSymbol] = terminalSymbol;

	// 非终结符
	SSyntaxParserHandler noTerminalSymbol;
	noTerminalSymbol.m_handleSyntaxParser = &SyntaxParser::handleNoTerminalSyntaxParser;
	m_mapSyntaxParserHandler[eSPHT_NoTerminalSymbol] = noTerminalSymbol;

	// 语义
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
	
	// 语法
	this->clearSyntaxStack();
	m_nParserWordTableIndex = 0;
	m_stackSyntaxParser.push(eSLV_StartSyntaxParser);
	while(1){
		// 分析队列为空
		if(true == m_stackSyntaxParser.empty()){
			break;
		}

		// 单词流读取不到
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

	// 还有单词流的单词还没有分析完
	int nMaxWordNum = WordStreamTableInst::instance().getMaxWordNumInTable();
	if(m_nParserWordTableIndex < nMaxWordNum){
		LogFileInst::instance().logError("SyntaxParser::processSyntaxParse SynataxParser error", __FILE__, __LINE__);
		return bProcessResult;
	}

	// 语法分析正确
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

	LogFileInst::instance().logError("SyntaxParser::handleErrorSymbolSyntaxParser 服务器逻辑出错 不应该调用该函数", __FILE__, __LINE__);
	return bHandleProcess;
}

bool SyntaxParser::handleNullSymbolSyntaxParser(int nStackElementValue, const CToken* pWordToken)
{
	bool bHandleProcess = false;
	if(0 != nStackElementValue){
		LogFileInst::instance().logError("SyntaxParser::handleNullSymbolSyntaxParser 服务器逻辑出错 不应该调用该函数", __FILE__, __LINE__);
		return bHandleProcess;
	}

	bHandleProcess = true;
	return bHandleProcess;
}

bool SyntaxParser::handleTerminalSymbolSyntaxParser(int nStackElementValue, const CToken* pWordToken)
{
	bool bHandleProcess = false;
	if((nStackElementValue >= eSLV_StartSyntaxParser) || (nStackElementValue <= 0)){
		LogFileInst::instance().logError("SyntaxParser::handleTerminalSymbolSyntaxParser 服务器逻辑出错 不应该调用该函数", __FILE__, __LINE__);
		return bHandleProcess;
	}

	if(NULL == pWordToken){
		LogFileInst::instance().logError("SyntaxParser::handleTerminalSymbolSyntaxParser pWordToken null", __FILE__, __LINE__);
		return bHandleProcess;
	}

	if(pWordToken->m_nWordStatus != nStackElementValue){
		LogFileInst::instance().logError("SyntaxParser::processSyntaxParse 源程序终结符 error", __FILE__, __LINE__);
		return bHandleProcess;
	}

	// 设置
	m_nParserWordTableIndex = m_nParserWordTableIndex + 1;
	bHandleProcess = true;
	return bHandleProcess;
}

bool SyntaxParser::handleNoTerminalSyntaxParser(int nStackElementValue, const CToken* pWordToken)
{
	bool bHandleProcess = false;
	if((nStackElementValue < eSLV_StartSyntaxParser) || (nStackElementValue >= eSLV_SemanticsParserStart)){
		LogFileInst::instance().logError("SyntaxParser::handleNoTerminalSyntaxParser 服务器逻辑出错 不应该调用该函数", __FILE__, __LINE__);
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
		LogFileInst::instance().logError("SyntaxParser::handleNoTerminalSyntaxParser 非终结符出错 error", __FILE__, __LINE__);
		return bHandleProcess;
	}
	
	int nProductId = SyntaxParserTableInst::instance().getProductFromParserTable(nSynatxParserRow, nSynatxParserCol);
	std::string strProductValue = SyntaxParserTableInst::instance().getProductById(nProductId);
	if(true == strProductValue.empty()){
		LogFileInst::instance().logError("SyntaxParser::handleNoTerminalSyntaxParser 非终结符出错 error strProductValue null", __FILE__, __LINE__);
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
		LogFileInst::instance().logError("SyntaxParser::handleSemanticsSyntaxParser 服务器逻辑出错 不应该调用该函数", __FILE__, __LINE__);
		return bHandleProcess;
	}

	bHandleProcess = SemanticsParserMgrInst::instance().processSemanticsParser(nStackElementValue);
	if(false == bHandleProcess){
		LogFileInst::instance().logError("SyntaxParser::handleSemanticsSyntaxParser 语义分析出错", __FILE__, __LINE__);
		return bHandleProcess;
	}

	bHandleProcess = true;
	return bHandleProcess;
}