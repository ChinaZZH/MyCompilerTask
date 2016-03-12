#include "EnumInfoTable.h"


EnumInfoTable::EnumInfoTable()
{

}


EnumInfoTable::~EnumInfoTable()
{

}

int EnumInfoTable::searchEnumInfoTable(int nStackTopProcId, const std::string& strCompareValue)
{
	int nEnumInfoAddress = -1;
	for(unsigned int i = 0; i < m_vecEnumInfoTable.size(); ++i){
		const EnumInfo& constEnumInfo = m_vecEnumInfoTable[i];
		bool bCompareResultValue = constEnumInfo.compare(nStackTopProcId, strCompareValue);
		if(false == bCompareResultValue){
			continue;
		}

		nEnumInfoAddress = i;
		return nEnumInfoAddress;
	}

	return nEnumInfoAddress;
}
