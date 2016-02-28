#include "SyntaxParserTable.h"
#include "../ConfigFile/State.h"
#include "../Log/LogFile.h"
#include "../Common/CommonLib.h"


SyntaxParserTable::SyntaxParserTable()
{
	for(int i = 0; i < g_s_ParseTableNum; ++i){
		for(int j = 0; j < g_s_ParseTableNum; ++j){
			m_arrayParseTbl[i][j] = -1;
		}
	}

	m_vecStringProductList.clear();
	m_vecStringProductList.push_back("");
}


SyntaxParserTable::~SyntaxParserTable()
{

}

void SyntaxParserTable::init()
{
	// 构建语法分析表
	bool bInitResult = this->initSyntaxParserTable();
	if(false == bInitResult){
		LogFileInst::instance().logError("SyntaxParserTable::init initSyntaxParserTable error", __FILE__, __LINE__);
	}

	// 构建产生式
	bInitResult = this->initProductTable();
	if(false == bInitResult){
		LogFileInst::instance().logError("SyntaxParserTable::init initProductTable error", __FILE__, __LINE__);
	}
}


bool SyntaxParserTable::initSyntaxParserTable()
{
	bool bInitTableResult = false;
	std::string strSyntaxFileName = ConfigFileDataInst::instance().getSyntaxParserTableFileName();
	if(true == strSyntaxFileName.empty()){
		LogFileInst::instance().logError("SyntaxParserTable::initSyntaxParserTable strSyntaxFileName null", __FILE__, __LINE__);
		return bInitTableResult;
	}

	std::string strSyntaxParserContent = CommonLib::FileRead(strSyntaxFileName);
	if(true == strSyntaxParserContent.empty()){
		LogFileInst::instance().logError("SyntaxParserTable::initSyntaxParserTable strSyntaxParserContent null", __FILE__, __LINE__);
		return bInitTableResult;
	}
	
	int nCntValue = 0;
	for(int i = 0; i < S_N_ParserTableRow; ++i){
		for(int j = 0; j < S_N_ParserTableCol; ++j){
			int nProductId = atoi(strSyntaxParserContent.substr(nCntValue, 3).c_str());
			nCntValue = nCntValue + 3;

			m_arrayParseTbl[i][j] = nProductId;
		}
	}

	bInitTableResult = true;
	return bInitTableResult;
}

bool SyntaxParserTable::initProductTable()
{
	bool bInitTableResult = false;
	std::string strProductTable = ConfigFileDataInst::instance().getProductFileName();
	if(true == strProductTable.empty()){
		LogFileInst::instance().logError("SyntaxParserTable::initProductTable strProductTable null", __FILE__, __LINE__);
		return bInitTableResult;
	}

	std::string strProductContent = CommonLib::FileRead(strProductTable);
	if(true == strProductContent.empty()){
		LogFileInst::instance().logError("SyntaxParserTable::initProductTable strProductContent null", __FILE__, __LINE__);
		return bInitTableResult;
	}

	std::string strTmpWord = "";
	for(int i = 0; i < strProductContent.length(); ++i){
		if('\n' != strProductContent[i]){
			strTmpWord.append(1, strProductContent[i]);
			continue;
		}

		if(true == strTmpWord.empty()){
			continue;
		}

		m_vecStringProductList.push_back(strTmpWord);
		strTmpWord.clear();
	}

	if(false == strTmpWord.empty()){
		m_vecStringProductList.push_back(strTmpWord);
	}
	
	bInitTableResult = true;
	return bInitTableResult;
}
