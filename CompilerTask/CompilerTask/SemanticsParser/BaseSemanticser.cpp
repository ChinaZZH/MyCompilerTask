#include "BaseSemanticser.h"
#include <string>
#include "../SymbolTable/SymbolTable.h"
#include "../SyntaxParser/SyntaxParser.h"
#include "../Log/LogFile.h"
#include "../GlobalData/WordStreamTable.h"


BaseSemanticser::BaseSemanticser()
{

}

BaseSemanticser::~BaseSemanticser()
{

}

bool BaseSemanticser::processSemanticsParser()
{
	return true;
}



eSemansticeParserTypeValue BaseSemanticser::returnSemanticserEnumValue()
{
	return eSPEV_NullParser;
}

bool BaseSemanticser::checkCompareIsSameNameWithWord(int nStackTopProcId, const std::string& strWordValue)
{
	bool bSameName = true;

	// 是否跟类型表信息表中的类型同名
	int nTypeInfoAddressValue = SymbolTableInst::instance().searchTypeInfoTable(nStackTopProcId, strWordValue);
	if (nTypeInfoAddressValue >= 0){
		return bSameName;
	}

	// 在当前函数内 是否有常量跟其变量同名(存在,则定义失败)
	int nConstAddressValue = SymbolTableInst::instance().searchConstInfoTable(nStackTopProcId, strWordValue);
	if (nConstAddressValue >= 0){
		return bSameName;
	}

	// 在当前函数内 是否有标号 跟其变量同名(存在,则定义失败)
	int nLabelAddressValue = SymbolTableInst::instance().searchLableInfoTable(nStackTopProcId, strWordValue);
	if (nLabelAddressValue >= 0){
		return bSameName;
	}

	// 在当前函数内 是否有枚举 跟其变量同名(存在,则定义失败)
	int nEnumAddressValue = SymbolTableInst::instance().searchEnumInfoTable(nStackTopProcId, strWordValue);
	if (nEnumAddressValue >= 0){
		return bSameName;
	}

	// 在当前函数内 是否有变量 跟其变量同名(存在,则定义失败)
	int nVarAddressValue = SymbolTableInst::instance().searchVarInfoTable(nStackTopProcId, strWordValue);
	if (nVarAddressValue >= 0){
		return bSameName;
	}

	// 是否跟过程同名(存在,则定义失败)
	bool bIsSameNameProc = SymbolTableInst::instance().compareProcNameIsSame(strWordValue);
	if (true == bIsSameNameProc){
		return bSameName;
	}

	bSameName = false;
	return bSameName;
}

const CToken* BaseSemanticser::getTokenWordByCurrentWordIndex()
{
	const CToken* pWordToken = this->getTokenWordByLastSomeWordIndex(0);
	return pWordToken;
}


const CToken* BaseSemanticser::getTokenWordByLastWordIndex()
{
	const CToken* pWordToken = this->getTokenWordByLastSomeWordIndex(1);
	return pWordToken;
}


const CToken* BaseSemanticser::getTokenWordByLastSomeWordIndex(int nLastWordIndex)
{
	int nParserWordTableIndex = SyntaxParserInst::instance().getParserWordTableIndex();
	if(nParserWordTableIndex <= 0){
		LogFileInst::instance().logError("BaseSemanticser::getTokenWordByLastSomeWordIndex nParserWordTableIndex error", __FILE__, __LINE__);
		return NULL;
	}

	// 标识符列表标识符
	int nLastParserWordIndex = nParserWordTableIndex - nLastWordIndex;
	if(nLastParserWordIndex <= 0){
		LogFileInst::instance().logError("BaseSemanticser::getTokenWordByLastSomeWordIndex nLastParserWordIndex error", __FILE__, __LINE__);
		return NULL;
	}

	// 从词法分析中得到的 单词集  中去朝 对应的单词
	const CToken* pParserWord = WordStreamTableInst::instance().getWordTokenByTableIndex(nLastParserWordIndex);
	if(NULL == pParserWord){
		LogFileInst::instance().logError("BaseSemanticser::getTokenWordByLastSomeWordIndex pParserWord null", __FILE__, __LINE__);
		return NULL;
	}

	return pParserWord;
}