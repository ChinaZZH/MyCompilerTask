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

class EnumTypeDefineBeforeIdentifier : public BaseSemanticser
{
public:
	EnumTypeDefineBeforeIdentifier();
	~EnumTypeDefineBeforeIdentifier();

public:
	virtual bool processSemanticsParser();

	virtual eSemansticeParserTypeValue returnSemanticserEnumValue();

private:
	bool processSetOfEnumElementCondition(TypeInfo* pTypeInfo, int nEmptyNewEnumAddress);
};