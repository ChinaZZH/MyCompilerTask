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
#include <stack>

enum eSemanticsStackIdFlag
{
	eSPIF_VarIdentifierListStart = 6,
};

typedef std::stack<eSemanticsStackIdFlag> SemanticserParserFlagStack;

// 语法分析当前标识
class SemanticsParserIdFlag
{
public:
	SemanticsParserIdFlag();
	~SemanticsParserIdFlag();

public:
	void startNewSemanticserParserFlag(eSemanticsStackIdFlag newFlag);

	eSemanticsStackIdFlag getCurrentSemanticsParserId();

	void endSemanticserParserFlag();

private:
	SemanticserParserFlagStack m_stackSemanticserParserFlag;
};