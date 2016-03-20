#include "IdentifierListFlagHandler.h"

IdentifierListFlagHandler::IdentifierListFlagHandler()
{

}

IdentifierListFlagHandler::~IdentifierListFlagHandler()
{

}

void IdentifierListFlagHandler::clearData()
{
	while(false == m_stackSemanticserParserFlag.empty()){
		m_stackSemanticserParserFlag.pop();
	}
}

void IdentifierListFlagHandler::startNewSemanticserParserFlag(eSemanticsStackIdFlag newFlag)
{
	m_stackSemanticserParserFlag.push(newFlag);
}

eSemanticsStackIdFlag IdentifierListFlagHandler::getCurrentSemanticsParserId()
{
	eSemanticsStackIdFlag topFlag = m_stackSemanticserParserFlag.top();
	return topFlag;
}

void IdentifierListFlagHandler::endSemanticserParserFlag()
{
	m_stackSemanticserParserFlag.pop();
}
