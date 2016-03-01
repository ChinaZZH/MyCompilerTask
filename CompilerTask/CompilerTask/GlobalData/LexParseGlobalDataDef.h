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

enum eLexStateValue
{
	eLSV_IntegerBackTwoCharacter = -42, // 是否需要回退两个字符  
	eLSV_Error = -99,  // 出错

	eLSV_TerminationState = 0,  // 终止状态判断 <0 为终止状态

	// 标识符终止(关键字,变量)
	eLSV_Identifier = 1,

	// 常量
	eLSV_ConstantDataStartIndex = 2,
	eLSV_ConstantString = 2,
	eLSV_ConstantInteger = 3,
	eLSV_ConstantCommonReal = 4,
	eLSV_ConstantSciencePlusReal = 5,
	eLSV_ConstantScienceReal = 6,
	eLSV_ConstantDataEndIndex = 6,

	// 界符
	eSLV_BoundStartIndex = 7,
	eSLV_BoundEndIndex = 15,

	// 运算符
	eSLV_OperatorStartIndex = 16,
	eSLV_OperatorEndIndex = 28,    // 赋值

	// 非终结符 程序结束符
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


// 终结符号类型
enum eEndSymbolType
{
	eEST_Identifier = 1,  // 标识符
	eEST_ConstantValue = 2,  // 常量
	eEST_BoundSymbol = 3,  // 界符
	eEST_OperatorSymbol = 4,  // 运算符
	eEST_TwoPoint = 5,  // 
	eEST_Other = 6,
};

