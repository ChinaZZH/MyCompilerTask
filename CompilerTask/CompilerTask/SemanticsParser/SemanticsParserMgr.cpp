#include "SemanticsParserMgr.h"
#include "../Log/LogFile.h"
#include "BaseSemanticser.h"
#include "MainProgramHeaderStatementSemanticser.h"
#include "LabelStatmentSemanticser.h"
#include "ConstStatmentSemanticser.h"
#include "IdentifierDefineListSemanticser.h"
#include "VarDefineBeforeListSemanticser.h"
#include "VarDefineAfterListSemanticser.h"
#include "TypeDefineSemanticser.h"
#include "IncludeFileBeforeFileNameSemanticser.h"
#include "IncludeFileAfterFileNameSemanticser.h"

SemanticsParserMgr::SemanticsParserMgr()
:m_semanticsParserIdFlag()
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
	m_mapSemanticserHandler[eSPEV_MainProgramHeaderStatementParser] = new MainProgramHeaderStatementSemanticser();
	m_mapSemanticserHandler[eSPEV_LabelStatmentParser] = new LabelStatementSemanticser();
	m_mapSemanticserHandler[eSPEV_ConstStatmentParser] = new ConstStatementSemanticser();
	m_mapSemanticserHandler[eSPEV_IdentifierTypeDefineList] = new IdentifierDefineListSemanticser();
	m_mapSemanticserHandler[eSPEV_TypeDefineParser] = new TypeDefineSemanticser();

	m_mapSemanticserHandler[eSPEV_VarDefineBeforeList] = new VarDefineBeforeListSemanticser();
	m_mapSemanticserHandler[eSPEV_VarDefineAfterList] = new VarDefineAfterListSemanticser();
	m_mapSemanticserHandler[eSPEV_IncludeFileBeforeFileName] = new IncludeFileBeforeFileNameSemanticser();
	m_mapSemanticserHandler[eSPEV_IncludeFileAfterFileName] = new IncludeFileAfterFileNameSemanticser();
}


IdentifierListFlagHandler& SemanticsParserMgr::getIdentifierListFlagHandler()
{
	return m_semanticsParserIdFlag;
}


ProcStackParserHandler& SemanticsParserMgr::getProcStackParserHandler()
{
	return m_procStackParserHandler;
}

TypePositionParseHandler& SemanticsParserMgr::getTypePositionParseHandler()
{
	return m_typeInfPositionParserHandler;
}
