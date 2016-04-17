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