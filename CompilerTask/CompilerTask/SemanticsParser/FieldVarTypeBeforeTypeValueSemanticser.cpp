#include "FieldVarTypeBeforeTypeValueSemanticser.h"
#include "SemanticsParserMgr.h"
#include "../SymbolTable/TypeInfoUserTable.h"
#include "../Log/LogFile.h"
#include "../Common/Structure.h"
#include "../SymbolTable/SymbolTable.h"
#include "../Common/ErrorProcess.h"

FieldVarTypeBeforeTypeValueSemanticser::FieldVarTypeBeforeTypeValueSemanticser()
{

}

FieldVarTypeBeforeTypeValueSemanticser::~FieldVarTypeBeforeTypeValueSemanticser()
{

}

bool FieldVarTypeBeforeTypeValueSemanticser::processSemanticsParser()
{
	bool bProcessSemanticsResult = false;

	const CToken* pLastTokenWord = this->getTokenWordByLastWordIndex();
	if(NULL == pLastTokenWord){
		LogFileInst::instance().logError("FieldVarTypeBeforeTypeValueSemanticser::processSemanticsParser pLastTokenWord null ", __FILE__, __LINE__);
		return bProcessSemanticsResult;
	}

	ProcStackParserHandler& procStackHandler = SemanticsParserMgrInst::instance().getProcStackParserHandler();
	int nTopProcAddressValue = procStackHandler.getTopProcStackProcAddress();

	// 创建新的字段
	FieldInfo newFieldInfo;
	newFieldInfo.initStrName(pLastTokenWord->m_szContentValue);
	newFieldInfo.initProcIndex(nTopProcAddressValue);
	newFieldInfo.m_nProcessState = 0;
	
	// 取出正在分析的类型， 将该字段加在类型上
	TypeInfo* pTypeInfoValue = this->getTypeInfoByParsingTypePosition();
	if(NULL == pTypeInfoValue){
		LogFileInst::instance().logError("FieldVarTypeBeforeTypeValueSemanticser::processSemanticsParser pTypeInfoValue null ", __FILE__, __LINE__);
		return bProcessSemanticsResult;
	}

	// 校验
	const FieldInfoVec& vecFieldInfo = pTypeInfoValue->m_FieldInfo;
	for(int i = 0; i < vecFieldInfo.size(); ++i){
		const FieldInfo& checkFieldInfo = vecFieldInfo[i];
		const std::string& strFieldName = checkFieldInfo.m_strName;
		if(0 == strFieldName.compare(newFieldInfo.m_strName)){
			std::string strErrorData("域名已经存在，重复定义 字段名:");
			strErrorData.append(newFieldInfo.m_strName);
			EmitErrorFile::EmitError(strErrorData);
			return bProcessSemanticsResult;
		}
	}

	// 该类型增加新的字段值
	pTypeInfoValue->m_FieldInfo.push_back(newFieldInfo);

	// 记录字段分析处理器
	FieldOfRecordParserHandler& fieldOfRecordHandler = SemanticsParserMgrInst::instance().getFieldOfRecordParserHandler();
	fieldOfRecordHandler.pushNewDataToFlagFieldStack(newFieldInfo.m_strName);

	bProcessSemanticsResult = true;
	return bProcessSemanticsResult;
}

eSemansticeParserTypeValue FieldVarTypeBeforeTypeValueSemanticser::returnSemanticserEnumValue()
{
	return eSemansticeParserTypeValue::eSPEV_FieldVarTypeBeforeTypeValue;  
}
