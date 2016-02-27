#include "ErrorProcess.h"
#include "Global.h"
#include <iostream>
#include "Structure.h"
#include "IntStringConverter.h"
#include "../ConfigFile/State.h"



void EmitErrorFile::EmitErrorOfCodeRow(int nErrorRowIndex, std::string szErrContent)
{
	std::string strRowValue = IntStringConverter::intValueConvertToString(nErrorRowIndex);
	std::string strSourceFileName = ConfigFileDataInst::instance().getSourceFile();

	EmitErrorFile::EmitError(strSourceFileName + "(" + strRowValue + "):" + szErrContent);
}

void EmitErrorFile::EmitError(std::string szErr, CToken token)
{

}

void EmitErrorFile::EmitError(std::string szErr)
{
	ErrorInfo tmp;
	tmp.m_szErrStr = szErr;
	tmp.m_iRow = 0;
	ErrorProcess.push_back(tmp);
}

void EmitErrorFile::PrintError()
{
	cout << endl;
	if(true == ErrorProcess.empty())
	{
		cout << '\n' << "Óï·¨´íÎó" << endl;
		return;
	}

	for(unsigned int i = 0; i < ErrorProcess.size(); ++i)
	{
		int nTempRow = ErrorProcess[i].m_iRow;
		if(0 == nTempRow)
		{
			cout << "[Error]" << ErrorProcess[i].m_szErrStr.c_str() << endl;
			continue;
		}

		cout << "[Error]" << ErrorProcess[i].m_szFileName.c_str()
			<< "(" << ErrorProcess[i].m_iRow << "):"
			<< ErrorProcess[i].m_szErrStr.c_str() << endl;
	}
}
