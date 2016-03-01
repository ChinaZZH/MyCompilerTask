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
#include <map>
#include "CommonObjectInfo.h"

struct VarInfo :CommonObjectInfo
{
	enum Rank{
		eR_Para = 0,
		eR_Var,
		eR_Ret,
	};

	int  m_nTypeLinkAddr;   // 变量类型描述指针
	Rank m_eRank;           // 变量的类型
	bool m_bDirectRef;      // 直接寻址/间接寻址
	int  m_nMemoryAlloAddr; // 逻辑存储地址
	std::string strReg;
	bool m_bUsedAlready;    // 是否已经被使用

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

typedef std::map<int, VarInfo> VarTableInfoMap;			//变量信息表

class VarInfoTable
{
public:
	VarInfoTable();
	~VarInfoTable();

private:
	VarTableInfoMap  m_mapVarIntoTable;
};