/********************************************************************
            Copyright (c) 2015
                   All rights reserved
         
    创建日期：  2016年 月 日 时 分
    文件名称：  
    说    明：       
    
    当前版本：  
    作    者：  郑祖煌
    概    述：      

*********************************************************************/

#pragma once
#include "../Common/Singleton.h"

struct TypeSysInfo
{
	int  m_nOpSymbol;     // 操作符
	int  m_nOpNumType1;   // 操作数1
	int  m_nOpNumType2;   // 操作数2
	int  m_nResultType;   // 结果的类型编码

	int  m_nConstProcessId; // 常量操作码
	int  m_nVarProcessId;   // 变量操作码
	int  m_nIrOpSymbol;     // IR操作符
	int  m_nOpNum1Convert;  // 操作数1的类型转换
	int  m_nOpNum2Convert;  // 操作数2的类型转换

	TypeSysInfo()
		:m_nOpSymbol(0)
		, m_nOpNumType1(0)
		, m_nOpNumType2(0)
		, m_nResultType(0)

		, m_nConstProcessId(0)
		, m_nVarProcessId(0)
		, m_nIrOpSymbol(0)
		, m_nOpNum1Convert(0)
		, m_nOpNum2Convert(0)
	{ }
};

class TypeSystemConfig
{
public:
	TypeSystemConfig();
	~TypeSystemConfig();

public:
	void initTypeSysTbl();

private:
	const static int TYPE_TABLE_FIELD_NUM = 35;
};

typedef  Singleton<TypeSystemConfig> TypeSystemConfigInst;
