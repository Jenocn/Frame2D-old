#ifndef _OBJECT_H_H_
#define _OBJECT_H_H_

#include "..\Common.h"
#include "..\F2DEnum.h"
#include "..\F2DMacros.h"
#include "..\F2DStruct.h"
#include "..\_Use.h"

NS_F2D_BEGIN

class Object
{
public:
	Object() {}

	/*
	将Object基类的析构函数写成虚函数,然后添加
	Release函数,调用delete this,子类只需将需要
	释放的内存放入析构函数
	*/
	//virtual ~Object();
	// void Release() { delete this; }

	void SetID(const int& id)
	{
		_id = id;
	}

	void SetName(const string& name)
	{
		_name = name;
	}

	int GetID() const
	{
		return _id;
	}

	string GetName() const
	{
		return _name;
	}

private:
	Object(Object&);
	Object& operator=(Object&);

	/*
	将new操作符声明为私有,不允许使用new的方法创建对象
	*/
	//void* operator new(size_t);

private:
	int _id;
	string _name;

};

NS_F2D_END

#endif