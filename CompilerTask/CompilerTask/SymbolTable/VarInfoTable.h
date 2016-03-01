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
#include "CommonObjectInfo.h"

struct VarInfo :CommonObjectInfo
{
	enum Rank{
		eR_Para = 0,
		eR_Var,
		eR_Ret,
	};

	int  m_nTypeLinkAddr;   // ������������ָ��
	Rank m_eRank;           // ����������
	bool m_bDirectRef;      // ֱ��Ѱַ/���Ѱַ
	int  m_nMemoryAlloAddr; // �߼��洢��ַ
	std::string strReg;
	bool m_bUsedAlready;    // �Ƿ��Ѿ���ʹ��

	VarInfo()
		:CommonObjectInfo()
		, m_nTypeLinkAddr(0)
		, m_eRank(eR_Para)
		, m_bDirectRef(false)
		, m_nMemoryAlloAddr(0)
		, strReg(0)
		, m_bUsedAlready(false)
	{  }
};

typedef std::map<int, VarInfo> VarTableInfoMap;			//������Ϣ��

class VarInfoTable
{
public:
	VarInfoTable();
	~VarInfoTable();

private:
	VarTableInfoMap  m_mapVarIntoTable;
};