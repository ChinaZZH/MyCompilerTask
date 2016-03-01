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

enum eLexStateValue
{
	eLSV_IntegerBackTwoCharacter = -42, // �Ƿ���Ҫ���������ַ�  
	eLSV_Error = -99,  // ����

	eLSV_TerminationState = 0,  // ��ֹ״̬�ж� <0 Ϊ��ֹ״̬

	// ��ʶ����ֹ(�ؼ���,����)
	eLSV_Identifier = 1,

	// ����
	eLSV_ConstantDataStartIndex = 2,
	eLSV_ConstantString = 2,
	eLSV_ConstantInteger = 3,
	eLSV_ConstantCommonReal = 4,
	eLSV_ConstantSciencePlusReal = 5,
	eLSV_ConstantScienceReal = 6,
	eLSV_ConstantDataEndIndex = 6,

	// ���
	eSLV_BoundStartIndex = 7,
	eSLV_BoundEndIndex = 15,

	// �����
	eSLV_OperatorStartIndex = 16,
	eSLV_OperatorEndIndex = 28,    // ��ֵ

	// ���ս�� ���������
	eSLV_StartSyntaxParser = 100,
	eSLV_SemanticsParserStart = 300, 
};

enum eConstantEnumValue
{
	eCEV_ConstantNull = 0,
	eCEV_ConstantString = 2,
	eCEV_ConstantInteger = 3,
	eCEV_ConstantCommonReal = 4,
	eCEV_ConstantSciencePlusReal = 5,
	eCEV_ConstantScienceReal = 6,
	eCEV_ConstantBoolValue = 7,
	eCEV_ConstantEnumValue = 8,
	eCEV_ConstantSetValue = 9,
	eCEV_ConstantPtrValue = 10,
};


// �ս��������
enum eEndSymbolType
{
	eEST_Identifier = 1,  // ��ʶ��
	eEST_ConstantValue = 2,  // ����
	eEST_BoundSymbol = 3,  // ���
	eEST_OperatorSymbol = 4,  // �����
	eEST_TwoPoint = 5,  // 
	eEST_Other = 6,
};

