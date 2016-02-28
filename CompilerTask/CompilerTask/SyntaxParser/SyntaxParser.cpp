#include "SyntaxParser.h"
#include "../GlobalData/LexParseGlobalDataDef.h"
#include "../GlobalData/WordStreamTable.h"
#include "../Log/LogFile.h"

SyntaxParser::SyntaxParser()
{

}

SyntaxParser::~SyntaxParser()
{

}

bool SyntaxParser::processSyntaxParse()
{
	bool bProcessResult = false;
	
	// �﷨
	m_stackSyntaxParser.push(eSLV_StartSyntaxParser);
	int nWordTableIndex = 0;     
	while(1){
		// ��������Ϊ��
		if(true == m_stackSyntaxParser.empty()){
			break;
		}

		// ��������ȡ����
		const CToken* pWordToken = WordStreamTableInst::instance().getWordTokenByTableIndex(nWordTableIndex);
		if(NULL == pWordToken){
			LogFileInst::instance().logError("SyntaxParser::processSyntaxParse pWordToken null", __FILE__, __LINE__);
			return bProcessResult;
		}

		int nStackElement = this->enParserStack();

		// ȡ����Ԫ�����쳣�� �����
		if(nStackElement < 0){
			LogFileInst::instance().logError("SyntaxParser::processSyntaxParse nStackElement error", __FILE__, __LINE__);
			return bProcessResult;
		}

		// �պ�
		if(0 == nStackElement){
			continue;
		}

		// �ս��
		if(nStackElement < eSLV_StartSyntaxParser){
			if(pWordToken->m_nWordStatus == nStackElement){
				nWordTableIndex = nWordTableIndex + 1;
			}
			else{
				LogFileInst::instance().logError("SyntaxParser::processSyntaxParse �ս������ error", __FILE__, __LINE__);
				return bProcessResult;
			}
		}

		// ���ս��
		if(){
		}
		
	}

	bProcessResult = false;
	return bProcessResult;
}

int SyntaxParser::enParserStack()
{
	int nElementValue = m_stackSyntaxParser.top();
	m_stackSyntaxParser.pop();
	return nElementValue;
}
