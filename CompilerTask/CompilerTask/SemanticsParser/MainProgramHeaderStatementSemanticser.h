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

class MainProgramHeaderStatementSemanticser : public BaseSemanticser
{
public:
	MainProgramHeaderStatementSemanticser();
	~MainProgramHeaderStatementSemanticser();

public:
	virtual bool processSemanticsParser();

	virtual eSemansticeParserTypeValue returnSemanticserEnumValue();

private:
	bool initBeforeSemanticserStart();
};