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
#include "BaseSemanticser.h"

class BeforeAllTypeConstructSemanticser : public BaseSemanticser
{
public:
	BeforeAllTypeConstructSemanticser();
	~BeforeAllTypeConstructSemanticser();

public:
	virtual bool processSemanticsParser();

	virtual eSemansticeParserTypeValue returnSemanticserEnumValue();

private:
	void helpProcessRecordType();

	void helpProcessArrayType();

	void helpProcessFunctionType();
};