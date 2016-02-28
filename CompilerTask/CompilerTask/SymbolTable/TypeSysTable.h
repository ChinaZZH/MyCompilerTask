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
#include <vector>
#include "../GlobalData/TypeSystemConfig.h"

typedef std::vector<TypeSysInfo> TypeSysTblVec;			//����ϵͳ��

class TypeSysTable
{
public:
	TypeSysTable();
	~TypeSysTable();

public:
	void addNewTypeSysUnit(TypeSysInfo newTypeSysInfo);

private:
	TypeSysTblVec  m_vecTypeSysTable;
};