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

class VarDefineBeforeListSemanticser : public BaseSemanticser
{
public:
	VarDefineBeforeListSemanticser();
	~VarDefineBeforeListSemanticser();

public:
	virtual bool processSemanticsParser();

	virtual eSemansticeParserEnumValue returnSemanticserEnumValue();
};