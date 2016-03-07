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

// 常量定义--->  标示符=常量 004
bool ConstStatementSemanticser::processSemanticsParser()
{
	bool bProcessResult = false;
	int nParserWordTableIndex = SyntaxParserInst::instance().getParserWordTableIndex();
	if(nParserWordTableIndex <= 0){
		LogFileInst::instance().logError("ConstStatementSemanticser::processSemanticsParser nParserWordTableIndex error", __FILE__, __LINE__);
		return bProcessResult;
	}

	// 找到const常量的标识符
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

	// 找出当前正在执行的函数
	int nProcStackId = SymbolTableInst::instance().getProcStackTop();
	if(nProcStackId < 0){
		LogFileInst::instance().logError("ConstStatementSemanticser::processSemanticsParser getProcStackTop error", __FILE__, __LINE__);
		return bProcessResult;
	}

	// label表中找到了 不能重复声明
	int nLabelTableIndex = SymbolTableInst::instance().searchLableInfoTable(nProcStackId, pParserWord->m_szContentValue);
	if(nLabelTableIndex >= 0){
		LogFileInst::instance().logError("ConstStatementSemanticser::processSemanticsParser searchLableInfoTable error", __FILE__, __LINE__);
		return bProcessResult;
	}

	// const表
	int nConstTableIndex = SymbolTableInst::instance().searchConstInfoTable(nProcStackId, pParserWord->m_szContentValue);
	if(nConstTableIndex >= 0){
		LogFileInst::instance().logError("ConstStatementSemanticser::processSemanticsParser searchConstInfoTable error", __FILE__, __LINE__);
		return bProcessResult;
	}

	// 不能跟过程名重名
	bool bCompareProcName = SymbolTableInst::instance().compareToProcName(nProcStackId, pParserWord->m_szContentValue);
	if(true == bCompareProcName){
		LogFileInst::instance().logError("ConstStatementSemanticser::processSemanticsParser compareToProcName error", __FILE__, __LINE__);
		return bProcessResult;
	}

	// 判断该过程是否有该常量 空间已经申请好了 从对应的const管理器中读取对应的空间
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
