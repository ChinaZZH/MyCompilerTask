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
