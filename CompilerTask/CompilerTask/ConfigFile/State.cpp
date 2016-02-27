
#include "State.h"
#include "../Common/ErrorProcess.h"
#include <io.h>
#include "IniFile.h"


ConfigFile::ConfigFile()
:m_szSourceFile("")
, m_szSysDir("")
, m_szOutputFile("")

, m_szSysLib("")
, m_szUserLib("")
, m_szErrFile("")
, m_bOpti(false)
{

}

ConfigFile::~ConfigFile()
{

}

bool ConfigFile::readConfigData(int argc, char** argv)
{
	
	CIniFile iniFile;
	iniFile.OpenIniFile("Main.ini");

	m_szSysDir = iniFile.ReadString("PathName", "SysDir", "Sys");
	m_szSysDir = this->addSysPathDirTag(m_szSysDir);

	m_szSysLib = iniFile.ReadString("PathName", "SysLibDir", "Sys");
	m_szSysLib = this->addSysPathDirTag(m_szSysLib);

	m_szUserLib = iniFile.ReadString("PathName", "UserLibDir", "User");
	m_szUserLib = this->addSysPathDirTag(m_szUserLib);

	m_szSourceFile = iniFile.ReadString("FileName", "SourceCodeFile", "MyCode.txt");
	m_szSourceFile = m_szUserLib + m_szSourceFile;

	m_szErrFile = iniFile.ReadString("FileName", "ErrorFile", "ErrorFile.txt");
	m_szErrFile = m_szUserLib + m_szErrFile;

	m_szOutputFile = iniFile.ReadString("FileName", "OutputFile", "OutputFile.txt");
	m_szOutputFile = m_szUserLib + m_szOutputFile;
	iniFile.CloseIniFile();

	bool bAceess = false;
	if (-1 == _access(m_szSysLib.c_str(), 2))
	{
		EmitErrorFile::EmitError("系统库路径未知");
		return bAceess;
	}

	if (-1 == _access(m_szUserLib.c_str(), 2))
	{
		EmitErrorFile::EmitError("用户库路径未知");
		return bAceess;
	}

	std::string szLexPaserInstFile = m_szSysDir + "Lex.txt";
	if (-1 == _access(szLexPaserInstFile.c_str(), 2))
	{
		EmitErrorFile::EmitError("无法找到文件Lex.txt");
		return bAceess;
	}

	std::string szKeyWords = m_szSysDir + "keywords.txt";
	if (-1 == _access(szKeyWords.c_str(), 2))
	{
		EmitErrorFile::EmitError("无法找到文件keywords.txt");
		return bAceess;
	}

	std::string szTypeSys = m_szSysDir + "TypeSys.txt";
	if (-1 == _access(szTypeSys.c_str(), 2))
	{
		EmitErrorFile::EmitError("无法找到文件TypeSys.txt");
		return bAceess;
	}

	std::string szAsmScheme = m_szSysDir + "AsmScheme.txt";
	if (-1 == _access(szAsmScheme.c_str(), 2))
	{
		EmitErrorFile::EmitError("无法找到文件AsmScheme.txt");
		return bAceess;
	}

	std::string szPeepHoleScheme = m_szSysDir + "PeepHoleScheme.txt";
	if (-1 == _access(szPeepHoleScheme.c_str(), 2))
	{
		EmitErrorFile::EmitError("无法找到文件PeepHoleScheme.txt");
		return bAceess;
	}


	if (-1 == _access(m_szSourceFile.c_str(), 2))
	{
		EmitErrorFile::EmitError("无法找到文件" + m_szSourceFile);
		return bAceess;
	}

	if(m_szOutputFile.empty())
	{
		EmitErrorFile::EmitError("缺少输出文件名");
		return bAceess;
	}

	bAceess = true;
	return bAceess;
}

std::string ConfigFile::addSysPathDirTag(std::string& strPathDir)
{
	int nStringLength = strPathDir.length();
	if(nStringLength <= 0)
	{
		return strPathDir;
	}

	if(strPathDir[strPathDir.length()-1] != '\\')
	{
		strPathDir += '\\';
	}

	return strPathDir;
}
