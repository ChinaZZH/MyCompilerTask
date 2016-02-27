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