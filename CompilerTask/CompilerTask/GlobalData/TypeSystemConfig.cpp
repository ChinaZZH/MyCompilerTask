#include "TypeSystemConfig.h"
#include "../ConfigFile/State.h"
#include "../Log/LogFile.h"
#include "../Common/CommonLib.h"
#include "../SymbolTable/SymbolTable.h"

TypeSystemConfig::TypeSystemConfig()
{

}

TypeSystemConfig::~TypeSystemConfig()
{

}

void TypeSystemConfig::initTypeSysTbl()
{
	std::string strTypeSysFile = ConfigFileDataInst::instance().getTypeSyssFile();
	if(true == strTypeSysFile.empty()){
		LogFileInst::instance().logError("TypeSystemConfig::initTypeSysTbl strTypeSysFile null", __FILE__, __LINE__);
		return;
	}

	std::string strTypeSysContent = CommonLib::FileRead(strTypeSysFile);
	if(true == strTypeSysContent.empty()){
		LogFileInst::instance().logError("TypeSystemConfig::initTypeSysTbl strTypeSysContent null", __FILE__, __LINE__);
		return;
	}

	for(int i = 0; i < (int)strTypeSysContent.size(); i = i + TYPE_TABLE_FIELD_NUM){
		std::string strTempTypeSys = strTypeSysContent.substr(i, 35);
		if(true == strTempTypeSys.empty()){
			LogFileInst::instance().logError("TypeSystemConfig::initTypeSysTbl strTempTypeSys null", __FILE__, __LINE__);
			return;
		}

		SymbolTableInst::instance().initTypeInfoByString(strTempTypeSys);
	}
}
