
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

	// ��ȡ�ı�
	std::string strFileContent = CommonLib::FileRead(strSourceFileName);
	if(true == strFileContent.empty()){
		LogFileInst::instance().logError("CLex::GenTokenFromSourceFile FileContent null", __FILE__, __LINE__);
		return bGetTokenResult;
	}

	// ��ֵ
	m_szSourceContent = strFileContent;

	// ��ʼɨ��
	int nNewLineBeginPos = 0;
	m_nReaderPosition = 0;
	bGetTokenResult = true;
	m_nRowIndex = 1;
	m_nStateValue = 0;

	int nFileContentLength = static_cast<int>(strFileContent.length());
	while((true == bGetTokenResult) && (m_nReaderPosition < nFileContentLength)){
		// ���ֻ��з��� ��¼�µ��к� TmpPosition����¼
		if (('\n'==strFileContent[m_nReaderPosition]) && (m_nReaderPosition>nNewLineBeginPos)){
			m_nRowIndex += 1;
			nNewLineBeginPos = m_nReaderPosition;
		}

		// ���ʻ���������¼
		unsigned char ucLexCharacter = strFileContent[m_nReaderPosition];
		if(ucLexCharacter >= g_s_AsciiCharNum){
			ucLexCharacter = (g_s_AsciiCharNum - 1);
		}

		// ���뵥�ʻ�����
		m_strWordBuff.push_back(ucLexCharacter);

		// �������ַ�������״̬
		int nNewStateValue = LexStateTableInst::instance().searchStateByInputChar(m_nStateValue, ucLexCharacter);
		if(eLSV_Error == nNewStateValue){
			char szError[1024] = { 0 };
			sprintf_s(szError, "CLex::GenTokenFromSourceFile processNewStateOfLex error RowIndex %d Position %d", m_nRowIndex, m_nReaderPosition);
			LogFileInst::instance().logError("CLex::GenTokenFromSourceFile processNewStateOfLex error", __FILE__, __LINE__);

			bGetTokenResult = false;
			return bGetTokenResult;
		}
		
		// ������״̬�Ĵ���
		bool bProcessTag = this->processNewStateOfLex(nNewStateValue);
		if(false == bProcessTag){
			LogFileInst::instance().logError("CLex::GenTokenFromSourceFile processNewStateOfLex error", __FILE__, __LINE__);

			bGetTokenResult = false;
			return bGetTokenResult;
		}

		// ɨ����һ���ַ�
		m_nReaderPosition += 1;
	}

	return bGetTokenResult;
}


bool CLex::processNewStateOfLex(int nProcessState)
{
	// �Ƿ�Ϊ����״̬
	bool bProcessResult = false;
	if(eLSV_Error == nProcessState){
		LogFileInst::instance().logError("CLex::processNewStateOfLex nProcessState error", __FILE__, __LINE__);
		return bProcessResult;
	}

	// ���������ֹ״̬, ����״̬������
	if(nProcessState >= eLSV_TerminationState){
		m_nStateValue = nProcessState;

		bProcessResult = true;
		return bProcessResult;	

	}

	// ��ֹ״̬�µ��ı�����
	// 1.0 ����һ���ַ�
	this->wordBuffBackOneCharacter();
	
	// ���˵����ҿո�
	m_strWordBuff = CommonLib::trim(m_strWordBuff);

	// ״̬���д���
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

	// ��յ��ʻ���
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
	// ���鸺��
	if (eLSV_IntegerBackTwoCharacter == nProcessState){
		// �������������
		return eEST_TwoPoint;
	}

	// ��״̬�ɸ���ת��Ϊ����
	nProcessState = (-1) *nProcessState;
	eEndSymbolType symbolStatus = eEST_Other;
	if (eLSV_Identifier == nProcessState){
		// ��ʶ��
		symbolStatus = eEST_Identifier;
	}else if ((nProcessState >= eLSV_ConstantDataStartIndex) && (nProcessState <= eLSV_ConstantDataEndIndex)){
		// ����
		symbolStatus = eEST_ConstantValue;
	}else if ((nProcessState >= eSLV_BoundStartIndex) && (nProcessState <= eSLV_BoundEndIndex)){
		// ���
		symbolStatus = eEST_BoundSymbol;
	}else if ((nProcessState >= eSLV_OperatorStartIndex) && (nProcessState <= eSLV_OperatorEndIndex)){
		// �����
		symbolStatus = eEST_OperatorSymbol;
	}else{
		symbolStatus = eEST_Other;
	}

	return symbolStatus;
}

bool CLex::handleProcessIdentifier(int nCurrentState)
{
	bool bProcessResult = true;
	// ��Сд������ �򽫴�дת��ΪСд ͳһ����
	m_strWordBuff = CommonLib::upperCase(m_strWordBuff);

	// ���ҹؼ��ֱ�
	int nKeyWordStatus = KeyWordTableInst::instance().searchKeyWordOnTable(m_strWordBuff);
	if(0 != nKeyWordStatus){
		// �ؼ���
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

	// ������
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
	// ��������һ��
	this->wordBuffBackOneCharacter();

	m_strWordBuff = CommonLib::trim(m_strWordBuff);

	int nConstAddress = SymbolTableInst::instance().recConstTbl(m_strWordBuff, eCEV_ConstantInteger);
	WordStreamTableInst::instance().pushNewWordToTable(eLSV_ConstantInteger, nConstAddress, m_nRowIndex);
	bProcessResult = true;
	return bProcessResult;
}

bool CLex::handleProcessOtherSymbol(int nCurrentState)
{
	// ��������
	return true;
}
