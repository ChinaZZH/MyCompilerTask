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
#include "../Common/Singleton.h"
#include <string>
#include "ConstInfoTable.h"
#include "TypeSysTable.h"
#include "VarInfoTable.h"
#include "ProcInfoTable.h"
#include "LabelInfoTable.h"
#include "EnumInfoTable.h"
#include "TypeInfoUserTable.h"



class SymbolTable
{
public:
	SymbolTable();

	~SymbolTable();

public:
	int getSerialId();

public:
	void init();

// 类型系统表
public:
	void initTypeInfoByString(const std::string& szTypeInfoString);

// 常量相关
public:
	int recConstTbl(const std::string& szValue, int iType);

	int searchConstInfoTable(const int nProcId, const std::string& strConstName);
	
	ConstInfo* getEmptyConstInfoByName(const std::string& strConstName);

// 标号相关
public:
	int searchLableInfoTable(const int nProcId, const std::string& strLableName);

	bool addLabelInfo(LabelInfo newLabelInfo);

// 过程相关
public:
	int addNewProcInfo(ProcInfo newProcInfo);

	bool compareToProcName(int nStackTopProcId, const std::string& strCompareValue);

	bool compareProcNameIsSame(const std::string& strCompareValu);

// 变量相关
public:
	void addNewVarToSpecficProcId(VarInfo newVarInfo);

	int searchVarInfoTable(int nStackTopProcId, const std::string& strCompareValue);

// 类型信息表
public:
	int searchTypeInfoTable(int nStackTopProcId, const std::string& strCompareValue);
	
	int addNewUserTypeInfoToTable(TypeInfo newUserTypeInfo);

// 枚举值
public:
	int searchEnumInfoTable(int nStackTopProcId, const std::string& strCompareValue);

private:
	int  m_nSerialId;

private:
	ConstInfoTable  m_constInfoTable;
	TypeSysTable    m_typeSysTable;
	VarInfoTable    m_varInfoTable;

	ProcInfoTable   m_procInfoTable;
	LabelInfoTable  m_labelInfoTable;
	EnumInfoTable   m_enumInfoTable;

	TypeInfoUserTable  m_typeInfoUserTable;
}; 

typedef Singleton<SymbolTable> SymbolTableInst;

