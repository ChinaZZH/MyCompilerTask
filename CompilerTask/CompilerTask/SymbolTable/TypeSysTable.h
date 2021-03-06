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
#include <vector>
#include "../GlobalData/TypeSystemConfig.h"

typedef std::vector<TypeSysInfo> TypeSysTblVec;			//类型系统表

class TypeSysTable
{
public:
	TypeSysTable();
	~TypeSysTable();

public:
	void addNewTypeSysUnit(TypeSysInfo newTypeSysInfo);

private:
	TypeSysTblVec  m_vecTypeSysTable;
};