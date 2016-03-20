/********************************************************************
            Copyright (c) 2015
                   All rights reserved
         
    创建日期：  2015年 月 日 时 分
    文件名称：  
    说    明：       
    
    当前版本：  
    作    者：  郑祖煌
    概    述：      

*********************************************************************/

#pragma once
#include <map>
#include <stack>
#include "../Common/Singleton.h"
#include "../SemanticsFlagHandler/IdentifierListFlagHandler.h"
#include "../SemanticsFlagHandler/ProcStackParserHandler.h"
#include "../SemanticsFlagHandler/TypePositionParseHandler.h"
#include "../SemanticsFlagHandler/TypeFlagHandler.h"

class BaseSemanticser;
typedef std::map<int, BaseSemanticser*> SemanticserHandlerMap;


class SemanticsParserMgr
{
public:
	SemanticsParserMgr();
	~SemanticsParserMgr();

public:
	void clearAllData();

public:
	bool processSemanticsParser(int nSemanticserValue);

private:
	void initSemanticsParser();

public:
	IdentifierListFlagHandler& getIdentifierListFlagHandler();

	ProcStackParserHandler& getProcStackParserHandler();

	TypePositionParseHandler& getTypePositionParseHandler();

	TypeFlagHandler& getTypeFlagHandler();

private:
	SemanticserHandlerMap m_mapSemanticserHandler;

private:
	IdentifierListFlagHandler m_semanticsParserIdFlag;

	ProcStackParserHandler    m_procStackParserHandler;

	TypePositionParseHandler  m_typeInfPositionParserHandler;

	TypeFlagHandler   m_typeFlagHandler;
};

typedef Singleton<SemanticsParserMgr> SemanticsParserMgrInst;