#include "SemanticsParserMgr.h"
#include "../Log/LogFile.h"
#include "BaseSemanticser.h"

SemanticsParserMgr::SemanticsParserMgr()
{
	this->initSemanticsParser();
}

SemanticsParserMgr::~SemanticsParserMgr()
{

}

bool SemanticsParserMgr::processSemanticsParser(int nSemanticserValue)
{
	bool bProcessSemantics = false;
	SemanticserHandlerMap::iterator itr = m_mapSemanticserHandler.find(nSemanticserValue);
	if(itr == m_mapSemanticserHandler.end()){
		LogFileInst::instance().logError("SemanticsParserMgr::processSemanticsParser 语义子程序 错误", __FILE__, __LINE__);
		return bProcessSemantics;
	}

	BaseSemanticser* pSemanticser = itr->second;
	if(NULL == pSemanticser){
		LogFileInst::instance().logError("SemanticsParserMgr::processSemanticsParser pSemanticser null", __FILE__, __LINE__);
		return bProcessSemantics;
	}

	bProcessSemantics = pSemanticser->processSemanticsParser();
	if(false == bProcessSemantics){
		LogFileInst::instance().logError("SemanticsParserMgr::processSemanticsParser 执行语义子程序的时候出错", __FILE__, __LINE__);
		return bProcessSemantics;
	}

	bProcessSemantics = true;
	return bProcessSemantics;
}


void SemanticsParserMgr::initSemanticsParser()
{

}
