#include "MainProgramHeaderStatementSemanticser.h"
#include "../SymbolTable/ProcInfoTable.h"
#include "../Log/LogFile.h"
#include "../SyntaxParser/SyntaxParser.h"
#include "../GlobalData/WordStreamTable.h"
#include "../SymbolTable/SymbolTable.h"
#include "SemanticsParserMgr.h"

MainProgramHeaderStatementSemanticser::MainProgramHeaderStatementSemanticser()
{

}

MainProgramHeaderStatementSemanticser::~MainProgramHeaderStatementSemanticser()
{

}

// 程序头---> program 标识符 001(标识符列表)
bool MainProgramHeaderStatementSemanticser::processSemanticsParser()
{
	bool bProcessParserResult = false;
	bool bInitSemanticserResult = this->initBeforeSemanticserStart();
	if(false == bInitSemanticserResult){
		LogFileInst::instance().logError("MainProgramHeaderStatementSemanticser::processSemanticsParser initBeforeSemanticserStart error", __FILE__, __LINE__);
		return bProcessParserResult;
	}

	// 找到前一个标识符
	int nParserWordTableIndex = SyntaxParserInst::instance().getParserWordTableIndex();
	if(nParserWordTableIndex <= 0){
		LogFileInst::instance().logError("MainProgramHeaderStatementSemanticser::processSemanticsParser nParserWordTableIndex error", __FILE__, __LINE__);
		return bProcessParserResult;
	}

	// 找到const常量的标识符
	int nLastParserWordIndex = nParserWordTableIndex - 1;
	if(nLastParserWordIndex <= 0){
		LogFileInst::instance().logError("MainProgramHeaderStatementSemanticser::processSemanticsParser nLastParserWordIndex error", __FILE__, __LINE__);
		return bProcessParserResult;
	}

	// 从词法分析中得到的 单词集  中去朝 对应的单词
	const CToken* pParserWord = WordStreamTableInst::instance().getWordTokenByTableIndex(nLastParserWordIndex);
	if(NULL == pParserWord){
		LogFileInst::instance().logError("MainProgramHeaderStatementSemanticser::processSemanticsParser pParserWord null", __FILE__, __LINE__);
		return bProcessParserResult;
	}

	SemanticsParserMgrInst::instance().clearAllData();

	// 创建新的一个过程
	ProcInfo newProcInfo;
	newProcInfo.m_strProcName = pParserWord->m_szContentValue;
	newProcInfo.m_eRankValue = ProcInfo::Rank::Main;
	newProcInfo.m_eType = ProcInfo::Type::Procedure;
	newProcInfo.m_ParaTable.clear();

	// 将该过程放入符号表中
	int nProcIndexAddress = SymbolTableInst::instance().addNewProcInfo(newProcInfo);

	// 放入过程栈中
	ProcStackParserHandler& procStackParserHandler = SemanticsParserMgrInst::instance().getProcStackParserHandler();
	procStackParserHandler.newProcCallAddToStack(nProcIndexAddress);

	// 标识符标识 处理器
	IdentifierListFlagHandler& identifierListHandler = SemanticsParserMgrInst::instance().getIdentifierListFlagHandler();
	identifierListHandler.startNewSemanticserParserFlag(eSPIF_MainProgramIdentifierListStart);

	// 类型标志 处理器
	TypeFlagHandler& typeFlagHandler = SemanticsParserMgrInst::instance().getTypeFlagHandler();
	typeFlagHandler.pushTypeFlagValueToStack(eTFEV_MainTypeValue);

	bProcessParserResult = true;
	return bProcessParserResult;
}

eSemansticeParserTypeValue MainProgramHeaderStatementSemanticser::returnSemanticserEnumValue()
{
	return eSemansticeParserTypeValue::eSPEV_MainProgramHeaderStatementParser;
}


bool MainProgramHeaderStatementSemanticser::initBeforeSemanticserStart()
{
	return true;
}