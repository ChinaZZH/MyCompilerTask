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

#pragma once
#include <string>
#include <vector>
#include <map>

class CommonLib
{
public:
	static std::string FileRead(std::string szFileName);

	static std::string StrErase(std::string szSourceContent, char eraseElement);

	static std::string trim(std::string str);

	static std::string ltrim(std::string str);

	static std::string rtrim(std::string str);

	static std::string upperCase(std::string strNeedCastString);
};



