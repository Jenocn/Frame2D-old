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
	��Object�������������д���麯��,Ȼ�����
	Release����,����delete this,����ֻ�轫��Ҫ
	�ͷŵ��ڴ������������
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
	��new����������Ϊ˽��,������ʹ��new�ķ�����������
	*/
	//void* operator new(size_t);

private:
	int _id;
	string _name;

};

NS_F2D_END

#endif