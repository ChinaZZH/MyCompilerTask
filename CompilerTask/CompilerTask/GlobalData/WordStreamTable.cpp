
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


