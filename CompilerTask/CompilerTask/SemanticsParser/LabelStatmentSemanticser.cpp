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

// 标号声明部分--->  label 标识符 003 标号声明列表
bool LabelStatementSemanticser::processSemanticsParser()
{
	bool bProcessResult = false;
	int nParserWordTableIndex = SyntaxParserInst::instance().getParserWordTableIndex();
	if (nParserWordTableIndex <= 0){
		LogFileInst::instance().logError("LabelStatementSemanticser::processSemanticsParser nParserWordTableIndex error", __FILE__, __LINE__);
		return bProcessResult;
	}

	// 找到const常量的标识符
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

	// 最开始的过程Id
	ProcStackParserHandler& procStackParserHandler = SemanticsParserMgrInst::instance().getProcStackParserHandler();
	int nStackTopProcId = procStackParserHandler.getTopProcStackProcAddress();
	if(nStackTopProcId < 0){
		LogFileInst::instance().logError("LabelStatementSemanticser::processSemanticsParser getProcStackTop error", __FILE__, __LINE__);
		return bProcessResult;
	}

	// 不能跟过程名重名
	bool bCompareProcName = SymbolTableInst::instance().compareToProcName(nStackTopProcId, pParserWord->m_szContentValue);
	if(true == bCompareProcName){
		LogFileInst::instance().logError("LabelStatementSemanticser::processSemanticsParser compareToProcName error", __FILE__, __LINE__);
		return bProcessResult;
	}

	// 初始化标号信息
	LabelInfo newLableInfo;
	newLableInfo.initStrName(pParserWord->m_szContentValue);
	newLableInfo.initDefValue(false);
	newLableInfo.initUseValue(false);
	newLableInfo.m_nProcIndex = nStackTopProcId;

	// 是否已经存在该标号(从符号表中搜索)
	int nLabelTableIndex = SymbolTableInst::instance().searchLableInfoTable(nStackTopProcId, pParserWord->m_szContentValue);
	if(nLabelTableIndex >= 0){
		LogFileInst::instance().logError("LabelStatementSemanticser::processSemanticsParser searchLableInfoTable error", __FILE__, __LINE__);
		return bProcessResult;
	}

	// 判断完成 放入符号表中
	SymbolTableInst::instance().addLabelInfo(newLableInfo);
	bProcessResult = true;
	return bProcessResult;
}

eSemansticeParserTypeValue LabelStatementSemanticser::returnSemanticserEnumValue()
{
	return eSemansticeParserTypeValue::eSPEV_LabelStatmentParser;
}
