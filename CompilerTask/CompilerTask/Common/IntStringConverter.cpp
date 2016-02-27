
#include "IntStringConverter.h"

IntStringConverter::IntStringConverter()
{

}

IntStringConverter::~IntStringConverter()
{

}

std::string IntStringConverter::intValueConvertToString(int nValue)
{
	char stringValue[24] = { 0 };
	sprintf_s(stringValue, "%d", nValue);
	
	std::string strConvertValue(stringValue);
	return strConvertValue;
}
