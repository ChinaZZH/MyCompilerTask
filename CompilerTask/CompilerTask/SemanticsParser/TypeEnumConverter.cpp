#include "TypeEnumConverter.h"

TypeEnumConverter::TypeEnumConverter()
{

}

TypeEnumConverter::~TypeEnumConverter()
{

}

eDataStoreEnumValue TypeEnumConverter::wordStatusToDataStoreType(int nWordStatus)
{
	eDataStoreEnumValue dataStoreValue = eDSEV_Null;
	switch(nWordStatus)
	{
	case 49:
		dataStoreValue = eDataStoreEnumValue::eDSEV_Char;
		break;

	case 44:
		dataStoreValue = eDataStoreEnumValue::eDSEV_Boolean;
		break;
	
	case 45:
		dataStoreValue = eDataStoreEnumValue::eDSEV_Byte; 
		break;

	case 47:
		dataStoreValue = eDataStoreEnumValue::eDSEV_CardInal;
		break;

	case 64:
		dataStoreValue = eDataStoreEnumValue::eDSEV_Integer;
		break;
	
	case 66:
		dataStoreValue = eDataStoreEnumValue::eDSEV_LongWord;
		break;

	case 74:
		dataStoreValue = eDataStoreEnumValue::eDSEV_Real;
		break;

	case 79:
		dataStoreValue = eDataStoreEnumValue::eDSEV_ShortInt;
		break;

	case 81:
		dataStoreValue = eDataStoreEnumValue::eDSEV_Single;
		break;

	case 82:
		dataStoreValue = eDataStoreEnumValue::eDSEV_SmallInt;
		break;
	
	case 83:
		dataStoreValue = eDataStoreEnumValue::eDSEV_String;
		break;

	case 92:
		dataStoreValue = eDataStoreEnumValue::eDSEV_Word;
		break;
	
	default:
		break;
	}

	return dataStoreValue;
}
