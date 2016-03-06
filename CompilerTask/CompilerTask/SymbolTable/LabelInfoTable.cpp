#include "LabelInfoTable.h"

LabelInfoTable::LabelInfoTable()
{

}

LabelInfoTable::~LabelInfoTable()
{

}

bool LabelInfoTable::addLabelInfo(LabelInfo newLabelInfo)
{
	int nLabelInfoKeyValue = m_mapLabelInfoTable.size();
	m_mapLabelInfoTable[nLabelInfoKeyValue] = newLabelInfo;
	return true;
}


int LabelInfoTable::searchLableInfoTable(const int nProcIdValue, const std::string& strLableName)
{
	for(LabelInfoMap::const_iterator itr = m_mapLabelInfoTable.begin(); itr != m_mapLabelInfoTable.end(); ++itr){
		const LabelInfo& labelInfo = (itr->second);
		bool bEqualOfCompareResult = labelInfo.compare(nProcIdValue, strLableName);
		if(false == bEqualOfCompareResult){
			continue;
		}

		int nLabelAddressValue = itr->first;
		return nLabelAddressValue;
	}

	int nErrorAddressValue = -1;
	return nErrorAddressValue;
}
