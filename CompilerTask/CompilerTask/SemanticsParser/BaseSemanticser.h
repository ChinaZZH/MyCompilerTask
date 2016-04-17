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
#include "SemanticsEnumDef.h"

class BaseSemanticser;
class CToken;

class BaseSemanticser
{
public:
	BaseSemanticser();

	virtual ~BaseSemanticser();

public:
	virtual bool processSemanticsParser();

	virtual eSemansticeParserTypeValue returnSemanticserEnumValue();

protected:
	bool checkCompareIsSameNameWithWord(int nTopProcId, const std::string& strWordValue);

	const CToken* getTokenWordByCurrentWordIndex();

	const CToken* getTokenWordByLastWordIndex();

	const CToken* getTokenWordByLastSomeWordIndex(int nLastWordIndex);
};