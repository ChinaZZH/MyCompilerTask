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
#include "../BaseSemanticser.h"
#include "../SemanticsEnumDef.h"


class IncludeFileBeforeFileNameSemanticser : public BaseSemanticser
{
public:
	IncludeFileBeforeFileNameSemanticser();
	~IncludeFileBeforeFileNameSemanticser();

public:
	virtual bool processSemanticsParser();

	virtual eSemansticeParserTypeValue returnSemanticserEnumValue();
};