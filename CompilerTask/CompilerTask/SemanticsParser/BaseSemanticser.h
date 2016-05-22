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
#include <string>

using namespace std;

class  BaseSemanticser;
struct CToken;
struct TypeInfo;

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

protected:
	TypeInfo* getTypeInfoByParsingTypePosition();
};