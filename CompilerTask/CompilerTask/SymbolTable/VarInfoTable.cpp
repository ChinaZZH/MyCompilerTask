#include "VarInfoTable.h"

VarInfoTable::VarInfoTable()
{

}

VarInfoTable::~VarInfoTable()
{

}

void VarInfoTable::addNewVarToSpecficProcId(VarInfo newVarInfo)
{
	int nVarAddressValue = m_mapVarIntoTable.size();
	newVarInfo.m_nTypeLinkAddr = nVarAddressValue;

	m_mapVarIntoTable[nVarAddressValue] = newVarInfo;
}


int VarInfoTable::searchVarInfoTable(int nStackTopProcId, const std::string& strCompareValue) 
{
	int nVarAddressValue = -1;
	for(VarTableInfoMap::const_iterator itr = m_mapVarIntoTable.begin(); itr != m_mapVarIntoTable.end(); ++itr){
		const VarInfo& tempVarInfo = itr->second;
		bool bCompareResult = tempVarInfo.compare(nStackTopProcId, strCompareValue);
		if(false == bCompareResult){
			continue;
		}

		nVarAddressValue = itr->first;
		return nVarAddressValue;
	}


	return nVarAddressValue;
}
