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

class UserDefineTypeSemanticser : public BaseSemanticser
{
public:
	UserDefineTypeSemanticser();
	~UserDefineTypeSemanticser();

public:
	virtual bool processSemanticsParser();

	virtual eSemansticeParserTypeValue returnSemanticserEnumValue();

private:
	bool processUserDefineOfSetType(int nLinkTypeAddress);
	bool processUserDefineOfFunctionParam(int nLinkTypeAddress);
	bool processUserDefineOfFunctionRetValue(int nLinkTypeAddress);
	bool processUserDefine(int nLinkTypeAddress);
};