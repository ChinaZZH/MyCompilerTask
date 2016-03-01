#include "ConstInfoTable.h"


ConstInfoTable::ConstInfoTable()
{

}

ConstInfoTable::~ConstInfoTable()
{

}

int ConstInfoTable::recConstTbl(const std::string& szValue, int iType)
{
	ConstInfo newConstInfo;
	newConstInfo.m_strName = szValue;
	newConstInfo.m_strConstStringValue = szValue;
	newConstInfo.m_eDataStoreValue = eDSEV_Null;
	newConstInfo.m_eConstBaseValue = static_cast<eConstantEnumValue>(iType);

	int nConstAddressValue = m_mapConstInfoTable.size();
	m_mapConstInfoTable[nConstAddressValue] = newConstInfo;

	// 将其放入类型表中
	//CType::ProcessConstType(nConstAddressValue);
	return nConstAddressValue;
}


// int SymbolTable::RecConstTbl(const std::string& szValue, int iType)
// {
// 	ConstInfo Tmp;
// 	Tmp.m_szName = szValue;
// 	Tmp.m_szVal = szValue;
// 	Tmp.m_StoreType = StoreType::T_NONE;
// 	switch (iType)
// 	{
// 	case 2:
// 	{
// 			  Tmp.m_ConstType = ConstType::STRING;
// 			  Tmp.m_szVal = Tmp.m_szVal.substr(1, Tmp.m_szVal.length() - 2);
// 			  Tmp.m_szVal = StrReplace(Tmp.m_szVal, "''", "'");
// 
// 	}; break;
// 	case 3:		Tmp.m_ConstType = ConstType::INTEGER;		break;
// 	case 4:		Tmp.m_ConstType = ConstType::REAL;		break;
// 	case 5:
// 	case 6:		Tmp.m_ConstType = ConstType::EREAL;		break;
// 	case 7:		Tmp.m_ConstType = ConstType::BOOLEAN;		break;
// 	}
// 	SymbolTbl.AddConst(Tmp);
// 	CType::ProcessConstType(SymbolTbl.ConstInfoTbl.size() - 1);
// 	return SymbolTbl.ConstInfoTbl.size() - 1;
// }