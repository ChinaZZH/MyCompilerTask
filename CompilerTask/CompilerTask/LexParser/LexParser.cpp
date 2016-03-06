
#include "LexParser.h"
#include <vector>
#include "../GlobalData/LexParseGlobalDataDef.h"
#include "../ConfigFile/State.h"
#include "../Common/CommonLib.h"
#include "../GlobalData/LexStateTable.h"
#include "../GlobalData/KeyWordTable.h"
#include "../GlobalData/WordStreamTable.h"
#include "../Common/ErrorProcess.h"
#include "../Log/LogFile.h"
#include "../SymbolTable/SymbolTable.h"



CLex::CLex()
	:m_nRowIndex(0)
	,m_nStateValue(0)
	, m_nReaderPosition(0)
{
	m_szSourceContent.clear();
	m_strWordBuff.clear();

	SSymbolHandler identifier;
	identifier.m_handlerOfProcessSymbol = &CLex::handleProcessIdentifier;
	m_mapSymbolHandlerMap[eEST_Identifier] = identifier;

	SSymbolHandler constValue;
	constValue.m_handlerOfProcessSymbol = &CLex::handleProcessConstant;
	m_mapSymbolHandlerMap[eEST_ConstantValue] = constValue;

	SSymbolHandler boundSymbol;
	boundSymbol.m_handlerOfProcessSymbol = &CLex::handleProcessBoundSymbol;
	m_mapSymbolHandlerMap[eEST_BoundSymbol] = boundSymbol;

	SSymbolHandler operatorSymbol;
	operatorSymbol.m_handlerOfProcessSymbol = &CLex::handleProcessOperatorSymbol;
	m_mapSymbolHandlerMap[eEST_OperatorSymbol] = operatorSymbol;

	SSymbolHandler twoPointSymbol;
	twoPointSymbol.m_handlerOfProcessSymbol = &CLex::handleProcessTwoPointSymbol;
	m_mapSymbolHandlerMap[eEST_TwoPoint] = twoPointSymbol;

	SSymbolHandler otherSymbol;
	otherSymbol.m_handlerOfProcessSymbol = &CLex::handleProcessOtherSymbol;
	m_mapSymbolHandlerMap[eEST_Other] = otherSymbol;
}


CLex::~CLex()
{

}


bool CLex::GenTokenFromSourceFile()
{
	bool bGetTokenResult = false;
	std::string strSourceFileName = ConfigFileDataInst::instance().getSourceFile();
	if(true == strSourceFileName.empty()){
		LogFileInst::instance().logError("CLex::GenTokenFromSourceFile SourceFileName null", __FILE__, __LINE__);
		return bGetTokenResult;
	}

	// 获取文本
	std::string strFileContent = CommonLib::FileRead(strSourceFileName);
	if(true == strFileContent.empty()){
		LogFileInst::instance().logError("CLex::GenTokenFromSourceFile FileContent null", __FILE__, __LINE__);
		return bGetTokenResult;
	}

	// 赋值
	m_szSourceContent = strFileContent;

	// 开始扫描
	int nNewLineBeginPos = 0;
	m_nReaderPosition = 0;
	bGetTokenResult = true;
	m_nRowIndex = 1;
	m_nStateValue = 0;

	int nFileContentLength = static_cast<int>(strFileContent.length());
	while((true == bGetTokenResult) && (m_nReaderPosition < nFileContentLength)){
		// 出现换行符， 记录新的行号 TmpPosition不记录
		if (('\n'==strFileContent[m_nReaderPosition]) && (m_nReaderPosition>nNewLineBeginPos)){
			m_nRowIndex += 1;
			nNewLineBeginPos = m_nReaderPosition;
		}

		// 单词缓冲区不记录
		unsigned char ucLexCharacter = strFileContent[m_nReaderPosition];
		if(ucLexCharacter >= g_s_AsciiCharNum){
			ucLexCharacter = (g_s_AsciiCharNum - 1);
		}

		// 放入单词缓冲区
		m_strWordBuff.push_back(ucLexCharacter);

		// 输入新字符的最新状态
		int nNewStateValue = LexStateTableInst::instance().searchStateByInputChar(m_nStateValue, ucLexCharacter);
		if(eLSV_Error == nNewStateValue){
			char szError[1024] = { 0 };
			sprintf_s(szError, "CLex::GenTokenFromSourceFile processNewStateOfLex error RowIndex %d Position %d", m_nRowIndex, m_nReaderPosition);
			LogFileInst::instance().logError("CLex::GenTokenFromSourceFile processNewStateOfLex error", __FILE__, __LINE__);

			bGetTokenResult = false;
			return bGetTokenResult;
		}
		
		// 对最新状态的处理
		bool bProcessTag = this->processNewStateOfLex(nNewStateValue);
		if(false == bProcessTag){
			LogFileInst::instance().logError("CLex::GenTokenFromSourceFile processNewStateOfLex error", __FILE__, __LINE__);

			bGetTokenResult = false;
			return bGetTokenResult;
		}

		// 扫描下一个字符
		m_nReaderPosition += 1;
	}

	return bGetTokenResult;
}


bool CLex::processNewStateOfLex(int nProcessState)
{
	// 是否为出错状态
	bool bProcessResult = false;
	if(eLSV_Error == nProcessState){
		LogFileInst::instance().logError("CLex::processNewStateOfLex nProcessState error", __FILE__, __LINE__);
		return bProcessResult;
	}

	// 如果不是终止状态, 更新状态并返回
	if(nProcessState >= eLSV_TerminationState){
		m_nStateValue = nProcessState;

		bProcessResult = true;
		return bProcessResult;	

	}

	// 终止状态下的文本处理
	// 1.0 回退一个字符
	this->wordBuffBackOneCharacter();
	
	// 过滤掉左右空格
	m_strWordBuff = CommonLib::trim(m_strWordBuff);

	// 状态进行处理
	eEndSymbolType symbol = this->getEndSymbolTypeByState(nProcessState);
	SymbolHandlerMap::iterator itr = m_mapSymbolHandlerMap.find(symbol);
	if(itr == m_mapSymbolHandlerMap.end()){
		LogFileInst::instance().logError("CLex::processNewStateOfLex eEndSymbolType error", __FILE__, __LINE__);
		return bProcessResult;
	}

	_HandleProcessSymbolStatus& handlerSymbol = (itr->second).m_handlerOfProcessSymbol;
	bool bLexResult = (this->*handlerSymbol)(nProcessState);
	if(false == bLexResult){
		LogFileInst::instance().logError("CLex::processNewStateOfLex handlerSymbol Process error", __FILE__, __LINE__);
		return bProcessResult;
	}

	// 清空单词缓存
	m_strWordBuff.clear();
	m_nStateValue = 0;
	bProcessResult = true;
	return bProcessResult;
}


void CLex::wordBuffBackOneCharacter()
{
	int nBuffSize = m_strWordBuff.size();
	if(nBuffSize > 0){
		m_strWordBuff.erase(nBuffSize - 1);
	}

	m_nReaderPosition = m_nReaderPosition - 1;
}

eEndSymbolType CLex::getEndSymbolTypeByState(int nProcessState)
{
	// 数组负数
	if (eLSV_IntegerBackTwoCharacter == nProcessState){
		// 回退两个运算符
		return eEST_TwoPoint;
	}

	// 将状态由负数转化为正数
	nProcessState = (-1) *nProcessState;
	eEndSymbolType symbolStatus = eEST_Other;
	if (eLSV_Identifier == nProcessState){
		// 标识符
		symbolStatus = eEST_Identifier;
	}else if ((nProcessState >= eLSV_ConstantDataStartIndex) && (nProcessState <= eLSV_ConstantDataEndIndex)){
		// 常量
		symbolStatus = eEST_ConstantValue;
	}else if ((nProcessState >= eSLV_BoundStartIndex) && (nProcessState <= eSLV_BoundEndIndex)){
		// 界符
		symbolStatus = eEST_BoundSymbol;
	}else if ((nProcessState >= eSLV_OperatorStartIndex) && (nProcessState <= eSLV_OperatorEndIndex)){
		// 运算符
		symbolStatus = eEST_OperatorSymbol;
	}else{
		symbolStatus = eEST_Other;
	}

	return symbolStatus;
}

bool CLex::handleProcessIdentifier(int nCurrentState)
{
	bool bProcessResult = true;
	// 大小写不敏感 则将大写转化为小写 统一处理
	m_strWordBuff = CommonLib::upperCase(m_strWordBuff);

	// 查找关键字表
	int nKeyWordStatus = KeyWordTableInst::instance().searchKeyWordOnTable(m_strWordBuff);
	if(0 != nKeyWordStatus){
		// 关键字
		WordStreamTableInst::instance().pushNewWordToTable(nKeyWordStatus, NULL, m_nRowIndex);
		return bProcessResult;
	}

	
	int nTrueBuff = m_strWordBuff.compare("TRUE");
	int nFalseBuff = m_strWordBuff.compare("FALSE");
	if((0==nTrueBuff) || (0==nFalseBuff)){
		int nConstAddress = SymbolTableInst::instance().recConstTbl(m_strWordBuff, eCEV_ConstantBoolValue);
		WordStreamTableInst::instance().pushNewWordToTable(eLSV_ConstantInteger, nConstAddress, m_nRowIndex);
		return bProcessResult;
	}

	// 变量名
	WordStreamTableInst::instance().pushNewWordToTable(eLSV_Identifier, m_strWordBuff, m_nRowIndex);
	return bProcessResult;
}


bool CLex::handleProcessConstant(int nCurrentState)
{
	bool bProcessResult = false;
	nCurrentState = (-1)*(nCurrentState);
	int nConstAddress = SymbolTableInst::instance().recConstTbl(m_strWordBuff, nCurrentState);
	WordStreamTableInst::instance().pushNewWordToTable(nCurrentState, nConstAddress, m_nRowIndex);
	bProcessResult = true;
	return bProcessResult;
}

bool CLex::handleProcessBoundSymbol(int nCurrentState)
{
	bool bProcessResult = false;
	nCurrentState = (-1)*(nCurrentState);
	WordStreamTableInst::instance().pushNewWordToTable(nCurrentState, NULL, m_nRowIndex);
	bProcessResult = true;
	return bProcessResult;
}

bool CLex::handleProcessOperatorSymbol(int nCurrentState)
{
	bool bProcessResult = false;
	nCurrentState = (-1)*(nCurrentState);
	WordStreamTableInst::instance().pushNewWordToTable(nCurrentState, NULL, m_nRowIndex);
	bProcessResult = true;
	return bProcessResult;
}

bool CLex::handleProcessTwoPointSymbol(int nCurrentState)
{
	bool bProcessResult = false;
	// 继续回退一格
	this->wordBuffBackOneCharacter();

	m_strWordBuff = CommonLib::trim(m_strWordBuff);

	int nConstAddress = SymbolTableInst::instance().recConstTbl(m_strWordBuff, eCEV_ConstantInteger);
	WordStreamTableInst::instance().pushNewWordToTable(eLSV_ConstantInteger, nConstAddress, m_nRowIndex);
	bProcessResult = true;
	return bProcessResult;
}

bool CLex::handleProcessOtherSymbol(int nCurrentState)
{
	// 不做处理
	return true;
}
