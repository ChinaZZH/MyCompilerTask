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



