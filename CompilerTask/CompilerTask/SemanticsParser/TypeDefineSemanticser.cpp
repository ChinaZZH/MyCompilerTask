#include "TypeDefineSemanticser.h"
#include "../SyntaxParser/SyntaxParser.h"
#include "../Log/LogFile.h"
#include "../GlobalData/WordStreamTable.h"
#include "SemanticsParserMgr.h"
#include "../SymbolTable/SymbolTable.h"

TypeDefineSemanticser::TypeDefineSemanticser()
{

}

TypeDefineSemanticser::~TypeDefineSemanticser()
{

}

// 类型定义---> 标识符 006 = 类型
eSemansticeParserTypeValue TypeDefineSemanticser::returnSemanticserEnumValue()
{
	return eSemansticeParserTypeValue::eSPEV_TypeDefineParser;
}

// 类型定义---> 标识符 006 = 类型
bool TypeDefineSemanticser::processSemanticsParser()
{
	bool bProcessSemanticser = false;

	// 获得单词的下标值
	int nParserWordIndex = SyntaxParserInst::instance().getParserWordTableIndex();
	nParserWordIndex = nParserWordIndex - 1;
	if(nParserWordIndex < 0){
		LogFileInst::instance().logError("TypeDefineSemanticser::processSemanticsParser nParserWordIndex error", __FILE__, __LINE__);
		return bProcessSemanticser;
	}

	// 从单词流表中获取对应的单词
	const CToken* pConstTokenWord = WordStreamTableInst::instance().getWordTokenByTableIndex(nParserWordIndex);
	if(NULL == pConstTokenWord){
		LogFileInst::instance().logError("TypeDefineSemanticser::processSemanticsParser pConstTokenWord null", __FILE__, __LINE__);
		return bProcessSemanticser;
	}

	// 正在分析的过程Id
	ProcStackParserHandler& procStackParserHandler = SemanticsParserMgrInst::instance().getProcStackParserHandler();
	int nStackTopProcId = procStackParserHandler.getTopProcStackProcAddress();
	if(nStackTopProcId < 0){
		LogFileInst::instance().logError("TypeDefineSemanticser::processSemanticsParser getProcStackTop error", __FILE__, __LINE__);
		return bProcessSemanticser;
	}

	// 放在基类 然后回调
	bool bCompareWordValue = this->checkCompareIsSameNameWithWord(nStackTopProcId, pConstTokenWord->m_szContentValue);
	if(true == bCompareWordValue){
		return bProcessSemanticser;
	}

	// 放入类型表中
	int nTypeUserInfoMaxAddress = SymbolTableInst::instance().addNewUserTypeInfoToTable(pConstTokenWord->m_szContentValue, nStackTopProcId);
	if (nTypeUserInfoMaxAddress < 0){
		LogFileInst::instance().logError("VarDefineAfterListSemanticser::processSemanticsParser nTypeUserInfoMaxAddress error", __FILE__, __LINE__);
		return bProcessSemanticser;
	}

	// 类型节点分析处理器
	TypePositionParseHandler& typeInfoPositionHandler = SemanticsParserMgrInst::instance().getTypePositionParseHandler();
	typeInfoPositionHandler.addProcessingTypeInfoAddress(nTypeUserInfoMaxAddress);

	bProcessSemanticser = true;
	return bProcessSemanticser;
}



