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
#include <string>

typedef std::stack<std::string> FieldInfoStack;

class FieldOfRecordParserHandler
{
public:
	FieldOfRecordParserHandler();
	~FieldOfRecordParserHandler();

public:
	void clearData();

public:
	void pushNewDataToConstFieldStack(const std::string& strConstFieldStack);

	std::string getConstFieldStackTop();
	
	void popConstFieldStack();

public:
	void pushNewDataToFlagFieldStack(const std::string& strFlagFieldStack);
	
	std::string getFlagFieldStackTop();
	
	void popFlagFieldStack();

private:
	FieldInfoStack  m_stackVarFieldConstValue;
	FieldInfoStack  m_stackVarFieldFlagValue;
};