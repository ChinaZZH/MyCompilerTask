#include "SemanticsParserIdFlag.h"

SemanticsParserIdFlag::SemanticsParserIdFlag()
{

}

SemanticsParserIdFlag::~SemanticsParserIdFlag()
{

}

void SemanticsParserIdFlag::startNewSemanticserParserFlag(eSemanticsStackIdFlag newFlag)
{
	m_stackSemanticserParserFlag.push(newFlag);
}

eSemanticsStackIdFlag SemanticsParserIdFlag::getCurrentSemanticsParserId()
{
	eSemanticsStackIdFlag topFlag = m_stackSemanticserParserFlag.top();
	return topFlag;
}

void SemanticsParserIdFlag::endSemanticserParserFlag()
{
	m_stackSemanticserParserFlag.pop();
}
