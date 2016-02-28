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
	std::string m_szSourceContent;	// 源代码字符串
	std::string m_strWordBuff;      // 单词缓冲区
	int m_nRowIndex;
	int m_nStateValue;

	int m_nReaderPosition;

private:
	SymbolHandlerMap  m_mapSymbolHandlerMap;
};

typedef Singleton<CLex> LexPaserInst;