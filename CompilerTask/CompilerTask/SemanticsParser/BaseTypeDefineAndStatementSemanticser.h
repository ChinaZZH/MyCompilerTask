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


class BaseTypeDefineAndStatementSemanticser : public BaseSemanticser
{
public:
	BaseTypeDefineAndStatementSemanticser();
	~BaseTypeDefineAndStatementSemanticser();

public:
	virtual bool processSemanticsParser();

	virtual eSemansticeParserTypeValue returnSemanticserEnumValue();

private:
	bool processSetTypeOfSemanticsParser();

	bool processFunctionParamOfSemanticsParser();

	bool processRetOfFunctionOfSemanticsParser();

	bool processSpecficOtherTypeOfSemanticsParser();
};