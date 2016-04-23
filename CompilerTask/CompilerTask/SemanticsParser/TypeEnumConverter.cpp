#include "TypeEnumConverter.h"

TypeEnumConverter::TypeEnumConverter()
{

}

TypeEnumConverter::~TypeEnumConverter()
{

}

eDataStoreEnumValue TypeEnumConverter::wordStatusToDataStoreType(int nWordStatus)
{
	enum eWordStatusValue
	{
		eWSV_BooleanWordStatus = 44,
		eWSV_ByteWordStatus = 45,
		eWSV_CardInal = 47,
		eWSV_CharWordStatus = 49,

		eWSV_IntegerWordStatus = 64,
		eWSV_LongWordWordStatus = 66,

		eWSV_RealWordStatus = 74,
		eWSV_ShortIntWordStatus = 79,
		eWSV_SingleWordStatus = 81,
		eWSV_SmallIntWordStatus = 82,
		eWSV_StringWordStatus = 83,

		eWSV_WordWordStatus = 92,
	};

	eDataStoreEnumValue dataStoreValue = eDSEV_Null;
	switch(nWordStatus)
	{
	case eWSV_CharWordStatus:
		dataStoreValue = eDataStoreEnumValue::eDSEV_Char;
		break;

	case eWSV_BooleanWordStatus:
		dataStoreValue = eDataStoreEnumValue::eDSEV_Boolean;
		break;
	
	case eWSV_ByteWordStatus:
		dataStoreValue = eDataStoreEnumValue::eDSEV_Byte; 
		break;

	case eWSV_CardInal:
		dataStoreValue = eDataStoreEnumValue::eDSEV_CardInal;
		break;

	case eWSV_IntegerWordStatus:
		dataStoreValue = eDataStoreEnumValue::eDSEV_Integer;
		break;
	
	case eWSV_LongWordWordStatus:
		dataStoreValue = eDataStoreEnumValue::eDSEV_LongWord;
		break;

	case eWSV_RealWordStatus:
		dataStoreValue = eDataStoreEnumValue::eDSEV_Real;
		break;

	case eWSV_ShortIntWordStatus:
		dataStoreValue = eDataStoreEnumValue::eDSEV_ShortInt;
		break;

	case eWSV_SingleWordStatus:
		dataStoreValue = eDataStoreEnumValue::eDSEV_Single;
		break;

	case eWSV_SmallIntWordStatus:
		dataStoreValue = eDataStoreEnumValue::eDSEV_SmallInt;
		break;
	
	case eWSV_StringWordStatus:
		dataStoreValue = eDataStoreEnumValue::eDSEV_String;
		break;

	case eWSV_WordWordStatus:
		dataStoreValue = eDataStoreEnumValue::eDSEV_Word;
		break;
	
	default:
		break;
	}

	return dataStoreValue;
}
