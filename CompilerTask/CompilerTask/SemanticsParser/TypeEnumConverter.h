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
#include "../GlobalData/SyntaxParserGlobalDataDef.h"

class TypeEnumConverter
{
public:
	TypeEnumConverter();
	~TypeEnumConverter();

public:
	static eDataStoreEnumValue wordStatusToDataStoreType(int nWordStatus);
};