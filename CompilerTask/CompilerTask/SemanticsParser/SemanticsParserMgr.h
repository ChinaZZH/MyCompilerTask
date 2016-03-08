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
#include "../SemanticsHelper/SemanticsParserIdFlag.h"

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
	SemanticsParserIdFlag& getSemanticsParserIdFlag();

private:
	SemanticserHandlerMap m_mapSemanticserHandler;

	SemanticsParserIdFlag m_semanticsParserIdFlag;
};

typedef Singleton<SemanticsParserMgr> SemanticsParserMgrInst;