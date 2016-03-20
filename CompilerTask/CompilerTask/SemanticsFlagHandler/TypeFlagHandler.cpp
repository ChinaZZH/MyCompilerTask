#include "TypeFlagHandler.h"

TypeFlagHandler::TypeFlagHandler()
{

}

TypeFlagHandler::~TypeFlagHandler()
{

}

void TypeFlagHandler::clearData()
{
	while(false == m_stackTypeFlag.empty()){
		m_stackTypeFlag.pop();
	}
}


void TypeFlagHandler::pushTypeFlagValueToStack(eTypeFlagEnumValue typeFlagEnum)
{
	m_stackTypeFlag.push(typeFlagEnum);
}

eTypeFlagEnumValue TypeFlagHandler::getTopTypeFlagValue()
{
	int nTypeFlagEnumValue = m_stackTypeFlag.top();

	eTypeFlagEnumValue typeFlagEnum = static_cast<eTypeFlagEnumValue>(nTypeFlagEnumValue);
	return typeFlagEnum;
}

eTypeFlagEnumValue TypeFlagHandler::popTypeFlagValueFromStack()
{
	eTypeFlagEnumValue typeFlagEnum = getTopTypeFlagValue();
	m_stackTypeFlag.pop();
	return typeFlagEnum;
}
