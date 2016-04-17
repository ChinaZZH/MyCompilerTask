#include "FieldOfRecordParserHandler.h"

FieldOfRecordParserHandler::FieldOfRecordParserHandler()
{

}

FieldOfRecordParserHandler::~FieldOfRecordParserHandler()
{

}

void FieldOfRecordParserHandler::clearData()
{
	while(false == m_stackVarFieldConstValue.empty()){
		m_stackVarFieldConstValue.pop();
	}

	while(false == m_stackVarFieldFlagValue.empty()){
		m_stackVarFieldFlagValue.pop();
	}
}

void FieldOfRecordParserHandler::pushNewDataToConstFieldStack(const std::string& strConstFieldStack)
{
	m_stackVarFieldConstValue.push(strConstFieldStack);
}

std::string FieldOfRecordParserHandler::getConstFieldStackTop()
{
	if(true == m_stackVarFieldConstValue.empty()){
		std::string strEmptyData;
		return strEmptyData;
	}

	std::string strConstFieldStack = m_stackVarFieldConstValue.top();
	return strConstFieldStack;
}

void FieldOfRecordParserHandler::popConstFieldStack()
{
	if(true == m_stackVarFieldConstValue.empty()){
		return;
	}

	m_stackVarFieldConstValue.pop();
}

void FieldOfRecordParserHandler::pushNewDataToFlagFieldStack(const std::string& strFlagFieldStack)
{
	m_stackVarFieldFlagValue.push(strFlagFieldStack);
}

std::string FieldOfRecordParserHandler::getFlagFieldStackTop()
{
	if(true == m_stackVarFieldFlagValue.empty()){
		std::string strEmptyData;
		return strEmptyData;
	}

	std::string strFlagFieldValue = m_stackVarFieldFlagValue.top();
	return strFlagFieldValue;
}

void FieldOfRecordParserHandler::popFlagFieldStack()
{
	if(true == m_stackVarFieldFlagValue.empty()){
		return;
	}

	m_stackVarFieldFlagValue.pop();
}
