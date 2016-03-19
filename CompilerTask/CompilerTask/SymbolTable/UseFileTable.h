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