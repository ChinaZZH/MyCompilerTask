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

struct CommonObjectInfo
{
	std::string m_strName;  // ��Ӧ������
	int m_nProcIndex;       // �������̵�ָ��

	CommonObjectInfo()
		:m_strName(0)
		, m_nProcIndex(0)
	{ }
};