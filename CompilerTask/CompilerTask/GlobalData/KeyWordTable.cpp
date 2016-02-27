
#include "KeyWordTable.h"
#include "../ConfigFile/State.h"
#include "../Common/CommonLib.h"


KeyWordTable::KeyWordTable()
{
	m_mapKeywordTbl.clear();
}

KeyWordTable::~KeyWordTable()
{

}

void KeyWordTable::initData()
{
	std::string strKeyWordsFile = ConfigFileDataInst::instance().getKeyWordsFile();
	if(true == strKeyWordsFile.empty())
	{
		return;
	}

	std::string strKeyWordsContent = CommonLib::FileRead(strKeyWordsFile);
	if(true == strKeyWordsContent.empty())
	{
		return;
	}

	this->parseStringToKeyWordsTable(strKeyWordsContent);
}

int KeyWordTable::searchKeyWordOnTable(std::string strKeyWord) const
{
	KeyWordMap::const_iterator itr = m_mapKeywordTbl.find(strKeyWord);
	if(itr == m_mapKeywordTbl.end()){
		return 0;
	}

	int nStatusValue = itr->second;
	return nStatusValue;
}

void KeyWordTable::parseStringToKeyWordsTable(const std::string& strParseContent)
{
	std::string strTmpWord = "";
	for(unsigned int i = 0; i < strParseContent.length(); ++i){
		if('\n' != strParseContent[i]){
			strTmpWord.append(1, strParseContent[i]);
			continue;
		}

		if(true == strTmpWord.empty()){
			continue;
		}

		int nOffSet = strTmpWord.find_first_of('.');
		std::string strKeyWordStatus = strTmpWord.substr(0, nOffSet);
		std::string strKeyWordString = strTmpWord.substr(nOffSet + 1, strTmpWord.size()-1);
		m_mapKeywordTbl[strKeyWordString] = atoi(strKeyWordStatus.c_str());
		
		strTmpWord.clear();
	}

	if(false == strTmpWord.empty()){
		int nOffSet = strTmpWord.find_first_of('.');
		std::string strKeyWordStatus = strTmpWord.substr(0, nOffSet - 1);
		std::string strKeyWordString = strTmpWord.substr(nOffSet + 1, strTmpWord.size() - 1);
		m_mapKeywordTbl[strKeyWordString] = atoi(strKeyWordStatus.c_str());
	}

}
