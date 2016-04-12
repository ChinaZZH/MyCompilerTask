#include "IdentifierDefineListSemanticser.h"
#include "SemanticsParserMgr.h"
#include "../SymbolTable/SymbolTable.h"
#include "../Log/LogFile.h"
#include "../SyntaxParser/SyntaxParser.h"
#include "../GlobalData/WordStreamTable.h"
#include "../Common/ErrorProcess.h"

IdentifierDefineListSemanticser::IdentifierDefineListSemanticser()
{

}

IdentifierDefineListSemanticser::~IdentifierDefineListSemanticser()
{

}

bool IdentifierDefineListSemanticser::processSemanticsParser()
{
	bool bProcessSemanticser = false;
	IdentifierListFlagHandler&  flagIdStack = SemanticsParserMgrInst::instance().getIdentifierListFlagHandler();
	eSemanticsStackIdFlag flagId = flagIdStack.getCurrentSemanticsParserId();
	switch(flagId){
	case eSPIF_RecordIdentifierListStart:
		bProcessSemanticser = this->processRecordIdentifierList();
		break;

	case eSPIF_VarIdentifierListStart:
		bProcessSemanticser = this->processVarIdentifierList();
		break;

	case eSPIF_FileIdentifierListStart:
		bProcessSemanticser = this->processFileIdentifierList();
		break;

	default:
		bProcessSemanticser = true;
		break;
	}
	

	return bProcessSemanticser;
}

// 标识符列表->标识符 012 标识符列表1    标识符列表1->, 标识符 012 标识符列表1
eSemansticeParserTypeValue IdentifierDefineListSemanticser::returnSemanticserEnumValue()
{
	return eSemansticeParserTypeValue::eSPEV_IdentifierTypeDefineList;
}

bool IdentifierDefineListSemanticser::processRecordIdentifierList()
{
	bool bProcessSemanticser = false;

	int nParserWordTableIndex = SyntaxParserInst::instance().getParserWordTableIndex();
	if(nParserWordTableIndex <= 0){
		LogFileInst::instance().logError("IdentifierDefineListSemanticser::processRecordIdentifierList nParserWordTableIndex error", __FILE__, __LINE__);
		return bProcessSemanticser;
	}

	// 标识符列表标识符
	int nLastParserWordIndex = nParserWordTableIndex - 1;
	if(nLastParserWordIndex <= 0){
		LogFileInst::instance().logError("IdentifierDefineListSemanticser::processRecordIdentifierList nLastParserWordIndex error", __FILE__, __LINE__);
		return bProcessSemanticser;
	}

	// 从词法分析中得到的 单词集  中去朝 对应的单词
	const CToken* pParserWord = WordStreamTableInst::instance().getWordTokenByTableIndex(nLastParserWordIndex);
	if(NULL == pParserWord){
		LogFileInst::instance().logError("IdentifierDefineListSemanticser::processRecordIdentifierList pParserWord null", __FILE__, __LINE__);
		return bProcessSemanticser;
	}

	TypePositionParseHandler& typePositionHandler = SemanticsParserMgrInst::instance().getTypePositionParseHandler();
	TypeInfo* pUserDefineTypeInfo = SymbolTableInst::instance().getTypeInfoFromTableAddress(typePositionHandler.getProcessingTypeAddress());
	if(NULL == pUserDefineTypeInfo){
		LogFileInst::instance().logError("IdentifierDefineListSemanticser::processRecordIdentifierList pUserDefineTypeInfo null", __FILE__, __LINE__);
		return bProcessSemanticser;
	}

	
	FieldInfo newFieldInfo;
	newFieldInfo.initStrName(pParserWord->m_szContentValue);
	ProcStackParserHandler& procStackHandler = SemanticsParserMgrInst::instance().getProcStackParserHandler();
	newFieldInfo.initProcIndex(procStackHandler.getTopProcStackProcAddress());
	newFieldInfo.m_nProcessState = 0;

	// 验证域名是否存在
	FieldInfoVec& vecFieldInfo = pUserDefineTypeInfo->m_FieldInfo;
	for(unsigned int i = 0; i < vecFieldInfo.size(); ++i){
		const std::string& strFieldStringName = vecFieldInfo[i].m_strName;
		int nCompareResult = strFieldStringName.compare(newFieldInfo.m_strName);
		if(0 == nCompareResult){
			std::string strErrorData("域名已经存在，重复定义 字段名:");
			strErrorData.append(newFieldInfo.m_strName);
			EmitErrorFile::EmitError(strErrorData);
			return bProcessSemanticser;
		}
	}

	vecFieldInfo.push_back(newFieldInfo);

	bProcessSemanticser = true;
	return bProcessSemanticser;
}

//变量列表的标识符
bool IdentifierDefineListSemanticser::processVarIdentifierList()
{
	bool bProcessSemanticser = false;

	// 获得单词的下标值
	int nParserWordIndex = SyntaxParserInst::instance().getParserWordTableIndex();
	nParserWordIndex = nParserWordIndex - 1;
	if(nParserWordIndex < 0){
		LogFileInst::instance().logError("IdentifierDefineListSemanticser::processVarIdentifierList nParserWordIndex error", __FILE__, __LINE__);
		return bProcessSemanticser;
	}

	// 从单词流表中获取对应的单词
	const CToken* pConstTokenWord = WordStreamTableInst::instance().getWordTokenByTableIndex(nParserWordIndex);
	if(NULL == pConstTokenWord){
		LogFileInst::instance().logError("IdentifierDefineListSemanticser::processVarIdentifierList pConstTokenWord null", __FILE__, __LINE__);
		return bProcessSemanticser;
	}

	// 正在分析的过程Id
	ProcStackParserHandler& procStackParserHandler = SemanticsParserMgrInst::instance().getProcStackParserHandler();
	int nStackTopProcId = procStackParserHandler.getTopProcStackProcAddress();
	if(nStackTopProcId < 0){
		LogFileInst::instance().logError("IdentifierDefineListSemanticser::processVarIdentifierList getProcStackTop error", __FILE__, __LINE__);
		return bProcessSemanticser;
	}

	// 是否同名
	bool bCompareNameWithWord = checkCompareIsSameNameWithWord(nStackTopProcId, pConstTokenWord->m_szContentValue);
	if(true == bCompareNameWithWord){
		return bProcessSemanticser;
	}

	// 检查完成 没有跟该变量名同名的 则将该变量放入变量表(存在,则定义失败)
	VarInfo newVarInfo;
	newVarInfo.initStrName(pConstTokenWord->m_szContentValue);
	newVarInfo.initProcIndex(nStackTopProcId);
	newVarInfo.m_eRank = VarInfo::eR_Var;
	SymbolTableInst::instance().addNewVarToSpecficProcId(newVarInfo);

	bProcessSemanticser = true;
	return bProcessSemanticser;
}


//处理USES模块包含声明
bool IdentifierDefineListSemanticser::processFileIdentifierList()
{
	bool bProcessSemanticser = false;

	// 获得单词的下标值
	int nParserWordIndex = SyntaxParserInst::instance().getParserWordTableIndex();
	nParserWordIndex = nParserWordIndex - 1;
	if(nParserWordIndex < 0){
		LogFileInst::instance().logError("IdentifierDefineListSemanticser::processFileIdentifierList nParserWordIndex error", __FILE__, __LINE__);
		return bProcessSemanticser;
	}

	// 从单词流表中获取对应的单词
	const CToken* pConstTokenWord = WordStreamTableInst::instance().getWordTokenByTableIndex(nParserWordIndex);
	if(NULL == pConstTokenWord){
		LogFileInst::instance().logError("IdentifierDefineListSemanticser::processFileIdentifierList pConstTokenWord null", __FILE__, __LINE__);
		return bProcessSemanticser;
	}

	// 查询符号表是否已经包含该使用文件
	int nUseFileAddressValue = SymbolTableInst::instance().searchUseFileTable(pConstTokenWord->m_szContentValue);
	if(nUseFileAddressValue > 0){
		LogFileInst::instance().logError("IdentifierDefineListSemanticser::processFileIdentifierList 模块已经包含了 null", __FILE__, __LINE__);
		return bProcessSemanticser;
	}

	// 没有的话 符号表进行包含
	SymbolTableInst::instance().addNewUseFlieData(pConstTokenWord->m_szContentValue);

	bProcessSemanticser = true;
	return bProcessSemanticser;
}
