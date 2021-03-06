/********************************************************************
            Copyright (c) 2015
                   All rights reserved
         
    创建日期：  2015年 月 日 时 分
    文件名称：  
    说    明：       
    
    当前版本：  
    作    者：  郑祖煌
    概    述：      

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