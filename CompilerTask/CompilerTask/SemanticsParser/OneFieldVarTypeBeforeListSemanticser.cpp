#include "OneFieldVarTypeBeforeListSemanticser.h"
#include "SemanticsParserMgr.h"

#include "../SyntaxParser/SyntaxParser.h"
#include "../Log/LogFile.h"
#include "../GlobalData/WordStreamTable.h"
#include "../GlobalData/LexParseGlobalDataDef.h"
#include "../SymbolTable/SymbolTable.h"

OneFieldVarTypeBeforeListSemanticser::OneFieldVarTypeBeforeListSemanticser()
{

}

OneFieldVarTypeBeforeListSemanticser::~OneFieldVarTypeBeforeListSemanticser()
{

}

bool OneFieldVarTypeBeforeListSemanticser::processSemanticsParser()
{
	bool bProcessResult = false;

	// 获取上一个字符
	const CToken* pParserWord = this->getTokenWordByLastWordIndex();
	if(NULL == pParserWord){
		LogFileInst::instance().logError("OneFieldVarTypeBeforeListSemanticser::processSemanticsParser pParserWord null", __FILE__, __LINE__);
		return bProcessResult;
	}

	// 不是常量
	if(eLSV_ConstantInteger != pParserWord->m_nWordStatus){
		LogFileInst::instance().logError("OneFieldVarTypeBeforeListSemanticser::processSemanticsParser WordStatus not Const Data", __FILE__, __LINE__);
		return bProcessResult;
	}
	
	// 取出常量
	const std::string& strConstDataAddress = pParserWord->m_szContentValue;
	int nConstDataAddress = atoi(strConstDataAddress.c_str());
	ConstInfo* pConstData = SymbolTableInst::instance().getConstDataByAddressValue(nConstDataAddress);
	if(NULL == pConstData){
		LogFileInst::instance().logError("OneFieldVarTypeBeforeListSemanticser::processSemanticsParser pConstData null", __FILE__, __LINE__);
		return bProcessResult;
	}

	// 放进去
	FieldOfRecordParserHandler& fieldOfRecordHandler = SemanticsParserMgrInst::instance().getFieldOfRecordParserHandler();
	fieldOfRecordHandler.pushNewDataToConstFieldStack(pConstData->m_strName);

	bProcessResult = true;
	return bProcessResult;
}

eSemansticeParserTypeValue OneFieldVarTypeBeforeListSemanticser::returnSemanticserEnumValue()
{
	return eSemansticeParserTypeValue::eSPEV_OneFieldVarTypeBeforeList;
}
