#include "EnumInfoTable.h"


EnumInfoTable::EnumInfoTable()
:m_nNewEnumBeginAddress(-1)
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


int EnumInfoTable::createNewEnumUnitSpace()
{
	EnumInfo emptyNewEnumValue;
	m_vecEnumInfoTable.push_back(emptyNewEnumValue);

	int nEnumAddress = this->getNewEnumAddressValue();
	m_nNewEnumBeginAddress = nEnumAddress;
	return nEnumAddress;
}

int EnumInfoTable::getNewEnumAddressValue()
{
	int nEnumValueAddress = -1;
	if(true == m_vecEnumInfoTable.empty()){
		return nEnumValueAddress;
	}

	nEnumValueAddress = m_vecEnumInfoTable.size() - 1;
	return nEnumValueAddress;
}


int EnumInfoTable::getEmptyOrNewEnumAddressValue()
{
	int nEnumAddressValue = -1;
	if(-1 == m_nNewEnumBeginAddress){
		return nEnumAddressValue;
	}

	// 判断是否是已经申请好的
	EnumInfo* pEmptyNewEnum = this->getEnumInfoByEnumAddress(m_nNewEnumBeginAddress);
	if(NULL == pEmptyNewEnum){
		return nEnumAddressValue;
	}

	bool bEmptyEnumStatus = pEmptyNewEnum->isEmptyObject();
	if(true == bEmptyEnumStatus){
		nEnumAddressValue = m_nNewEnumBeginAddress;
		return nEnumAddressValue;
	}

	// 判断是否需要新创建
	EnumInfo emptyNewEnumValue;
	m_vecEnumInfoTable.push_back(emptyNewEnumValue);
	nEnumAddressValue = this->getNewEnumAddressValue();
	return nEnumAddressValue;
}


int EnumInfoTable::getNewEnumBeginAddressValue()
{
	return m_nNewEnumBeginAddress;
}

EnumInfo* EnumInfoTable::getEnumInfoByEnumAddress(int nEnumAddress)
{
	int nEnumTableSize = static_cast<int>(m_vecEnumInfoTable.size());
	if((nEnumAddress<0) || (nEnumAddress>=nEnumTableSize)){
		return NULL;
	}

	EnumInfo* pEnumValue = &(m_vecEnumInfoTable[nEnumAddress]);
	return pEnumValue;
}

void EnumInfoTable::reSetNewEnumBeginAddressToNull()
{
	m_nNewEnumBeginAddress = -1;
}
