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

enum eSemansticeParserEnumValue
{
	eSPEV_NullParser = 0,  // �������

	eSPEV_MainProgramHeaderStatementParser = 301, // �������ײ�����
	eSPEV_LabelStatmentParser = 303,  // �������
	eSPEV_ConstStatmentParser = 304,  // ��������
	//eSPEV_ProcCallSentence    = 305,

	eSPEV_TypeDefineParser  = 306,  // ���Ͷ���
	//eSPEV_VarStatmentParser   = 306,
	//eSPEV_ProcStatmentParser  = 307,
};