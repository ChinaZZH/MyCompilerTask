// CompilerTask.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"


// Compiler.cpp : �������̨Ӧ�ó������ڵ㡣
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
	//���������в���
	bool bCommandInit = ConfigFileDataInst::instance().readConfigData(argc, argv);
	if (false == bCommandInit)
	{
		EmitErrorFile::PrintError();
		system("pause");
		return 1;
	}

	KeyWordTableInst::instance().initData();
	LexStateTableInst::instance().initData();

	std::cout << "�ʷ�������ʼ......." << std::endl;
	bool bTokenResult = LexPaserInst::instance().GenTokenFromSourceFile();
	if (false == bTokenResult)
	{
		EmitErrorFile::PrintError();
		system("pause");
		return 1;
	}

	std::cout << "�ʷ������ɹ�, �����﷨����" << std::endl;
	system("pause");
	return 0;
}



