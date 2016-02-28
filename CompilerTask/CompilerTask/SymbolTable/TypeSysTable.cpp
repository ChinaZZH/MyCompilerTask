#include "TypeSysTable.h"

TypeSysTable::TypeSysTable()
{

}

TypeSysTable::~TypeSysTable()
{

}

void TypeSysTable::addNewTypeSysUnit(TypeSysInfo newTypeSysInfo)
{
	m_vecTypeSysTable.push_back(newTypeSysInfo);
}
