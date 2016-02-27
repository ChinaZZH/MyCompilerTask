/********************************************************************
            Copyright (c) 2015
                   All rights reserved
         
    创建日期：  2015年 月 日 时 分
    文件名称：  
    说    明：       
    
    当前版本：  
    作    者：  郑祖煌
    概    述：      

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