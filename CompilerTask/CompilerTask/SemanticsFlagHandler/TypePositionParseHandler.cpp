#include "TypePositionParseHandler.h"

TypePositionParseHandler::TypePositionParseHandler()
{

}

TypePositionParseHandler::~TypePositionParseHandler()
{

}

void TypePositionParseHandler::addProcessingTypeInfoAddress(int nTypeInfoAddress)
{
	m_stackTypePaser.push(nTypeInfoAddress);
}
