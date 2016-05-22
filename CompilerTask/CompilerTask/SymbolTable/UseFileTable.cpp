#include "UseFileTable.h"

UseFileTable::UseFileTable()
{

}

UseFileTable::~UseFileTable()
{

}

int UseFileTable::searchUseFileTable(const std::string& strUseFileName)
{
	int nFileTableAddress = -1;
	int nUseFileSize = static_cast<int>(m_vecUseFileData.size());
	for(int i = 0; i < nUseFileSize; ++i){
		const UseFileData& fileData = m_vecUseFileData[i];
		if(0 == fileData.m_strFileName.compare(strUseFileName)){
			nFileTableAddress = i;
			return nFileTableAddress;
		}
	}

	return nFileTableAddress;
}

int UseFileTable::addNewUseFlieData(const std::string& strUseFileName)
{
	int nFileAddress = m_vecUseFileData.size();

	bool bFileExistStatus = false;
	UseFileData newUseFile(strUseFileName, bFileExistStatus);
	m_vecUseFileData.push_back(newUseFile);

	return nFileAddress;
}
