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