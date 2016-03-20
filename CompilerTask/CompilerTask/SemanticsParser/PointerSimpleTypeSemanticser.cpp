#include "PointerSimpleTypeSemanticser.h"
#include "SemanticsParserMgr.h"
#include "../SemanticsFlagHandler/TypePositionParseHandler.h"
#include "../Log/LogFile.h"
#include "../SymbolTable/SymbolTable.h"
#include "../SymbolTable/TypeInfoUserTable.h"
#include "../Common/IntStringConverter.h"
#include "../SyntaxParser/SyntaxParser.h"
#include "../GlobalData/WordStreamTable.h"
#include "TypeEnumConverter.h"

PointerSimpleTypeSemanticser::PointerSimpleTypeSemanticser()
{

}

PointerSimpleTypeSemanticser::~PointerSimpleTypeSemanticser()
{

}

/*
ָ������	-> ^ ������
������	-> ��ʶ�� 008
-> char 009
-> boolean 009
-> integer 009
-> byte 009
-> shortint 009
-> smallint 009
-> word 009
-> longword 009
-> cardinal 009
-> real 009
-> single 009
*/

bool PointerSimpleTypeSemanticser::processSemanticsParser()
{
	bool bProcessSemanticsResult = false;

	TypePositionParseHandler& typePositionHandler = SemanticsParserMgrInst::instance().getTypePositionParseHandler();
	int nTopTypeAddressValue = typePositionHandler.getProcessingTypeAddress();
	if(nTopTypeAddressValue < 0){
		LogFileInst::instance().logError("PointerSimpleTypeSemanticser::processSemanticsParser nTopTypeAddressValue error", __FILE__, __LINE__);
		return bProcessSemanticsResult;
	}

	TypeInfo* pTypeInfoUnit = SymbolTableInst::instance().getTypeInfoFromTableAddress(nTopTypeAddressValue);
	if(NULL == pTypeInfoUnit){
		LogFileInst::instance().logError("PointerSimpleTypeSemanticser::processSemanticsParser pTypeInfoUnit null", __FILE__, __LINE__);
		return bProcessSemanticsResult;
	}

	ProcStackParserHandler& procParserHandler = SemanticsParserMgrInst::instance().getProcStackParserHandler();
	int nTopProcAddress = procParserHandler.getTopProcStackProcAddress();

	// ��ʼ��������
	int nSerialIdValue = SymbolTableInst::instance().getSerialId();
	std::string strSerialValue = IntStringConverter::intValueConvertToString(nSerialIdValue);
	std::string strInitTypeName("_noname");
	strInitTypeName.append(strSerialValue);

	int nSimpleTypeAddressValue = SymbolTableInst::instance().addNewUserTypeInfoToTable(strSerialValue, nTopProcAddress);
	if(nSimpleTypeAddressValue < 0){
		LogFileInst::instance().logError("PointerSimpleTypeSemanticser::processSemanticsParser nTypeInfoAddress error", __FILE__, __LINE__);
		return bProcessSemanticsResult;
	}

	pTypeInfoUnit->m_eDataType = eDataStoreEnumValue::eDSEV_Pointer;
	pTypeInfoUnit->m_nAddressLink = nSimpleTypeAddressValue;

	// �ӵ��������л�ȡ��Ӧ�ĵ���
	int nParserWordIndex = SyntaxParserInst::instance().getParserWordTableIndex();
	nParserWordIndex = nParserWordIndex - 1;
	const CToken* pConstTokenWord = WordStreamTableInst::instance().getWordTokenByTableIndex(nParserWordIndex);

	TypeInfo* pSimpleTypeInfoUnit = SymbolTableInst::instance().getTypeInfoFromTableAddress(nSimpleTypeAddressValue);
	pSimpleTypeInfoUnit->m_nProcessState = 1;
	pSimpleTypeInfoUnit->m_eDataType = TypeEnumConverter::wordStatusToDataStoreType(pConstTokenWord->m_nWordStatus);
	pSimpleTypeInfoUnit->m_eBaseType = TypeEnumConverter::wordStatusToDataStoreType(pConstTokenWord->m_nWordStatus);


	bProcessSemanticsResult = true;
	return bProcessSemanticsResult;
}

/*
ָ������	-> ^ ������
������	-> ��ʶ�� 008
-> char 009
-> boolean 009
-> integer 009
-> byte 009
-> shortint 009
-> smallint 009
-> word 009
-> longword 009
-> cardinal 009
-> real 009
-> single 009
*/

eSemansticeParserTypeValue PointerSimpleTypeSemanticser::returnSemanticserEnumValue()
{
	return eSPEV_PointerSimpleType;
}
