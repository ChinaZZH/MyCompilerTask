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
#include <vector>

struct UseFileData
{
	std::string  m_strFileName;
	bool  m_bFileExistFlag;

	UseFileData(std::string strFileName, bool bFileExistFlag)
		:m_strFileName(strFileName)
		, m_bFileExistFlag(bFileExistFlag)
	{ }
};

typedef std::vector<UseFileData>  UseFileDataVec;

class UseFileTable
{
public:
	UseFileTable();
	~UseFileTable();


public:
	int searchUseFileTable(const std::string& strUseFileName);

	int addNewUseFlieData(const std::string& strUseFileName);

private:
	UseFileDataVec  m_vecUseFileData;
};