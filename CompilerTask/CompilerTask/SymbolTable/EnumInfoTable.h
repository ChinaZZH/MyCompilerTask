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
#include <vector>

struct EnumInfo :CommonObjectInfo
{

};

typedef std::vector<EnumInfo> EnumInfoVec;

class EnumInfoTable
{
public:
	EnumInfoTable();
	~EnumInfoTable();

public:
	int searchEnumInfoTable(int nStackTopProcId, const std::string& strCompareValue);

	int createNewEnumUnitSpace();

	int getNewEnumAddressValue();

	int getEmptyOrNewEnumAddressValue();

	int getNewEnumBeginAddressValue();

	EnumInfo* getEnumInfoByEnumAddress(int nEnumAddress);

	void reSetNewEnumBeginAddressToNull();

private:
	EnumInfoVec  m_vecEnumInfoTable;
	int m_nNewEnumBeginAddress;
};