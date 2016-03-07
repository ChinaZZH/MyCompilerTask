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

enum eSemansticeParserEnumValue
{
	eSPEV_NullParser = 0,  // 标号声明

	eSPEV_MainProgramHeaderStatementParser = 301, // 主程序首部声明
	eSPEV_LabelStatmentParser = 303,  // 标号声明
	eSPEV_ConstStatmentParser = 304,  // 常量声明
	//eSPEV_ProcCallSentence    = 305,

	eSPEV_TypeDefineParser  = 306,  // 类型定义
	//eSPEV_VarStatmentParser   = 306,
	//eSPEV_ProcStatmentParser  = 307,
};