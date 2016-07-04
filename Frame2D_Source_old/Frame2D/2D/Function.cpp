#include "Function.h"

USING_NS_F2D

UpdateFunc* UpdateFunc::Create(function<void(const float&)> func)
{
	UpdateFunc* updateFunc = new (nothrow)UpdateFunc();
	assert(updateFunc && "UpdateFunc Create Failed!");
	updateFunc->RegisterFunc(func);

	return updateFunc;
}

void UpdateFunc::RegisterFunc(function<void(const float&)> func)
{
	_updateFunc = func;
}

void UpdateFunc::Release()
{
	delete this;
}

void UpdateFunc::Update(const float& delta)
{
	_updateFunc(delta);
}

///////////////////////////////
// keyboard
///////////////////////////////
KeyboardFunc* KeyboardFunc::Create(function<void(const ENUM_F2D_MESSAGE&, const ENUM_F2D_KEYCODE&)> func)
{
	KeyboardFunc* keyFun = new(nothrow) KeyboardFunc();
	assert(keyFun && "KeyboardFunc Create Failed!");
	keyFun->RegisterFunc(func);
	return keyFun;
}

void KeyboardFunc::RegisterFunc(function<void(const ENUM_F2D_MESSAGE&, const ENUM_F2D_KEYCODE&)> func)
{
	_func = func;
}

void KeyboardFunc::Release()
{
	delete this;
}

void KeyboardFunc::Notify(const ENUM_F2D_MESSAGE& message, const ENUM_F2D_KEYCODE& keycode)
{
	_func(message, keycode);
}


/////////////////////////////////
// Mouse
////////////////////////////////
MouseFunc* MouseFunc::Create(function<void(const ENUM_F2D_MESSAGE&, const int&, const int&, const int&)> func)
{
	MouseFunc* mouseFunc = new(nothrow) MouseFunc();
	assert(mouseFunc && "MouseFunc Create Failed!");
	mouseFunc->RegisterFunc(func);

	return mouseFunc;
}

void MouseFunc::RegisterFunc(function<void(const ENUM_F2D_MESSAGE&, const int&, const int&, const int&)> func)
{
	_func = func;
}

void MouseFunc::Release()
{
	delete this;
}

void MouseFunc::Notify(const ENUM_F2D_MESSAGE& message, const int& cursorPosX, const int& cursorPosY, const int& value)
{
	_func(message, cursorPosX, cursorPosY, value);
}

