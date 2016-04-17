#include "TypeDefineSemanticser.h"
#include "../SyntaxParser/SyntaxParser.h"
#include "../Log/LogFile.h"
#include "../GlobalData/WordStreamTable.h"
#include "SemanticsParserMgr.h"
#include "../SymbolTable/SymbolTable.h"

TypeDefineSemanticser::TypeDefineSemanticser()
{

}

TypeDefineSemanticser::~TypeDefineSemanticser()
{

}

// ���Ͷ���---> ��ʶ�� 006 = ����
eSemansticeParserTypeValue TypeDefineSemanticser::returnSemanticserEnumValue()
{
	return eSemansticeParserTypeValue::eSPEV_TypeDefineParser;
}

// ���Ͷ���---> ��ʶ�� 006 = ����
bool TypeDefineSemanticser::processSemanticsParser()
{
	bool bProcessSemanticser = false;

	const CToken* pConstTokenWord = this->getTokenWordByLastWordIndex();
	if(NULL == pConstTokenWord){
		LogFileInst::instance().logError("TypeDefineSemanticser::processSemanticsParser pConstTokenWord null", __FILE__, __LINE__);
		return bProcessSemanticser;
	}

	// ���ڷ����Ĺ���Id
	ProcStackParserHandler& procStackParserHandler = SemanticsParserMgrInst::instance().getProcStackParserHandler();
	int nStackTopProcId = procStackParserHandler.getTopProcStackProcAddress();
	if(nStackTopProcId < 0){
		LogFileInst::instance().logError("TypeDefineSemanticser::processSemanticsParser getProcStackTop error", __FILE__, __LINE__);
		return bProcessSemanticser;
	}

	// ���ڻ��� Ȼ��ص�
	bool bCompareWordValue = this->checkCompareIsSameNameWithWord(nStackTopProcId, pConstTokenWord->m_szContentValue);
	if(true == bCompareWordValue){
		return bProcessSemanticser;
	}

	// �������ͱ���
	int nTypeUserInfoMaxAddress = SymbolTableInst::instance().addNewUserTypeInfoToTable(pConstTokenWord->m_szContentValue, nStackTopProcId);
	if (nTypeUserInfoMaxAddress < 0){
		LogFileInst::instance().logError("VarDefineAfterListSemanticser::processSemanticsParser nTypeUserInfoMaxAddress error", __FILE__, __LINE__);
		return bProcessSemanticser;
	}

	// ���ͽڵ����������
	TypePositionParseHandler& typeInfoPositionHandler = SemanticsParserMgrInst::instance().getTypePositionParseHandler();
	typeInfoPositionHandler.addProcessingTypeInfoAddress(nTypeUserInfoMaxAddress);

	bProcessSemanticser = true;
	return bProcessSemanticser;
}



