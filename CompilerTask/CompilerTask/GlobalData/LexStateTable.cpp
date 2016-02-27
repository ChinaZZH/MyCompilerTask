
#include "LexStateTable.h"
#include "../ConfigFile/State.h"
#include "../Common/CommonLib.h"

LexStateTable::LexStateTable()
{
	for (int i = 0; i < g_s_LexStateMaxNum; i++)
	{
		for(int j = 0; j < g_s_AsciiCharNum; j++)
		{
			m_arrayLexStateTable[i][j] = 0;
		}
	}
}

LexStateTable::~LexStateTable()
{

}

void LexStateTable::initData()
{
	// 设置词法分析状态表
	std::string strLexStateFile = ConfigFileDataInst::instance().getLexPaserInstFileName();
	if(true == strLexStateFile.empty()){
		return;
	}

	std::string strLexContent = CommonLib::FileRead(strLexStateFile);
	if(true == strLexContent.empty()){
		return;
	}

	strLexContent = CommonLib::StrErase(strLexContent, '\n');
	
	this->parseInitDataToStateTable(strLexContent);
}

int LexStateTable::searchStateByInputChar(int nSpecficState, int nInputChar)
{
	int nSearchStateValue = 0;
	if((nSpecficState < 0) || (nSpecficState >= g_s_LexStateMaxNum)){
		return nSearchStateValue;
	}

	if((nInputChar < 0) || (nInputChar >= g_s_AsciiCharNum)){
		return nSearchStateValue;
	}

	nSearchStateValue = m_arrayLexStateTable[nSpecficState][nInputChar];
	return nSearchStateValue;
}


void LexStateTable::parseInitDataToStateTable(const std::string& strInitStateData)
{
	int iTmp = 0;
	for(int iRow = 0; iRow <= 36; iRow++)
	{
		for(int iCol = 0; iCol <= 128; iCol++)
		{
			std::string strStateTag = strInitStateData.substr(iTmp, 3);
			int nLexState = atoi(strStateTag.c_str());
			m_arrayLexStateTable[iRow][iCol] = nLexState;
			
			iTmp = iTmp + 3;
		}
	}

	
	int i = 0;
}
