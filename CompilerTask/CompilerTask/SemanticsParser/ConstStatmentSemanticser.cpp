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

// 常量定义--->  标示符=常量 004
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

	// 找出当前正在执行的函数
	ProcStackParserHandler& procStackParserHandler = SemanticsParserMgrInst::instance().getProcStackParserHandler();
	int nProcStackId = procStackParserHandler.getTopProcStackProcAddress();
	if(nProcStackId < 0){
		LogFileInst::instance().logError("ConstStatementSemanticser::processSemanticsParser getProcStackTop error", __FILE__, __LINE__);
		return bProcessResult;
	}

	// label表中找到了 不能重复声明
	int nLabelTableIndex = SymbolTableInst::instance().searchLableInfoTable(nProcStackId, pIdentifierWord->m_szContentValue);
	if(nLabelTableIndex >= 0){
		LogFileInst::instance().logError("ConstStatementSemanticser::processSemanticsParser searchLableInfoTable error", __FILE__, __LINE__);
		return bProcessResult;
	}

	// const表
	int nConstTableIndex = SymbolTableInst::instance().searchConstInfoTable(nProcStackId, pIdentifierWord->m_szContentValue);
	if(nConstTableIndex >= 0){
		LogFileInst::instance().logError("ConstStatementSemanticser::processSemanticsParser searchConstInfoTable error", __FILE__, __LINE__);
		return bProcessResult;
	}

	// 不能跟过程名重名
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
