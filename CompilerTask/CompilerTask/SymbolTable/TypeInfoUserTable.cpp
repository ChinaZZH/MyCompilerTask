#include "TypeInfoUserTable.h"

TypeInfoUserTable::TypeInfoUserTable()
{

}

TypeInfoUserTable::~TypeInfoUserTable()
{

}

int TypeInfoUserTable::searchTypeInfoTable(int nStackTopProcId, const std::string& strCompareValue)
{
	int nTypeInfoAddressValue = -1;
	for(TypeInfoMap::const_iterator itr = m_mapTypeUserInfoTable.begin(); itr != m_mapTypeUserInfoTable.end(); ++itr){
		const TypeInfo& searchTypeInfo = itr->second;
		bool bCompareResult = searchTypeInfo.compare(nStackTopProcId, strCompareValue);
		if(false == bCompareResult){
			continue;
		}

		nTypeInfoAddressValue = itr->first;
		return nTypeInfoAddressValue;
	}

	return nTypeInfoAddressValue;
}

int TypeInfoUserTable::addNewUserTypeInfoToTable(TypeInfo newUserTypeInfo)
{
	int nNewAddressValue = m_mapTypeUserInfoTable.size();
	m_mapTypeUserInfoTable[nNewAddressValue] = newUserTypeInfo;
	return nNewAddressValue;
}
