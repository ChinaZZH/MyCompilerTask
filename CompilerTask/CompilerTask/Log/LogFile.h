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

#pragma  once

#include <iostream>
#include "../Common/Singleton.h"
#include <stdio.h>
#include <time.h>
#include <sys/utime.h>


using namespace std;

class LogFile
{
public:
	LogFile();

	~LogFile();

public:
	void logError(const std::string& strErrorInfo, const std::string& strFileName, int nLineValue);


private:
	void initFile();

	std::string calculateDateOfFileName();

	std::string getStringOfTime();

private:
	std::string m_strLogFileName;

	FILE* m_pLogFile;
};

typedef Singleton<LogFile> LogFileInst;