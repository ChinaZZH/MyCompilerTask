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

using namespace std;

struct LineInfo
{
	int m_iRow;
	std::string m_szFileName;
	LineInfo(int iRow, std::string szFileName);
	LineInfo();
};

struct CToken
{
	CToken();
	int m_nWordStatus;
	std::string m_szContentValue;
	LineInfo m_LineInfo;
	CToken(int nWordStatus, std::string szContent, int iRow, std::string szFileName);
	~CToken(void);
};


struct ErrorInfo
{
	std::string m_szErrStr;
	std::string m_szFileName;
	int m_iRow;
};