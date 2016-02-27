
#include "Initializationer.h"
#include "../LexParser/LexParser.h"
#include "../ConfigFile/State.h"
#include "../GlobalData/KeyWordTable.h"
#include "../GlobalData/LexStateTable.h"

Initializationer::Initializationer()
{

}

Initializationer::~Initializationer()
{

}

void Initializationer::initBeforeLexParse()
{
	KeyWordTableInst::instance().initData();
	LexStateTableInst::instance().initData();
}
