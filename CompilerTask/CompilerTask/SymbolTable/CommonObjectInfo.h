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
#include <string>
#include <iostream>
using namespace std;

struct CommonObjectInfo
{
	std::string m_strName;  // ��Ӧ������
	int m_nProcIndex;       // �������̵�ָ��

	CommonObjectInfo()
		:m_strName("")
		, m_nProcIndex(-1)
	{ 
		
	}

	virtual ~CommonObjectInfo() 
	{ }

	bool compare(const int nProcIdValue, const std::string& strNameValue) const
	{
		bool bEqualOfCompare = false;
		if(this->m_nProcIndex != nProcIdValue){
			return bEqualOfCompare;
		}

		if(0 != m_strName.compare(strNameValue)){
			return bEqualOfCompare;
		}

		bEqualOfCompare = true;
		return bEqualOfCompare;
	}

	bool isEmptyObject(){
		if(-1 == m_nProcIndex){
			return true;
		}

		return false;
	}

	void initStrName(const std::string& strNewName){
		this->m_strName = strNewName;
	}

	void initProcIndex(int nProcIdValue){
		this->m_nProcIndex = nProcIdValue;
	}
};