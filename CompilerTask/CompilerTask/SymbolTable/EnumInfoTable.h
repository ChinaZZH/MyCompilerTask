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

class EnumInfoTable
{
public:
	EnumInfoTable();
	~EnumInfoTable();

private:
	std::vector<EnumInfo>  m_vecEnumInfoTable;
};