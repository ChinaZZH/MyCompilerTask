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

enum eSemansticeParserTypeValue
{
	eSPEV_NullParser = 0,

	eSPEV_MainProgramHeaderStatementParser = 301,
	eSPEV_LabelStatmentParser = 303,
	eSPEV_ConstStatmentParser = 304,
	//eSPEV_ProcCallSentence = 305,  // δʵ��

	eSPEV_TypeDefineParser = 306,     
	//eSPEV_BaseTypeParser = 307,
	eSPEV_PointerSimpleIndetifierType = 308,  // ������->��ʶ��
	eSPEV_PointerSimpleType = 309,

	eSPEV_AfterAllTypeConstruct = 310,  
	eSPEV_IdentifierTypeDefineList = 312,
	eSPEV_VarDefineBeforeList = 313,
	//eSPEV_EnumTypeDefine = 314,
	eSPEV_BeforeAllTypeConstruct = 315,  

	eSPEV_BeforeRecordTypeStatement = 319,
	eSPEV_AfterRecordTypeStatement  = 320,

	//eSPEV_ProcedureTypeBeforeArgsList = 321,
	eSPEV_SetTypeBeforeSpecficType = 324,
	eSPEV_SetTypeAfterSpecficType = 325,

	//eSPEV_ProcedureTypeAfterArgsList = 339,
	eSPEV_VarDefineAfterList = 340,

	eSPEV_IncludeFileBeforeFileName = 393,
	eSPEV_IncludeFileAfterFileName = 394,
	//eSPEV_ProcedureTypeAfterArgsListNextTwo = 344,
};

//eSPEV_NullParser = 0,   �������

//eSPEV_MainProgramHeaderStatementParser = 301, // �������ײ�����
//eSPEV_LabelStatmentParser = 303,  // �������
//eSPEV_ConstStatmentParser = 304,  // ��������
//eSPEV_ProcCallSentence    = 305,
//
//eSPEV_TypeDefineParser = 306,  // ���Ͷ���
//eSPEV_ProcStatmentParser  = 307,
//
// ��������
//eSPEV_VarIdentifierDefineList = 312,  // ��ʶ���б�->��ʶ�� 012 ��ʶ���б�1    ��ʶ���б�1->, ��ʶ�� 012 ��ʶ���б�1  
//eSPEV_VarDefineBeforeList = 313,      // �������� (��������-->013 ��ʶ���б� 040������)
//eSPEV_VarDefineAfterList = 340,      // �������� (��������-->013 ��ʶ���б� 040������)

