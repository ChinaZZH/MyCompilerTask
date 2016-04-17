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

	// �����µ��ֶ�
	FieldInfo newFieldInfo;
	newFieldInfo.initStrName(pLastTokenWord->m_szContentValue);
	newFieldInfo.initProcIndex(nTopProcAddressValue);
	newFieldInfo.m_nProcessState = 0;
	
	// ȡ�����ڷ��������ͣ� �����ֶμ���������
	TypeInfo* pTypeInfoValue = this->getTypeInfoByParsingTypePosition();
	if(NULL == pTypeInfoValue){
		LogFileInst::instance().logError("FieldVarTypeBeforeTypeValueSemanticser::processSemanticsParser pTypeInfoValue null ", __FILE__, __LINE__);
		return bProcessSemanticsResult;
	}

	// У��
	const FieldInfoVec& vecFieldInfo = pTypeInfoValue->m_FieldInfo;
	for(int i = 0; i < vecFieldInfo.size(); ++i){
		const FieldInfo& checkFieldInfo = vecFieldInfo[i];
		const std::string& strFieldName = checkFieldInfo.m_strName;
		if(0 == strFieldName.compare(newFieldInfo.m_strName)){
			std::string strErrorData("�����Ѿ����ڣ��ظ����� �ֶ���:");
			strErrorData.append(newFieldInfo.m_strName);
			EmitErrorFile::EmitError(strErrorData);
			return bProcessSemanticsResult;
		}
	}

	// �����������µ��ֶ�ֵ
	pTypeInfoValue->m_FieldInfo.push_back(newFieldInfo);

	// ��¼�ֶη���������
	FieldOfRecordParserHandler& fieldOfRecordHandler = SemanticsParserMgrInst::instance().getFieldOfRecordParserHandler();
	fieldOfRecordHandler.pushNewDataToFlagFieldStack(newFieldInfo.m_strName);

	bProcessSemanticsResult = true;
	return bProcessSemanticsResult;
}

eSemansticeParserTypeValue FieldVarTypeBeforeTypeValueSemanticser::returnSemanticserEnumValue()
{
	return eSemansticeParserTypeValue::eSPEV_FieldVarTypeBeforeTypeValue;  
}
