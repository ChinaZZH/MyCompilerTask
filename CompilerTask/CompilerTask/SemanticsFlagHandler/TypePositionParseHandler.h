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
#include <stack>


typedef std::stack<int> TypePaserStack; 

class TypePositionParseHandler
{
public:
	TypePositionParseHandler();
	~TypePositionParseHandler();

public:
	void addProcessingTypeInfoAddress(int nTypeInfoAddress);

private:
	TypePaserStack  m_stackTypePaser;
};

