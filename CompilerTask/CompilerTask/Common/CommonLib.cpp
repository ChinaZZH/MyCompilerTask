#include "CommonLib.h"

using namespace std;


std::string CommonLib::FileRead(std::string szFileName)
{
	std::string strFileContent = "";
	FILE* fp = fopen(szFileName.c_str(), "rt");
	if (NULL == fp)
	{
		return strFileContent;
	}

	int i = 1;
	char Buffer[1];
	while (i == 1)
	{
		i = fread(Buffer, 1, 1, fp);
		if (1 != i)
		{
			break;
		}

		char element = Buffer[0];
		strFileContent.push_back(element);
	}

	fclose(fp);
	return strFileContent;
}


std::string CommonLib::StrErase(std::string szSourceContent, char eraseElement)
{
	std::string strTempContent;
	int nContentNum = szSourceContent.size();
	for(int i = 0; i < nContentNum; ++i){
		if(eraseElement == szSourceContent[i]){
			continue;
		}

		strTempContent.push_back(szSourceContent[i]);
	}

	return strTempContent;
}

std::string CommonLib::trim(std::string str)
{
	return rtrim(ltrim(str));
}


std::string CommonLib::ltrim(std::string str)
{
	if(true == str.empty()){
		return str;
	}

	string szTmp = "";
	unsigned int i;

	for(i = 0; str[i] <= 32 && i < str.length(); i++){
		;
	}

	for(; i < str.length(); i++){
		szTmp.append(1, str[i]);
	}

	return szTmp;
}

std::string CommonLib::rtrim(std::string str)
{
	if(true == str.empty()){
		return str;
	}

	string szTmp = "";
	int i = str.length() - 1;
	for( ; str[i] <= 32 && i >= 0; i--){
		;
	}

	for(int j = 0; j <= i; j++){
		szTmp.append(1, str[j]);
	}

	return szTmp;
}

std::string CommonLib::upperCase(std::string strNeedCastString)
{
	string strNewStringValue = strNeedCastString;
	for(unsigned int i = 0; i < strNewStringValue.length(); i++){

		if(strNewStringValue[i] < 'a' || strNewStringValue[i] > 'z'){
			continue;
		}

		char cNewCharacter = (strNewStringValue[i] - 'a') + 'A';
		strNewStringValue[i] = cNewCharacter;
	}
	
	return strNewStringValue;
}
