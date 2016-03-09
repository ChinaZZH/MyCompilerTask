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

// �洢����ö��ֵ
enum eDataStoreEnumValue
{
	eDSEV_Null = 0,
	
	eDSEV_Char = 1,
	eDSEV_Boolean = 2,
	eDSEV_Integer = 3,
	eDSEV_Byte = 4,
	eDSEV_ShortInt = 5,

	eDSEV_SmallInt = 6,
	eDSEV_Word = 7,
	eDSEV_LongWord = 8,
	eDSEV_CardInal = 9,
	eDSEV_Real = 10,

	eDSEV_Single = 11,
	eDSEV_Enum   = 12,
	eDSEV_Array  = 13,
	eDSEV_Set    = 14,
	eDSEV_Record = 15,
	
	eDSEV_String = 16,
	eDSEV_File   = 17,
	eDSEV_Pointer= 18,
	eDSEV_Long8  = 19, //��ʽ���ͣ�8�ֽڵ���������
	eDSEV_Func   = 20,

	eDSEV_Proc = 21,
	eDSEV_User = 22,
};



