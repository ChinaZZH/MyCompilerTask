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

enum eSyntaxParserHandlerTag
{
	eSPHT_ErrorSymbol = 0,  // �쳣����
	eSPHT_NullSymbol  = 1,  // �շ���

	eSPHT_TerminalSymbol   = 2,  // �ս��
	eSPHT_NoTerminalSymbol = 3,  // ���ս��
	eSPHT_Semantics = 4,  // ����    
};