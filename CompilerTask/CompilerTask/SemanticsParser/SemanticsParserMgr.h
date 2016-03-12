/********************************************************************
            Copyright (c) 2015
                   All rights reserved
         
    �������ڣ�  2015�� �� �� ʱ ��
    �ļ����ƣ�  
    ˵    ����       
    
    ��ǰ�汾��  
    ��    �ߣ�  ֣���
    ��    ����      

*********************************************************************/

#pragma once
#include <map>
#include <stack>
#include "../Common/Singleton.h"
#include "../SemanticsFlagHandler/IdentifierListFlagHandler.h"
#include "../SemanticsFlagHandler/ProcStackParserHandler.h"

class BaseSemanticser;
typedef std::map<int, BaseSemanticser*> SemanticserHandlerMap;


class SemanticsParserMgr
{
public:
	SemanticsParserMgr();
	~SemanticsParserMgr();

public:
	bool processSemanticsParser(int nSemanticserValue);

private:
	void initSemanticsParser();

public:
	IdentifierListFlagHandler& getIdentifierListFlagHandler();

	ProcStackParserHandler& getProcStackParserHandler();

private:
	SemanticserHandlerMap m_mapSemanticserHandler;

	IdentifierListFlagHandler m_semanticsParserIdFlag;

	ProcStackParserHandler    m_procStackParserHandler;
};

typedef Singleton<SemanticsParserMgr> SemanticsParserMgrInst;