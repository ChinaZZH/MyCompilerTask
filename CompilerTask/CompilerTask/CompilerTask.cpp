// CompilerTask.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"


// Compiler.cpp : 定义控制台应用程序的入口点。
#include <iostream>
#include <vector>
#include "GlobalData/KeyWordTable.h"
#include "GlobalData/LexStateTable.h"
#include "Common/Structure.h"
#include "ConfigFile/State.h"
#include "Common/ErrorProcess.h"
#include "LexParser/LexParser.h"
#include "Log/LogFile.h"

using namespace std;
extern std::vector<CToken> TokenList;


int _tmain(int argc, char* argv[])
{
	//处理命令行参数
	bool bCommandInit = ConfigFileDataInst::instance().readConfigData(argc, argv);
	if (false == bCommandInit)
	{
		EmitErrorFile::PrintError();
		system("pause");
		return 1;
	}

	KeyWordTableInst::instance().initData();
	LexStateTableInst::instance().initData();

	std::cout << "词法分析开始......." << std::endl;
	bool bTokenResult = LexPaserInst::instance().GenTokenFromSourceFile();
	if (false == bTokenResult)
	{
		EmitErrorFile::PrintError();
		system("pause");
		return 1;
	}

	std::cout << "词法分析成功, 继续语法分析" << std::endl;
	system("pause");
	return 0;
}



