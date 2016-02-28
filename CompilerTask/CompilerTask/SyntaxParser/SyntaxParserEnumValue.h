/********************************************************************
            Copyright (c) 2015
                   All rights reserved
         
    创建日期：  2015年 月 日 时 分
    文件名称：  
    说    明：       
    
    当前版本：  
    作    者：  郑祖煌
    概    述：      

*********************************************************************/

#pragma once

enum eSyntaxParserHandlerTag
{
	eSPHT_ErrorSymbol = 0,  // 异常符号
	eSPHT_NullSymbol  = 1,  // 空符号

	eSPHT_TerminalSymbol   = 2,  // 终结符
	eSPHT_NoTerminalSymbol = 3,  // 非终结符
	eSPHT_Semantics = 4,  // 语义    
};