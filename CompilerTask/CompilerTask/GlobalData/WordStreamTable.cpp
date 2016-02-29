
#include "WordStreamTable.h"
#include "../Common/Structure.h"
#include "../ConfigFile/State.h"

WordStreamTable::WordStreamTable()
{
	m_vecWordsStreamTable.clear();
}

WordStreamTable::~WordStreamTable()
{

}

void WordStreamTable::pushNewWordToTable(int nWordStatus, int nSymbolAddress, int nRowIndex)
{
	char szSymbolAddress[12] = { 0 };
	sprintf_s(szSymbolAddress, "%d", nSymbolAddress);
	std::string strSymbolAddress(szSymbolAddress);

	this->pushNewWordToTable(nWordStatus, strSymbolAddress, nRowIndex);
}


void WordStreamTable::pushNewWordToTable(int nWordStatus, std::string strContentValue, int nRowIndex)
{
	std::string strSourceFileName = ConfigFileDataInst::instance().getSourceFile();
	if(true == strSourceFileName.empty()){
		return;
	}

	CToken newTokenWord(nWordStatus, strContentValue, nRowIndex, strSourceFileName);
	m_vecWordsStreamTable.push_back(newTokenWord);
}


int WordStreamTable::getMaxWordNumInTable()
{
	int nMaxWordNum = m_vecWordsStreamTable.size();
	return nMaxWordNum;
}


const CToken* WordStreamTable::getWordTokenByTableIndex(int nTableIndex)
{
	bool bCheckIndexCorrect = this->checkWordTableIndexIsCorrect(nTableIndex);
	if(false == bCheckIndexCorrect){
		return NULL;
	}

	const CToken* pGetWordToken = &m_vecWordsStreamTable[nTableIndex];
	return pGetWordToken;
}


bool WordStreamTable::checkWordTableIndexIsCorrect(int nIndexValue)
{
	bool bCheckIndexResult = false;
	if(nIndexValue < 0){
		return bCheckIndexResult;
	}

	if(nIndexValue >= (int)m_vecWordsStreamTable.size()){
		return bCheckIndexResult;
	}

	bCheckIndexResult = true;
	return bCheckIndexResult;
}