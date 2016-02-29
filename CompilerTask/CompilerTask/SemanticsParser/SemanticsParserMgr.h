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
#include "../Common/Singleton.h"

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

private:
	SemanticserHandlerMap m_mapSemanticserHandler;
};

typedef Singleton<SemanticsParserMgr> SemanticsParserMgrInst;