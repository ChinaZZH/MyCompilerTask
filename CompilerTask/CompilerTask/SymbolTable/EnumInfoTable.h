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

private:
	EnumInfoVec  m_vecEnumInfoTable;
};