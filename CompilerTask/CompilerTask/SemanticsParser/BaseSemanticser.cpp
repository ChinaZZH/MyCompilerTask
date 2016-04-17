#include "BaseSemanticser.h"
#include <string>
#include "../SymbolTable/SymbolTable.h"
#include "../SyntaxParser/SyntaxParser.h"
#include "../Log/LogFile.h"
#include "../GlobalData/WordStreamTable.h"


BaseSemanticser::BaseSemanticser()
{

}

BaseSemanticser::~BaseSemanticser()
{

}

bool BaseSemanticser::processSemanticsParser()
{
	return true;
}



eSemansticeParserTypeValue BaseSemanticser::returnSemanticserEnumValue()
{
	return eSPEV_NullParser;
}

bool BaseSemanticser::checkCompareIsSameNameWithWord(int nStackTopProcId, const std::string& strWordValue)
{
	bool bSameName = true;

	// �Ƿ�����ͱ���Ϣ���е�����ͬ��
	int nTypeInfoAddressValue = SymbolTableInst::instance().searchTypeInfoTable(nStackTopProcId, strWordValue);
	if (nTypeInfoAddressValue >= 0){
		return bSameName;
	}

	// �ڵ�ǰ������ �Ƿ��г����������ͬ��(����,����ʧ��)
	int nConstAddressValue = SymbolTableInst::instance().searchConstInfoTable(nStackTopProcId, strWordValue);
	if (nConstAddressValue >= 0){
		return bSameName;
	}

	// �ڵ�ǰ������ �Ƿ��б�� �������ͬ��(����,����ʧ��)
	int nLabelAddressValue = SymbolTableInst::instance().searchLableInfoTable(nStackTopProcId, strWordValue);
	if (nLabelAddressValue >= 0){
		return bSameName;
	}

	// �ڵ�ǰ������ �Ƿ���ö�� �������ͬ��(����,����ʧ��)
	int nEnumAddressValue = SymbolTableInst::instance().searchEnumInfoTable(nStackTopProcId, strWordValue);
	if (nEnumAddressValue >= 0){
		return bSameName;
	}

	// �ڵ�ǰ������ �Ƿ��б��� �������ͬ��(����,����ʧ��)
	int nVarAddressValue = SymbolTableInst::instance().searchVarInfoTable(nStackTopProcId, strWordValue);
	if (nVarAddressValue >= 0){
		return bSameName;
	}

	// �Ƿ������ͬ��(����,����ʧ��)
	bool bIsSameNameProc = SymbolTableInst::instance().compareProcNameIsSame(strWordValue);
	if (true == bIsSameNameProc){
		return bSameName;
	}

	bSameName = false;
	return bSameName;
}

const CToken* BaseSemanticser::getTokenWordByCurrentWordIndex()
{
	const CToken* pWordToken = this->getTokenWordByLastSomeWordIndex(0);
	return pWordToken;
}


const CToken* BaseSemanticser::getTokenWordByLastWordIndex()
{
	const CToken* pWordToken = this->getTokenWordByLastSomeWordIndex(1);
	return pWordToken;
}


const CToken* BaseSemanticser::getTokenWordByLastSomeWordIndex(int nLastWordIndex)
{
	int nParserWordTableIndex = SyntaxParserInst::instance().getParserWordTableIndex();
	if(nParserWordTableIndex <= 0){
		LogFileInst::instance().logError("BaseSemanticser::getTokenWordByLastSomeWordIndex nParserWordTableIndex error", __FILE__, __LINE__);
		return NULL;
	}

	// ��ʶ���б��ʶ��
	int nLastParserWordIndex = nParserWordTableIndex - nLastWordIndex;
	if(nLastParserWordIndex <= 0){
		LogFileInst::instance().logError("BaseSemanticser::getTokenWordByLastSomeWordIndex nLastParserWordIndex error", __FILE__, __LINE__);
		return NULL;
	}

	// �Ӵʷ������еõ��� ���ʼ�  ��ȥ�� ��Ӧ�ĵ���
	const CToken* pParserWord = WordStreamTableInst::instance().getWordTokenByTableIndex(nLastParserWordIndex);
	if(NULL == pParserWord){
		LogFileInst::instance().logError("BaseSemanticser::getTokenWordByLastSomeWordIndex pParserWord null", __FILE__, __LINE__);
		return NULL;
	}

	return pParserWord;
}