#include "ProcStackParserHandler.h"

ProcStackParserHandler::ProcStackParserHandler()
{

}

ProcStackParserHandler::~ProcStackParserHandler()
{

}

int ProcStackParserHandler::getTopProcStackProcAddress()
{
	int nTopProcAddressValue = m_stackProcParser.top();
	return nTopProcAddressValue;
}

bool ProcStackParserHandler::newProcCallAddToStack(int nProcIdAddress)
{
	m_stackProcParser.push(nProcIdAddress);
	return true;
}