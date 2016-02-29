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

struct CommonObjectInfo
{
	std::string m_strName;  // 对应的名字
	int m_nProcIndex;       // 所属过程的指针

	CommonObjectInfo()
		:m_strName(0)
		, m_nProcIndex(0)
	{ }
};