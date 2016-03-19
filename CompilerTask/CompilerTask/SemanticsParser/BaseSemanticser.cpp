#include "BaseSemanticser.h"
#include <string>
#include "../SymbolTable/SymbolTable.h"


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
