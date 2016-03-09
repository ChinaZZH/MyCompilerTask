#include "IdentifierDefineListSemanticser.h"
#include "SemanticsParserMgr.h"
#include "../SymbolTable/SymbolTable.h"
#include "../Log/LogFile.h"
#include "../SyntaxParser/SyntaxParser.h"
#include "../GlobalData/WordStreamTable.h"

IdentifierDefineListSemanticser::IdentifierDefineListSemanticser()
{

}

IdentifierDefineListSemanticser::~IdentifierDefineListSemanticser()
{

}

bool IdentifierDefineListSemanticser::processSemanticsParser()
{
	bool bProcessSemanticser = false;
	SemanticsParserIdFlag&  flagIdStack = SemanticsParserMgrInst::instance().getSemanticsParserIdFlag();
	eSemanticsStackIdFlag flagId = flagIdStack.getCurrentSemanticsParserId();
	switch(flagId){
	case eSPIF_VarIdentifierListStart:
		bProcessSemanticser = this->processVarIdentifierList();
		break;

	default:
		bProcessSemanticser = true;
		break;
	}
	

	return bProcessSemanticser;
}

// 标识符列表->标识符 012 标识符列表1    标识符列表1->, 标识符 012 标识符列表1
eSemansticeParserEnumValue IdentifierDefineListSemanticser::returnSemanticserEnumValue()
{
	return eSPEV_VarIdentifierDefineList;
}

// 标识符列表->标识符 012 标识符列表1    标识符列表1->, 标识符 012 标识符列表1
bool IdentifierDefineListSemanticser::processVarIdentifierList()
{
	bool bProcessSemanticser = false;

	int nParserWordIndex = SyntaxParserInst::instance().getParserWordTableIndex();
	nParserWordIndex = nParserWordIndex - 1;
	if(nParserWordIndex < 0){
		LogFileInst::instance().logError("IdentifierDefineListSemanticser::processVarIdentifierList nParserWordIndex error", __FILE__, __LINE__);
		return bProcessSemanticser;
	}

	// 从单词流表中获取对应的单词
	const CToken* pConstTokenWord = WordStreamTableInst::instance().getWordTokenByTableIndex(nParserWordIndex);
	if(NULL == pConstTokenWord){
		LogFileInst::instance().logError("IdentifierDefineListSemanticser::processVarIdentifierList pConstTokenWord null", __FILE__, __LINE__);
		return bProcessSemanticser;
	}

	// 正在分析的过程Id
	int nStackTopProcId = SymbolTableInst::instance().getProcStackTop();
	if(nStackTopProcId < 0){
		LogFileInst::instance().logError("IdentifierDefineListSemanticser::processVarIdentifierList getProcStackTop error", __FILE__, __LINE__);
		return bProcessSemanticser;
	}

	// 是否跟类型表信息表中的类型同名
	int nTypeInfoAddressValue = SymbolTableInst::instance().searchTypeInfoTable(nStackTopProcId, pConstTokenWord->m_szContentValue);
	if(nTypeInfoAddressValue >= 0){
		return bProcessSemanticser;
	}

	// 在当前函数内 是否有常量跟其变量同名(存在,则定义失败)
	int nConstAddressValue = SymbolTableInst::instance().searchConstInfoTable(nStackTopProcId, pConstTokenWord->m_szContentValue);
	if(nConstAddressValue >= 0){
		return bProcessSemanticser;
	}

	// 在当前函数内 是否有标号 跟其变量同名(存在,则定义失败)
	int nConstAddressValue = SymbolTableInst::instance().searchConstInfoTable(nStackTopProcId, pConstTokenWord->m_szContentValue);
	if(nConstAddressValue >= 0){
		return bProcessSemanticser;
	}

	// 在当前函数内 是否有枚举 跟其变量同名(存在,则定义失败)
	int nLabelAddressValue = SymbolTableInst::instance().searchLableInfoTable(nStackTopProcId, pConstTokenWord->m_szContentValue);
	if(nLabelAddressValue >= 0){
		return bProcessSemanticser;
	}

	// 在当前函数内 是否有变量 跟其变量同名(存在,则定义失败)
	int nVarAddressValue = SymbolTableInst::instance().searchVarInfoTable(nStackTopProcId, pConstTokenWord->m_szContentValue);
	if(nVarAddressValue >= 0){
		return bProcessSemanticser;
	}

	// 是否跟过程同名(存在,则定义失败)
	bool bIsSameNameProc = SymbolTableInst::instance().compareProcNameIsSame(pConstTokenWord->m_szContentValue);
	if(true == bIsSameNameProc){
		return bProcessSemanticser;
	}

	// 检查完成 没有跟该变量名同名的 则将该变量放入变量表(存在,则定义失败)
	VarInfo newVarInfo;
	newVarInfo.initStrName(pConstTokenWord->m_szContentValue);
	newVarInfo.initProcIndex(nStackTopProcId);
	newVarInfo.m_eRank = VarInfo::eR_Var;
	SymbolTableInst::instance().addNewVarToSpecficProcId(newVarInfo);

	bProcessSemanticser = true;
	return bProcessSemanticser;
}
