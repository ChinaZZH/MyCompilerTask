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