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