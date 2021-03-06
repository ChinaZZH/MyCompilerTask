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

enum eSemansticeParserTypeValue
{
	eSPEV_NullParser = 0,

	eSPEV_MainProgramHeaderStatementParser = 301,
	eSPEV_LabelStatmentParser = 303,
	eSPEV_ConstStatmentParser = 304,
	//eSPEV_ProcCallSentence = 305,  // 未实现

	eSPEV_TypeDefineParser = 306,     
	eSPEV_BaseTypeDefineAndStatement = 307,
	eSPEV_PointerSimpleIndetifierType = 308,  // 简单类型->标识符
	eSPEV_PointerSimpleType = 309,

	eSPEV_AfterAllTypeConstruct = 310,  
	eSPEV_EnumTypeDefineBeforeIdentifier = 311,
	eSPEV_IdentifierTypeDefineList = 312,
	eSPEV_VarDefineBeforeList = 313,
	eSPEV_EnumTypeDefineAfterIdentifier = 314,
	eSPEV_BeforeAllTypeConstruct = 315,  

	eSPEV_ArrayTypeBeforeLeftBrackets = 316, 
	eSPEV_ArrayIntegerConstant  = 317,
	eSPEV_ArrayEndIntegerConstant = 318,
	eSPEV_BeforeRecordTypeStatement = 319,
	eSPEV_AfterRecordTypeStatement  = 320,

	//eSPEV_ProcedureTypeBeforeArgsList = 321,
	eSPEV_UserDefineTypeStatement  = 323,
	eSPEV_SetTypeBeforeSpecficType = 324,
	eSPEV_SetTypeAfterSpecficType = 325,

	eSPEV_FieldVarTypeBeforeTypeValue = 329,
	eSPEV_FieldVarTypeAfterEndStatus  = 330,
	eSPEV_OneFieldVarTypeBeforeList   = 331,
	eSPEV_OneFieldVarTypeAfterList    = 332,
	eSPEV_FieldVarTypeAfterTypeValue  = 333,
	eSPEV_FieldVarTypeBeforeEndStatus = 334,

	//eSPEV_ProcedureTypeAfterArgsList = 339,
	eSPEV_VarDefineAfterList = 340,

	eSPEV_IncludeFileBeforeFileName = 393,
	eSPEV_IncludeFileAfterFileName = 394,
	//eSPEV_ProcedureTypeAfterArgsListNextTwo = 344,
};

//eSPEV_NullParser = 0,   标号声明

//eSPEV_MainProgramHeaderStatementParser = 301, // 主程序首部声明
//eSPEV_LabelStatmentParser = 303,  // 标号声明
//eSPEV_ConstStatmentParser = 304,  // 常量声明
//eSPEV_ProcCallSentence    = 305,
//
//eSPEV_TypeDefineParser = 306,  // 类型定义
//eSPEV_ProcStatmentParser  = 307,
//
// 变量部分
//eSPEV_VarIdentifierDefineList = 312,  // 标识符列表->标识符 012 标识符列表1    标识符列表1->, 标识符 012 标识符列表1  
//eSPEV_VarDefineBeforeList = 313,      // 变量定义 (变量定义-->013 标识符列表 040：类型)
//eSPEV_VarDefineAfterList = 340,      // 变量定义 (变量定义-->013 标识符列表 040：类型)

