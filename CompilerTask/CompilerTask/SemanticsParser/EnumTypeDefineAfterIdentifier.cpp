#include "EnumTypeDefineAfterIdentifier.h"
#include "SemanticsParserMgr.h"
#include "../SymbolTable/SymbolTable.h"
#include "../Log/LogFile.h"

EnumTypeDefineAfterIdentifier::EnumTypeDefineAfterIdentifier()
{

}

EnumTypeDefineAfterIdentifier::~EnumTypeDefineAfterIdentifier()
{

}

bool EnumTypeDefineAfterIdentifier::processSemanticsParser()
{
	bool bProcessSemanticsResult = false;
	
	int nEmptyEnumAddress = SymbolTableInst::instance().getEmptyOrNewEnumAddressValue();
	if(nEmptyEnumAddress < 0){
		LogFileInst::instance().logError("EnumTypeDefineAfterIdentifier::processSemanticsParser nEmptyEnumAddress error", __FILE__, __LINE__);
		return bProcessSemanticsResult;
	}

	EnumInfo* pEmptyEumValue = SymbolTableInst::instance().getEnumInfoByEnumAddress(nEmptyEnumAddress);
	if(NULL == pEmptyEumValue){
		LogFileInst::instance().logError("EnumTypeDefineAfterIdentifier::processSemanticsParser pEmptyEumValue null", __FILE__, __LINE__);
		return bProcessSemanticsResult;
	}


	int nTopTypeAddress = SymbolTableInst::instance().getTopTypeUserInfoAddress();

	ProcStackParserHandler& procStackHandler = SemanticsParserMgrInst::instance().getProcStackParserHandler();
	int nTopProcAddress = procStackHandler.getTopProcStackProcAddress();


	int nEnumConstValue = 0;
	int nNewlyBeginEnumAddrss = SymbolTableInst::instance().getNewEnumBeginAddressValue();
	int nEndEnumAddress = SymbolTableInst::instance().getNewEnumAddressValue();
	for(int i = nNewlyBeginEnumAddrss; i <= nEndEnumAddress; ++i){
		int nNewConstAddress = SymbolTableInst::instance().recConstTbl(pEmptyEumValue->m_strName, eConstantEnumValue::eCEV_ConstantEnumValue);
		if(nNewConstAddress < 0){
			continue;
		}

		ConstInfo* pNewConstInfo = SymbolTableInst::instance().getConstDataByAddressValue(nNewConstAddress);
		if (NULL == pNewConstInfo){
			continue;
		}

		
		pNewConstInfo->initStrName(pEmptyEumValue->m_strName);
		pNewConstInfo->initProcIndex(nTopProcAddress);
		pNewConstInfo->m_nConstIntValue = nEnumConstValue;
		pNewConstInfo->m_nEnumTypeLinkAddr = nTopTypeAddress;
		pNewConstInfo->m_eConstBaseValue = eConstantEnumValue::eCEV_ConstantEnumValue;
		pNewConstInfo->m_eDataStoreValue = eDataStoreEnumValue::eDSEV_Enum;
		

		// 常量值递增
		nEnumConstValue += 1;
	}

	// 设置结束状态
	pEmptyEumValue->initStrName("-1");
	SymbolTableInst::instance().reSetNewEnumBeginAddressToNull();

	IdentifierListFlagHandler& identifierListHandler = SemanticsParserMgrInst::instance().getIdentifierListFlagHandler();
	identifierListHandler.endSemanticserParserFlag();

	bProcessSemanticsResult = true;
	return bProcessSemanticsResult;
}

eSemansticeParserTypeValue EnumTypeDefineAfterIdentifier::returnSemanticserEnumValue()
{
	return eSemansticeParserTypeValue::eSPEV_EnumTypeDefineAfterIdentifier;
}
