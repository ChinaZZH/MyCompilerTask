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
#include <iostream>
using namespace std;

struct CommonObjectInfo
{
	std::string m_strName;  // 对应的名字
	int m_nProcIndex;       // 所属过程的指针

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