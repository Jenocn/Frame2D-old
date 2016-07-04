#ifndef _F2D_FUNC_H_H_
#define _F2D_FUNC_H_H_

#include "Object.h"

NS_F2D_BEGIN

/*
	更新函数类
	void Update(const float&)
*/
class UpdateFunc : public Object
{
public:
	static UpdateFunc* Create(function<void(const float&)> func);

	void RegisterFunc(function<void(const float&)> func);

	void Release();

	void Update(const float& delta);

private:
	UpdateFunc() {}
	UpdateFunc(UpdateFunc&);
	UpdateFunc& operator=(UpdateFunc&);

private:
	function<void(const float&)> _updateFunc;
};

/*
	键盘消息回调函数
	void KeyboardFunc(const ENUM_F2D_MESSAGE& msg, const ENUM_F2D_KEYCODE& keycode)
*/
class KeyboardFunc : public Object
{
public:
	static KeyboardFunc* Create(function<void(const ENUM_F2D_MESSAGE&, const ENUM_F2D_KEYCODE&)> func);

	void RegisterFunc(function<void(const ENUM_F2D_MESSAGE&, const ENUM_F2D_KEYCODE&)> func);

	void Release();

	void Notify(const ENUM_F2D_MESSAGE& message, const ENUM_F2D_KEYCODE& keycode);

private:
	KeyboardFunc(){}
	KeyboardFunc(KeyboardFunc&);
	KeyboardFunc& operator=(KeyboardFunc&);

private:
	function<void(const ENUM_F2D_MESSAGE&, const ENUM_F2D_KEYCODE&)> _func;
};

/*
鼠标消息回调函数
void MouseFunc(const ENUM_F2D_MESSAGE& msg, int cursorPosX, int cursorPosY, int value)
*/
class MouseFunc : public Object
{
public:
	static MouseFunc* Create(function<void(const ENUM_F2D_MESSAGE&, const int&, const int&, const int&)> func);

	void RegisterFunc(function<void(const ENUM_F2D_MESSAGE&, const int&, const int&, const int&)> func);

	void Release();

	void Notify(const ENUM_F2D_MESSAGE& message, const int& cursorPosX, const int& cursorPosY, const int& value);

private:
	MouseFunc(){}
	MouseFunc(MouseFunc&);
	MouseFunc& operator=(MouseFunc&);

private:
	function<void(const ENUM_F2D_MESSAGE&, const int&, const int&, const int&)> _func;
};

NS_F2D_END

#endif