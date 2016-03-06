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
#include <set>

// 参数列表结构体
struct ParaInfo
{
	std::string m_strParamName;  // 形参名
	int  m_nParamType;           // 形参类型 
	int  m_nParamValueAddress;   // 形参所指向的地址

	enum AssignType{NULLVALUE, VAL, VAR} m_eAssignType; // 传值  还引用

	// 构造函数
	ParaInfo()
		:m_strParamName(0)
		, m_nParamType(0)
		, m_nParamValueAddress(0)
		, m_eAssignType(NULLVALUE)
	{ }
};

struct IRCode
{
	// 暂时不实现
};

struct ProcInfo
{
	std::string m_strProcName;           // 函数名   
	enum Rank{ Main, Sub } m_eRankValue; // 主函数 还是 子函数
	enum Type{ Procedure, Function, Type } m_eType;  // 函数类型(1.过程  2.函数 3.函数指针)
	
	std::vector<ParaInfo> m_ParaTable;  // 形参列表
	int  m_nReturnType;                 // 返回值类型 
	int  m_nReturnValueAddres;          // 返回值所指向的地址

	enum Flag { Forward, Extern, None } m_eFlag;
	int  m_nExternStrValue;
	int  m_nProcDefToken;

	enum CallType{NoneCall, Stdcall, Fastcall} m_eCallType;
	std::vector<IRCode> m_vecIrCodeList;          // 生成的代码序列表
	std::set<int>  m_setTmpMemShareList;          // 可共享存储区域临时变量的集合
	
	int  m_nValSize;         // 相关局部变量的空间大小
	int  m_nTmpLinkAddress;  // 临时变量的指针
	bool m_bUsed;            // 该 过程/函数 是否已被使用
	bool m_bTmpUsed;         // 是否使用了 临时变量

	// 构造函数
	ProcInfo()
		:m_strProcName(0)
		, m_eRankValue(Main)
		, m_eType(Procedure)
		, m_nReturnType(0)
		, m_nReturnValueAddres(0)

		, m_eFlag(None)
		, m_nExternStrValue(0)
		, m_nProcDefToken(0)
		, m_eCallType(NoneCall)
		, m_nValSize(0)
		, m_nTmpLinkAddress(0)
		, m_bUsed(false)
		, m_bTmpUsed(false)
	{  }
};


class ProcInfoTable
{
public:
	ProcInfoTable();
	~ProcInfoTable();

private:
	std::vector<ProcInfo> m_vecProcInfoTbl;			//过程信息表
};