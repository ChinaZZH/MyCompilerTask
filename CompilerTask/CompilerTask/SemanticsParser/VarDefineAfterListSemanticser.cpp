#include "VarDefineAfterListSemanticser.h"
#include "SemanticsParserMgr.h"
#include "SemanticsEnumDef.h"
#include "../SymbolTable/TypeInfoUserTable.h"
#include "../SymbolTable/SymbolTable.h"
#include "../Log/LogFile.h"
#include "../Common/IntStringConverter.h"


VarDefineAfterListSemanticser::VarDefineAfterListSemanticser()
{

}

VarDefineAfterListSemanticser::~VarDefineAfterListSemanticser()
{

}

bool VarDefineAfterListSemanticser::processSemanticsParser()
{
	bool bProcessSemanticser = false;
	
	ProcStackParserHandler& procParserHandler = SemanticsParserMgrInst::instance().getProcStackParserHandler();
	int nTopProcAddress = procParserHandler.getTopProcStackProcAddress();
	if(nTopProcAddress < 0){
		LogFileInst::instance().logError("VarDefineAfterListSemanticser::processSemanticsParser nTopProcAddress error", __FILE__, __LINE__);
		return bProcessSemanticser;
	}

	
	int nSerialIdValue = SymbolTableInst::instance().getSerialId();
	std::string strSerialValue = IntStringConverter::intValueConvertToString(nSerialIdValue);
	std::string strInitTypeName("_noname");
	strInitTypeName.append(strSerialValue);

	TypeInfo newUserTypeInfo;
	newUserTypeInfo.initStrName(strInitTypeName);
	newUserTypeInfo.initProcIndex(nTopProcAddress);
	newUserTypeInfo.nullLinkAddressValue();
	
	int nTypeUserInfoMaxAddress = SymbolTableInst::instance().addNewUserTypeInfoToTable(newUserTypeInfo);
	if(nTypeUserInfoMaxAddress < 0){
		LogFileInst::instance().logError("VarDefineAfterListSemanticser::processSemanticsParser nTypeUserInfoMaxAddress error", __FILE__, __LINE__);
		return bProcessSemanticser;
	}

	// 类型节点分析处理器
	TypePositionParseHandler& typeInfoPositionHandler = SemanticsParserMgrInst::instance().getTypePositionParseHandler();
	typeInfoPositionHandler.addProcessingTypeInfoAddress(nTypeUserInfoMaxAddress);

	// 标识符分析处理器
	IdentifierListFlagHandler& identifierFlagParserHandler = SemanticsParserMgrInst::instance().getIdentifierListFlagHandler();
	identifierFlagParserHandler.endSemanticserParserFlag();

	bProcessSemanticser = true;
	return bProcessSemanticser;
}

eSemansticeParserTypeValue VarDefineAfterListSemanticser::returnSemanticserEnumValue()
{
	return eSemansticeParserTypeValue::eSPEV_VarDefineAfterList;
}
