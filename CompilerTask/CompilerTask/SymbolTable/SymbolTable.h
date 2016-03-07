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
#include "ProcParserStack.h"



class SymbolTable
{
public:
	SymbolTable();

	~SymbolTable();

public:
	void init();

	void initTypeInfoByString(const std::string& szTypeInfoString);

public:
	int recConstTbl(const std::string& szValue, int iType);

	int searchConstInfoTable(const int nProcId, const std::string& strConstName);
	
	ConstInfo* getEmptyConstInfoByName(const std::string& strConstName);

public:
	int searchLableInfoTable(const int nProcId, const std::string& strLableName);

	bool addLabelInfo(LabelInfo newLabelInfo);

public:
	int addNewProcInfo(ProcInfo newProcInfo);

	bool compareToProcName(int nStackTopProcId, const std::string& strCompareValue);

public:
	int getProcStackTop();

	bool newProcCallAddToStack(int nProcIdAddress);

private:
	ConstInfoTable  m_constInfoTable;
	TypeSysTable    m_typeSysTable;
	VarInfoTable    m_varInfoTable;

	ProcInfoTable   m_procInfoTable;
	LabelInfoTable  m_labelInfoTable;
	EnumInfoTable   m_enumInfoTable;

	ProcParserStack m_procParserStack;
}; 

typedef Singleton<SymbolTable> SymbolTableInst;

