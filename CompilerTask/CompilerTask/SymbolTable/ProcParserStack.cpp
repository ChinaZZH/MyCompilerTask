#include "ProcParserStack.h"

ProcParserStack::ProcParserStack()
{

}

ProcParserStack::~ProcParserStack()
{

}

int ProcParserStack::getTopProcStackProcAddress()
{
	int nTopProcAddressValue = m_stackProcParser.top();
	return nTopProcAddressValue;
}

bool ProcParserStack::newProcCallAddToStack(int nProcIdAddress)
{
	m_stackProcParser.push(nProcIdAddress);
	return true;
}
