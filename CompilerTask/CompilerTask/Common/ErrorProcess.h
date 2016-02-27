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

#include <string>
#include "Structure.h"

class EmitErrorFile
{
public:
	EmitErrorFile();

	~EmitErrorFile();

public:
	static void EmitErrorOfCodeRow(int nErrorRowIndex, std::string szErrContent);

	static void EmitError(std::string szErr);

	static void EmitError(std::string szErr, CToken token);

	static void PrintError();
};
