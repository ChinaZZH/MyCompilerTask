
#include "Structure.h"

LineInfo::LineInfo()
{

}
LineInfo::LineInfo(int iRow, std::string szFileName)
{
	m_iRow = iRow;
	m_szFileName = szFileName;
}

CToken::CToken()
{

}

CToken::CToken(int nWordStatus, std::string szContent, int iRow, std::string szFileName)
:m_nWordStatus(nWordStatus)
, m_szContentValue(szContent)
, m_LineInfo(iRow, szFileName)
{
	
}

CToken::~CToken(void)
{
}
