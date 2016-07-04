#include "Listener.h"
#include "Function.h"
#include "EventObj.h"

USING_NS_F2D

void Listener::RegisterEventObj(EventObj* obj)
{
	_eventObj = obj;
}


/////////////////////////////
// KeyboardListener
/////////////////////////////
KeyboardListener* KeyboardListener::Create(EventObj* obj, KeyboardFunc* func)
{
	KeyboardListener* lis = new (nothrow)KeyboardListener();
	lis->RegisterEventObj(obj);
	lis->RegisterFunc(func);

	return lis;
}

KeyboardListener::~KeyboardListener()
{
	_keyboardFunc->Release();
}

void KeyboardListener::Notify(const F2D_MSG_INFO& msg)
{
	_keyboardFunc->Notify(msg.message, msg.keycode);
}

void KeyboardListener::RegisterFunc(KeyboardFunc* func)
{
	_keyboardFunc = func;
}

///////////////////////////////////////
// MouseListener
//////////////////////////////////////
MouseListener* MouseListener::Create(EventObj* obj, MouseFunc* func)
{
	MouseListener* listener = new(nothrow) MouseListener();
	assert(listener && "MouseListener Create Failed!");
	listener->RegisterEventObj(obj);
	listener->RegisterFunc(func);

	return listener;
}

MouseListener::~MouseListener()
{
	_mouseFunc->Release();
}

void MouseListener::Notify(const F2D_MSG_INFO& msg)
{
	_mouseFunc->Notify(msg.message, msg.positionX, msg.positionY, 0);
}

void MouseListener::RegisterFunc(MouseFunc* func)
{
	_mouseFunc = func;
}
