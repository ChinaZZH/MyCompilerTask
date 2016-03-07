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
#include "CommonObjectInfo.h"
#include <map>

struct LabelInfo :CommonObjectInfo
{
	bool m_bDef;  // 是否已经定义
	bool m_bUse;  // 是否已经使用

	LabelInfo()
		:m_bDef(false)
		, m_bUse(false)
	{ }

	void initDefValue(bool bInitDefValue){
		this->m_bDef = bInitDefValue;
	}

	void initUseValue(bool bInitUseValue){
		this->m_bUse = bInitUseValue;
	}
};

typedef std::map<int, LabelInfo> LabelInfoMap;
class LabelInfoTable
{
public:
	LabelInfoTable();
	~LabelInfoTable();

public:
	bool addLabelInfo(LabelInfo newLabelInfo);

	int searchLableInfoTable(const int nProcIdValue, const std::string& strLableName);

private:
	LabelInfoMap m_mapLabelInfoTable;
};