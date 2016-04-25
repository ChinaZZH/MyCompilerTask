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
	case eSPIF_EnumIdentifierListStart:
		bProcessSemanticser = this->processEnumTypeIdentifierList();
		break;

	case eSPIF_RecordIdentifierListStart:
		bProcessSemanticser = this->processRecordIdentifierList();
		break;

	case eSPIF_FieldOfRecordListStart:
		bProcessSemanticser = this->processFieldOfRecordList();
		break;

	case eSPIF_ParamOfProcListStart:
	case eSPIF_ParamOfFunctionListStart:
		bProcessSemanticser = this->processParamTypeOfFunction();
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


bool IdentifierDefineListSemanticser::processEnumTypeIdentifierList()
{
	bool bProcessSemanticser = false;
	const CToken* pConstTokenWord = this->getTokenWordByLastWordIndex();
	if(NULL == pConstTokenWord){
		LogFileInst::instance().logError("IdentifierDefineListSemanticser::processEnumTypeIdentifierList pConstTokenWord null", __FILE__, __LINE__);
		return bProcessSemanticser;
	}

	// 正在分析的过程Id
	ProcStackParserHandler& procStackParserHandler = SemanticsParserMgrInst::instance().getProcStackParserHandler();
	int nStackTopProcId = procStackParserHandler.getTopProcStackProcAddress();
	if(nStackTopProcId < 0){
		LogFileInst::instance().logError("IdentifierDefineListSemanticser::processEnumTypeIdentifierList getProcStackTop error", __FILE__, __LINE__);
		return bProcessSemanticser;
	}

	// 是否同名
	bool bCompareNameWithWord = checkCompareIsSameNameWithWord(nStackTopProcId, pConstTokenWord->m_szContentValue);
	if(true == bCompareNameWithWord){
		EmitErrorFile::EmitError("该标识符已经定义");
		return bProcessSemanticser;
	}

	// 判断地址是否合法
	int nNewlyEnumAddress = SymbolTableInst::instance().getEmptyOrNewEnumAddressValue();
	if(nNewlyEnumAddress < 0){
		LogFileInst::instance().logError("IdentifierDefineListSemanticser::processEnumTypeIdentifierList nNewlyEnumAddress error", __FILE__, __LINE__);
		return bProcessSemanticser;
	}

	int nNewlyBeginEnumAddress = SymbolTableInst::instance().getNewEnumBeginAddressValue();
	if((nNewlyEnumAddress - nNewlyBeginEnumAddress) > 256){
		EmitErrorFile::EmitError("枚举类型已经超过标号最大个数的限制：256");
		return bProcessSemanticser;
	}

	// 初始化内容
	EnumInfo* pEmptyEnumValue = SymbolTableInst::instance().getEnumInfoByEnumAddress(nNewlyEnumAddress);
	if(NULL == pEmptyEnumValue){
		LogFileInst::instance().logError("IdentifierDefineListSemanticser::processEnumTypeIdentifierList pEmptyEnumValue null", __FILE__, __LINE__);
		return bProcessSemanticser;
	}


	pEmptyEnumValue->initStrName(pConstTokenWord->m_szContentValue);
	pEmptyEnumValue->initProcIndex(nStackTopProcId);

	bProcessSemanticser = true;
	return bProcessSemanticser;
}


bool IdentifierDefineListSemanticser::processRecordIdentifierList()
{
	bool bProcessSemanticser = false;

	const CToken* pParserWord = this->getTokenWordByLastWordIndex();
	if(NULL == pParserWord){
		LogFileInst::instance().logError("IdentifierDefineListSemanticser::processRecordIdentifierList pParserWord null", __FILE__, __LINE__);
		return bProcessSemanticser;
	}

	TypeInfo* pUserDefineTypeInfo = this->getTypeInfoByParsingTypePosition();
	if(NULL == pUserDefineTypeInfo){
		LogFileInst::instance().logError("IdentifierDefineListSemanticser::processRecordIdentifierList pUserDefineTypeInfo null ", __FILE__, __LINE__);
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

	const CToken* pConstTokenWord = this->getTokenWordByLastWordIndex();
	if (NULL == pConstTokenWord){
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

	const CToken* pConstTokenWord = this->getTokenWordByLastWordIndex();
	if (NULL == pConstTokenWord){
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


bool IdentifierDefineListSemanticser::processFieldOfRecordList()
{
	bool bProcessSemanticser = false;

	const CToken* pParserWord = this->getTokenWordByLastWordIndex();
	if(NULL == pParserWord){
		LogFileInst::instance().logError("IdentifierDefineListSemanticser::processRecordIdentifierList pParserWord null", __FILE__, __LINE__);
		return bProcessSemanticser;
	}

	TypeInfo* pUserDefineTypeInfo = this->getTypeInfoByParsingTypePosition();
	if(NULL == pUserDefineTypeInfo){
		LogFileInst::instance().logError("IdentifierDefineListSemanticser::processRecordIdentifierList  pUserDefineTypeInfo null ", __FILE__, __LINE__);
		return bProcessSemanticser;
	}

	FieldOfRecordParserHandler& fieldOfRecordHandler = SemanticsParserMgrInst::instance().getFieldOfRecordParserHandler();

	FieldInfo newFieldInfo;
	newFieldInfo.initStrName(pParserWord->m_szContentValue);
	ProcStackParserHandler& procStackHandler = SemanticsParserMgrInst::instance().getProcStackParserHandler();
	newFieldInfo.initProcIndex(procStackHandler.getTopProcStackProcAddress());
	newFieldInfo.m_nProcessState = 0;
	newFieldInfo.m_strVarFieldConst = fieldOfRecordHandler.getConstFieldStackTop();
	newFieldInfo.m_strVarFieldFlag = fieldOfRecordHandler.getFlagFieldStackTop();

	// 验证域名是否存在
	FieldInfoVec& vecFieldInfo = pUserDefineTypeInfo->m_FieldInfo;
	for (unsigned int i = 0; i < vecFieldInfo.size(); ++i){
		const std::string& strFieldStringName = vecFieldInfo[i].m_strName;
		int nCompareResult = strFieldStringName.compare(newFieldInfo.m_strName);
		if (0 == nCompareResult){
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


bool IdentifierDefineListSemanticser::processParamTypeOfFunction()
{
	bool bProcessSemanticser = false;

	const CToken* pParserWord = this->getTokenWordByLastWordIndex();
	if(NULL == pParserWord){
		LogFileInst::instance().logError("IdentifierDefineListSemanticser::processParamTypeOfFunction pParserWord null", __FILE__, __LINE__);
		return bProcessSemanticser;
	}

	
	ProcInfo* pNewProcInfo = SymbolTableInst::instance().getRecenetlyProcIndex();
	if(NULL == pNewProcInfo){
		LogFileInst::instance().logError("IdentifierDefineListSemanticser::processParamTypeOfFunction pNewProcInfo null", __FILE__, __LINE__);
		return bProcessSemanticser;
	}

	// 校验
	const ParaInfoVec& vecParamInfo = pNewProcInfo->m_ParaTable;
	for(int i = 0; i < vecParamInfo.size(); ++i){
		const ParaInfo& checkParamInfo = vecParamInfo[i];
		if(0 != checkParamInfo.m_strParamName.compare(pParserWord->m_szContentValue)){
			EmitErrorFile::EmitError("标识符名已经存在");
			return bProcessSemanticser;
		}
	}

	// 将新的参数放入参数列表
	ParaInfo::AssignType assignType = ParaInfo::VAR;
	IdentifierListFlagHandler& identifierListHandler = SemanticsParserMgrInst::instance().getIdentifierListFlagHandler();
	eSemanticsStackIdFlag flagValueOfIdentifier = identifierListHandler.getCurrentSemanticsParserId();
	if(eSPIF_ParamOfProcListStart == flagValueOfIdentifier){
		assignType = ParaInfo::VAL;
	}

	
	ParaInfo newParamInfo;
	newParamInfo.m_strParamName = (pParserWord->m_szContentValue);
	newParamInfo.m_eAssignType = assignType;
	newParamInfo.m_nParamType = -1;

	pNewProcInfo->m_ParaTable.push_back(newParamInfo);

	bProcessSemanticser = true;
	return bProcessSemanticser;
}