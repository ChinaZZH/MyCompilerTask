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
	
	// 语法
	m_stackSyntaxParser.push(eSLV_StartSyntaxParser);
	int nWordTableIndex = 0;     
	while(1){
		// 分析队列为空
		if(true == m_stackSyntaxParser.empty()){
			break;
		}

		// 单词流读取不到
		const CToken* pWordToken = WordStreamTableInst::instance().getWordTokenByTableIndex(nWordTableIndex);
		if(NULL == pWordToken){
			LogFileInst::instance().logError("SyntaxParser::processSyntaxParse pWordToken null", __FILE__, __LINE__);
			return bProcessResult;
		}

		int nStackElement = this->enParserStack();

		// 取出的元素是异常的 错误的
		if(nStackElement < 0){
			LogFileInst::instance().logError("SyntaxParser::processSyntaxParse nStackElement error", __FILE__, __LINE__);
			return bProcessResult;
		}

		// 空号
		if(0 == nStackElement){
			continue;
		}

		// 终结符
		if(nStackElement < eSLV_StartSyntaxParser){
			if(pWordToken->m_nWordStatus == nStackElement){
				nWordTableIndex = nWordTableIndex + 1;
			}
			else{
				LogFileInst::instance().logError("SyntaxParser::processSyntaxParse 终结符出错 error", __FILE__, __LINE__);
				return bProcessResult;
			}
		}

		// 非终结符
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
