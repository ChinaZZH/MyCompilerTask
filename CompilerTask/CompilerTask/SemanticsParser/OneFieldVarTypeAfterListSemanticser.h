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

#include "BaseSemanticser.h"
#include "SemanticsEnumDef.h"


class OneFieldVarTypeAfterListSemanticser : public BaseSemanticser
{
public:
	OneFieldVarTypeAfterListSemanticser();
	~OneFieldVarTypeAfterListSemanticser();

public:
	virtual bool processSemanticsParser();

	virtual eSemansticeParserTypeValue returnSemanticserEnumValue();
};