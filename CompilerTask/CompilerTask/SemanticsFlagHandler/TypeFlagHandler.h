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
#include <stack>


// 类型标志 枚举值
enum eTypeFlagEnumValue
{
	eTFEV_MainTypeValue   = 0,
	eTFEV_RecordTypeValue = 1,  // 记录类型
	eTFEV_SetTypeValue    = 2,  // 集合类型
	eTFEV_ArrayTypeValue  = 3,  // 数组类型
	eTFEV_FileTypeValue   = 4,  // 文件类型
	eTFEV_ProcTypeValue   = 5,  // 过程类型

	eTFEV_FunctionTypeValue    = 6,  // 函数类型
	eTFEV_FunctionRetTypeValue = 7,  // 函数返回值类型
};

typedef std::stack<int> TypeFlagStack;

class TypeFlagHandler
{
public:
	TypeFlagHandler();
	~TypeFlagHandler();

public:
	void clearData();

	void pushTypeFlagValueToStack(eTypeFlagEnumValue typeFlagEnum);

	eTypeFlagEnumValue getTopTypeFlagValue();

	eTypeFlagEnumValue popTypeFlagValueFromStack();

private:
	TypeFlagStack m_stackTypeFlag;
};

