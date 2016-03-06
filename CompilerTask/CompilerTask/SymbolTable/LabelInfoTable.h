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
#include "CommonObjectInfo.h"
#include <map>

struct LabelInfo :CommonObjectInfo
{
	bool m_bDef;  // �Ƿ��Ѿ�����
	bool m_bUse;  // �Ƿ��Ѿ�ʹ��

	LabelInfo()
		:m_bDef(false)
		, m_bUse(false)
	{ }
};

typedef std::map<int, LabelInfo> LabelInfoMap;
class LabelInfoTable
{
public:
	LabelInfoTable();
	~LabelInfoTable();

public:
	bool addLabelInfo(LabelInfo newLabelInfo);

	int searchLableInfoTable(const int nProcIdValue, const std::string& strLableName);

private:
	LabelInfoMap m_mapLabelInfoTable;
};