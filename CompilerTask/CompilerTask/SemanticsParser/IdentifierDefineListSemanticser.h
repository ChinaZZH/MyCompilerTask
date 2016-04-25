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

class IdentifierDefineListSemanticser : public BaseSemanticser
{
public:
	IdentifierDefineListSemanticser();
	~IdentifierDefineListSemanticser();

public:
	virtual bool processSemanticsParser();

	virtual eSemansticeParserTypeValue returnSemanticserEnumValue();

private:
	bool processEnumTypeIdentifierList();

	bool processRecordIdentifierList();

	bool processFieldOfRecordList();

	bool processParamTypeOfFunction();

	bool processVarIdentifierList();

	bool processFileIdentifierList();
};
