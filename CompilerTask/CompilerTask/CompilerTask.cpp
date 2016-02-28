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
#include "SymbolTable/SymbolTable.h"
#include "GlobalData/TypeSystemConfig.h"
#include "GlobalData/SyntaxParserTable.h"
#include "SyntaxParser/SyntaxParser.h"

using namespace std;


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
	TypeSystemConfigInst::instance().initTypeSysTbl();
	SyntaxParserTableInst::instance().init();
	SymbolTableInst::instance().init();

	// 词法分析初始化
	std::cout << "词法分析开始......." << std::endl;
	bool bTokenResult = LexPaserInst::instance().GenTokenFromSourceFile();
	if(false == bTokenResult){
		EmitErrorFile::PrintError();
		system("pause");
		return 1;
	}
	std::cout << "词法分析成功, 继续语法分析" << std::endl;


	// 语法分析配置读取
	std::cout << std::endl << "语法分析开始......." << std::endl;
	bool bProcessSyntax = SyntaxParserInst::instance().processSyntaxParse();
	if(false == bProcessSyntax){
		EmitErrorFile::PrintError();
		system("pause");
		return 1;
	}
	std::cout << "语法分析成功" << std::endl;
	

	system("pause");
	return 0;
}



