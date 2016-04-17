#include "PointerSimpleIdentifierTypeSemanticser.h"
#include "SemanticsParserMgr.h"
#include "../Log/LogFile.h"
#include "../SymbolTable/SymbolTable.h"
#include "../SyntaxParser/SyntaxParser.h"
#include "../GlobalData/WordStreamTable.h"
#include "../Common/ErrorProcess.h"

PointerSimpleIdentifierTypeSemanticser::PointerSimpleIdentifierTypeSemanticser()
{

}

PointerSimpleIdentifierTypeSemanticser::~PointerSimpleIdentifierTypeSemanticser()
{

}


/*
ָ������	-> ^ ������
������	-> ��ʶ�� 008
*/

bool PointerSimpleIdentifierTypeSemanticser::processSemanticsParser()
{
	bool bProcessSemanticsResult = false;

	const CToken* pConstTokenWord = this->getTokenWordByLastWordIndex();
	if(NULL == pConstTokenWord){
		LogFileInst::instance().logError("PointerSimpleIdentifierTypeSemanticser::processSemanticsParser pConstTokenWord null", __FILE__, __LINE__);
		return bProcessSemanticsResult;
	}

	// ���ڷ����Ĺ���Id
	ProcStackParserHandler& procStackParserHandler = SemanticsParserMgrInst::instance().getProcStackParserHandler();
	int nStackTopProcId = procStackParserHandler.getTopProcStackProcAddress();
	if(nStackTopProcId < 0){
		LogFileInst::instance().logError("PointerSimpleIdentifierTypeSemanticser::processSemanticsParser getProcStackTop error", __FILE__, __LINE__);
		return bProcessSemanticsResult;
	}

	TypeInfo* pTypeInfoUnit = this->getTypeInfoByParsingTypePosition();
	if(NULL == pTypeInfoUnit){
		LogFileInst::instance().logError("PointerSimpleIdentifierTypeSemanticser::processSemanticsParser  pUserDefineTypeInfo null ", __FILE__, __LINE__);
		return bProcessSemanticsResult;
	}

	pTypeInfoUnit->m_eDataType = eDataStoreEnumValue::eDSEV_Pointer;
	pTypeInfoUnit->m_strContentValue = pConstTokenWord->m_szContentValue;

	int nIdentifierTypeAddress = SymbolTableInst::instance().searchTypeInfoTable(nStackTopProcId, pConstTokenWord->m_szContentValue);
	if(nIdentifierTypeAddress < 0){
		bProcessSemanticsResult = true;
		return bProcessSemanticsResult;
	}
	
	TypeInfo* pIdentifierTypeInfoUnit = SymbolTableInst::instance().getTypeInfoFromTableAddress(nIdentifierTypeAddress);
	if(0 == pIdentifierTypeInfoUnit->m_nProcessState){
		EmitErrorFile::EmitError("ָ��ָ�����������������");
		return bProcessSemanticsResult;
	}
	

	bProcessSemanticsResult = true;
	return bProcessSemanticsResult;
}


/*
ָ������	-> ^ ������
������	-> ��ʶ�� 008
*/

eSemansticeParserTypeValue PointerSimpleIdentifierTypeSemanticser::returnSemanticserEnumValue()
{
	return eSPEV_PointerSimpleIndetifierType;
}
