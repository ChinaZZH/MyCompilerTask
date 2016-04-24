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
#include "../Common/Singleton.h"
#include <string>
#include "ConstInfoTable.h"
#include "TypeSysTable.h"
#include "VarInfoTable.h"
#include "ProcInfoTable.h"
#include "LabelInfoTable.h"
#include "EnumInfoTable.h"
#include "TypeInfoUserTable.h"
#include "UseFileTable.h"


struct TypeInfo;

class SymbolTable
{
public:
	SymbolTable();

	~SymbolTable();

public:
	int getSerialId();

public:
	void init();

// ����ϵͳ��
public:
	void initTypeInfoByString(const std::string& szTypeInfoString);

// �������
public:
	int recConstTbl(const std::string& szValue, int iType);

	int searchConstInfoTable(const int nProcId, const std::string& strConstName);
	
	ConstInfo* getEmptyConstInfoByName(const std::string& strConstName);

	ConstInfo* getConstDataByAddressValue(int nAddressValue);

// ������
public:
	int searchLableInfoTable(const int nProcId, const std::string& strLableName);

	bool addLabelInfo(LabelInfo newLabelInfo);

// �������
public:
	int addNewProcInfo(ProcInfo newProcInfo);

	bool compareToProcName(int nStackTopProcId, const std::string& strCompareValue);

	bool compareProcNameIsSame(const std::string& strCompareValu);

	ProcInfo* getRecenetlyProcIndex();

// �������
public:
	void addNewVarToSpecficProcId(VarInfo newVarInfo);

	int searchVarInfoTable(int nStackTopProcId, const std::string& strCompareValue);

// ������Ϣ��
public:
	int searchTypeInfoTable(int nStackTopProcId, const std::string& strCompareValue);
	
	int addNewUserTypeInfoToTable(const std::string& strInitTypeName, int nProcAddress);

	TypeInfo* getTypeInfoFromTableAddress(int nTypeAddressValue);

	int getTopTypeUserInfoAddress();

// ö��ֵ
public:
	int searchEnumInfoTable(int nStackTopProcId, const std::string& strCompareValue);

	int createNewEnumUnitSpace();

	int getNewEnumBeginAddressValue();

	int getEmptyOrNewEnumAddressValue();

	EnumInfo* getEnumInfoByEnumAddress(int nEnumAddress);

	int getNewEnumAddressValue();

	void reSetNewEnumBeginAddressToNull();

// �ļ�����˵��
public:
	int searchUseFileTable(const std::string& strUseFileName);

	int addNewUseFlieData(const std::string& strUseFileName);

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
	UseFileTable    m_useFileTable;
}; 

typedef Singleton<SymbolTable> SymbolTableInst;

