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