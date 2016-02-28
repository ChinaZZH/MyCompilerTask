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
#include "SymbolTable/SymbolTable.h"
#include "GlobalData/TypeSystemConfig.h"
#include "GlobalData/SyntaxParserTable.h"
#include "SyntaxParser/SyntaxParser.h"

using namespace std;


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
	TypeSystemConfigInst::instance().initTypeSysTbl();
	SyntaxParserTableInst::instance().init();
	SymbolTableInst::instance().init();

	// �ʷ�������ʼ��
	std::cout << "�ʷ�������ʼ......." << std::endl;
	bool bTokenResult = LexPaserInst::instance().GenTokenFromSourceFile();
	if(false == bTokenResult){
		EmitErrorFile::PrintError();
		system("pause");
		return 1;
	}
	std::cout << "�ʷ������ɹ�, �����﷨����" << std::endl;


	// �﷨�������ö�ȡ
	std::cout << std::endl << "�﷨������ʼ......." << std::endl;
	bool bProcessSyntax = SyntaxParserInst::instance().processSyntaxParse();
	if(false == bProcessSyntax){
		EmitErrorFile::PrintError();
		system("pause");
		return 1;
	}
	std::cout << "�﷨�����ɹ�" << std::endl;
	

	system("pause");
	return 0;
}



