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

class BaseSemanticser
{
public:
	BaseSemanticser() { }

	virtual ~BaseSemanticser() = 0;

public:
	virtual bool processSemanticsParser() = 0;
};