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

template <typename T>
struct Singleton
{
private:
	struct object_creator
	{
		object_creator() { Singleton<T>::instance(); }
		inline void do_nothing() const { }
	};
	static object_creator create_object;
	Singleton();
public:
	typedef  T  object_type;
	static object_type & instance()
	{
		static object_type obj;
		create_object.do_nothing();
		return obj;
	}
};

template <typename T>  typename Singleton<T>::object_creator Singleton<T>::create_object;