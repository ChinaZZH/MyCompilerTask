/********************************************************************
            Copyright (c) 2015
                   All rights reserved
         
    �������ڣ�  2016�� �� �� ʱ ��
    �ļ����ƣ�  
    ˵    ����       
    
    ��ǰ�汾��  
    ��    �ߣ�  ֣���
    ��    ����      

*********************************************************************/

#pragma once
#include <string>
#include <map>

//ConstInfo
typedef std::map<int, int> ConstInfoMap;

class ConstInfoTable
{
public:
	ConstInfoTable();
	~ConstInfoTable();

public:
	int RecConstTbl(const std::string& szValue, int iType);

public:
	ConstInfoMap  m_mapConstInfoTable;

};