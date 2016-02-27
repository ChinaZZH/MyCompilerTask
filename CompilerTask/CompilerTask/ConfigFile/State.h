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
#include "../Common/Singleton.h"

class ConfigFile
{
public:
	ConfigFile();

	~ConfigFile();

	bool readConfigData(int argc, char** argv);

public:
	std::string getSourceFile() { return m_szSourceFile;  }

	std::string getLexPaserInstFileName() { return (m_szSysDir + "Lex.txt"); }

	std::string getKeyWordsFile() { return (m_szSysDir + "keywords.txt");  }

private:
	std::string addSysPathDirTag(std::string& strPathDir);

private:
	std::string  m_szSourceFile;
	std::string  m_szSysDir;
	std::string  m_szOutputFile;

	std::string  m_szSysLib;
	std::string  m_szUserLib;
	std::string  m_szErrFile;

	bool m_bOpti;
};

typedef Singleton<ConfigFile> ConfigFileDataInst;