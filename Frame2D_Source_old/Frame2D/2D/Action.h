#ifndef _ACTION_H_H_
#define _ACTION_H_H_

#include "Object.h"

NS_F2D_BEGIN

class Element;

class Action : public Object
{
public:
	virtual ~Action() {}

	void Release()
	{
		delete this;
	}

	virtual void Init() = 0;

	/*
		更新函数
	*/
	virtual void Update(const float& delta) = 0;

	/*
		函数功能:注册动作对象
	*/
	void Register(Element* element)
	{
		_element = element;
		Init();
	}

	bool IsFinish()
	{
		return _finish;
	}

protected:
	Action()
		: _element(0)
		, _finish(false)
	{}
	Element* _element;
	bool _finish;

private:
	Action(Action&);
	Action& operator=(Action&);
};

NS_F2D_END

#endif