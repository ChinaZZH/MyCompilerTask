#include "TypePositionParseHandler.h"

TypePositionParseHandler::TypePositionParseHandler()
{

}

TypePositionParseHandler::~TypePositionParseHandler()
{

}

void TypePositionParseHandler::clearData()
{
	while(false == m_stackTypePaser.empty()){
		m_stackTypePaser.pop();
	}
}

void TypePositionParseHandler::addProcessingTypeInfoAddress(int nTypeInfoAddress)
{
	m_stackTypePaser.push(nTypeInfoAddress);
}


int TypePositionParseHandler::getProcessingTypeAddress()
{
	int nTypePositionAddress = -1;
	if(true == m_stackTypePaser.empty()){
		return nTypePositionAddress;
	}

	nTypePositionAddress = m_stackTypePaser.top();
	return nTypePositionAddress;
}

bool TypePositionParseHandler::isEmptyStatus()
{
	return m_stackTypePaser.empty();
}


void TypePositionParseHandler::popTypeAddressData()
{
	m_stackTypePaser.pop();
}
