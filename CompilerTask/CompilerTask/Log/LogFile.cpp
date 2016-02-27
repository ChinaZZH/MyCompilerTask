
#include "LogFile.h"
#include <stdio.h>



LogFile::LogFile()
:m_pLogFile(NULL)
{
	m_strLogFileName.clear();

	this->initFile();
}

LogFile::~LogFile()
{
	if(NULL != m_pLogFile){
		fclose(m_pLogFile);
	}
}

void LogFile::logError(const std::string& strErrorInfo, const std::string& strFileName, int nLineValue)
{
	std::string strDateTime = this->getStringOfTime();
	char logErrorInfo[1024] = { 0 };
	sprintf_s(logErrorInfo, "%s   %s at %s, %d", strDateTime.c_str(), strErrorInfo.c_str(), strFileName.c_str(), nLineValue);
	
	// 输入到控制台
	std::cout << logErrorInfo << std::endl;

	// 输入到文件
	std::string strTempLogName = calculateDateOfFileName();
	if(0 != m_strLogFileName.compare(strTempLogName)){
		fclose(m_pLogFile);

		m_strLogFileName = strTempLogName;
		m_pLogFile = fopen(m_strLogFileName.c_str(), "wb");
	}

	if(NULL == m_pLogFile){
		std::cout << "日志文件名出错 指针为空" << std::endl;
		return;
	}

	
	fprintf(m_pLogFile, "%s\r\n", logErrorInfo);
}

void LogFile::initFile()
{
	m_strLogFileName = this->calculateDateOfFileName();
	if(true == m_strLogFileName.empty()){
		std::cout << "日志文件名出错" << std::endl;
		return;
	}

	m_pLogFile = fopen(m_strLogFileName.c_str(), "wb");
	if(NULL == m_pLogFile){
		std::cout << "打开日志文件出错 文件:" << m_strLogFileName.c_str() << std::endl;
		return;
	}
}


std::string LogFile::calculateDateOfFileName()
{
	// 获取系统当前时间
	time_t nowtime;
	nowtime = time(&nowtime);

	struct tm *timeinfo;
	timeinfo = localtime(&nowtime);

	// 拼接成字符串
	char strDateTime[12] = { 0 };
	int nYear = timeinfo->tm_year + 1900;
	int nMonth = timeinfo->tm_mon + 1;
	int nDay = timeinfo->tm_mday;
	sprintf_s(strDateTime, "%02d-%02d-%02d", nYear, nMonth, nDay);

	std::string strLogFileName("Log/ErrorLog_");
	strLogFileName.append(strDateTime);
	return strLogFileName;
}


std::string LogFile::getStringOfTime()
{
	time_t nowtime;
	nowtime = time(&nowtime);

	struct tm *timeinfo;
	timeinfo = localtime(&nowtime);

	char strDateTime[24] = { 0 };
	int nYear = timeinfo->tm_year + 1900;
	int nMonth = timeinfo->tm_mon + 1;
	int nDay = timeinfo->tm_mday;
	sprintf_s(strDateTime, "%02d-%02d-%02d %02d::%02d::%02d", nYear, nMonth, nDay, timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
	return strDateTime;
}
