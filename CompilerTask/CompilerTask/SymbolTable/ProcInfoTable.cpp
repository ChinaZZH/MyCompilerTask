#include "ProcInfoTable.h"

ProcInfoTable::ProcInfoTable()
{

}

ProcInfoTable::~ProcInfoTable()
{

}


int ProcInfoTable::addNewProcInfo(ProcInfo newProcInfo)
{
	m_vecProcInfoTbl.push_back(newProcInfo);
	int nProcIdIndex = m_vecProcInfoTbl.size() - 1;
	return nProcIdIndex;
}


int ProcInfoTable::getRecenetlyProcIndex()
{
	int nProcIdIndex = (m_vecProcInfoTbl.size() - 1);
	return nProcIdIndex;
}

ProcInfo* ProcInfoTable::getProcInfoByIndex(int nProcIndex)
{
	if((nProcIndex < 0) || (nProcIndex >= m_vecProcInfoTbl.size())){
		return NULL;
	}

	ProcInfo* pSearchProcInfo = &(m_vecProcInfoTbl[nProcIndex]);
	return pSearchProcInfo;
}
