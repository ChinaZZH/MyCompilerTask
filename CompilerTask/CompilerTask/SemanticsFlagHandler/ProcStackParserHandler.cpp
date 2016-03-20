#include "ProcStackParserHandler.h"

ProcStackParserHandler::ProcStackParserHandler()
{

}

ProcStackParserHandler::~ProcStackParserHandler()
{

}

void ProcStackParserHandler::clearData()
{
	while(false == m_stackProcParser.empty()){
		m_stackProcParser.pop();
	}
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