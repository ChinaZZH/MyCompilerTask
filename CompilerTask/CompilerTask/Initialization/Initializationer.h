/********************************************************************
            Copyright (c) 2015
                   All rights reserved
         
    �������ڣ�  2015�� �� �� ʱ ��
    �ļ����ƣ�  
    ˵    ����       
    
    ��ǰ�汾��  
    ��    �ߣ�  ֣���
    ��    ����      

*********************************************************************/

#pragma once

#include <string>
#include <vector>
#include "../Common/Structure.h"
#include <map>
#include "../Common/Singleton.h"


using namespace std;
class Initializationer
{
public:
	Initializationer();

	~Initializationer();

public:
	void initBeforeLexParse();
};

typedef Singleton<Initializationer> InitializationerInst;