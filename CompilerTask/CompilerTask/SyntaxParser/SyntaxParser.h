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
#include "../Common/Singleton.h"
#include <stack>
#include <string>
#include <map>
#include "SyntaxParserEnumValue.h"

class CToken;
class SyntaxParser;
typedef bool(SyntaxParser::*_HandleSyntaxParserStatus)(int nStackElementValue, const CToken* pWordToken);
struct SSyntaxParserHandler
{
	_HandleSyntaxParserStatus  m_handleSyntaxParser;

	SSyntaxParserHandler()
		:m_handleSyntaxParser(NULL)
	{ }
};

typedef std::map<eSyntaxParserHandlerTag, SSyntaxParserHandler> SyntaxParserHandlerMap;

class SyntaxParser
{
public:
	SyntaxParser();
	~SyntaxParser();

public:
	bool processSyntaxParse();

private:
	void clearSyntaxStack();

	int popTopValueParserStack();

	bool pushValueToParserStack(const std::string& strProductValue);

	eSyntaxParserHandlerTag getSyntaxHandlerByValue(int nStackElementValue);

private:
	bool handleErrorSymbolSyntaxParser(int nStackElementValue, const CToken* pWordToken);

	bool handleNullSymbolSyntaxParser(int nStackElementValue, const CToken* pWordToken);

	bool handleTerminalSymbolSyntaxParser(int nStackElementValue, const CToken* pWordToken);

	bool handleNoTerminalSyntaxParser(int nStackElementValue, const CToken* pWordToken);

	bool handleSemanticsSyntaxParser(int nStackElementValue, const CToken* pWordToken);

private:
	std::stack<int> m_stackSyntaxParser;

	int m_nParserWordTableIndex;

	SyntaxParserHandlerMap m_mapSyntaxParserHandler;
};

typedef Singleton<SyntaxParser> SyntaxParserInst;