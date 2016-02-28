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
#include <string>
#include <vector>
#include "../Common/Structure.h"
#include <map>
#include "../Common/Singleton.h"
#include "../GlobalData/LexParseGlobalDataDef.h"

using namespace std;



class CLex;
typedef bool (CLex::*_HandleProcessSymbolStatus)(int nCurrentState);
struct SSymbolHandler
{
	_HandleProcessSymbolStatus  m_handlerOfProcessSymbol;

	SSymbolHandler()
		:m_handlerOfProcessSymbol(NULL)
	{ }
};

typedef map<eEndSymbolType, SSymbolHandler> SymbolHandlerMap;

class CLex
{
public:
	CLex();

	~CLex();

public:

public:
	bool GenTokenFromSourceFile();

private:
	bool processNewStateOfLex(int nProcessState);

	void wordBuffBackOneCharacter();

	eEndSymbolType getEndSymbolTypeByState(int nCheckStatus);

private:
	bool handleProcessIdentifier(int nCurrentState);
	bool handleProcessConstant(int nCurrentState);
	bool handleProcessBoundSymbol(int nCurrentState);
	bool handleProcessOperatorSymbol(int nCurrentState);
	bool handleProcessTwoPointSymbol(int nCurrentState);
	bool handleProcessOtherSymbol(int nCurrentState);

private:	
	std::string m_szSourceContent;	// Դ�����ַ���
	std::string m_strWordBuff;      // ���ʻ�����
	int m_nRowIndex;
	int m_nStateValue;

	int m_nReaderPosition;

private:
	SymbolHandlerMap  m_mapSymbolHandlerMap;
};

typedef Singleton<CLex> LexPaserInst;