#ifndef _LISTENER_H_H_
#define _LISTENER_H_H_

#include "Object.h"

NS_F2D_BEGIN

class EventObj;
class KeyboardFunc;
class MouseFunc;

class Listener
{
public:
	virtual ~Listener()
	{}

	/*
	释放内存,并delete自身
	*/
	void Release()
	{
		_eventObj = 0;
		delete this;
	}

	/*
	函数功能:接受并调用回调函数
	*/
	virtual void Notify(const F2D_MSG_INFO& msg) = 0;

	/*
	函数功能:获得事件对象
	*/
	EventObj* GetEventObj() const
	{
		return _eventObj;
	}

	/*
	绑定监听的对象
	*/
	void RegisterEventObj(EventObj* obj);

	///*
	//是否有效
	//*/
	//bool IsVisible() const
	//{
	//	return _visible;
	//}

	///*
	//函数功能:设置是否有效
	//*/
	//void SetVisible(bool enable)
	//{
	//	_visible = enable;
	//}

protected:
	Listener()
		: _eventObj(0)
	{}

	EventObj* _eventObj;

private:
	Listener(Listener&);
	Listener& operator=(Listener&);
	//bool _visible;
};

/*
键盘消息监听器
*/
class KeyboardListener : public Listener
{
public:
	/*
	函数功能:创建一个按键消息监听器
	参数1:绑定需要监听事件的对象
	参数2:键盘消息的回调函数
	*/
	static KeyboardListener* Create(EventObj* obj, KeyboardFunc* func);

	virtual ~KeyboardListener();
	
	/*
	函数功能:获得消息并继续下发
	*/
	virtual void Notify(const F2D_MSG_INFO& msg);

	/*
	绑定回调函数
	*/
	void RegisterFunc(KeyboardFunc* func);

private:
	KeyboardFunc* _keyboardFunc;
};

// 鼠标事件监听器
class MouseListener : public Listener
{
public:
	/*
	函数功能:创建一个鼠标消息监听器
	参数1:绑定需要监听事件的对象
	参数2:鼠标消息的回调函数
	*/
	static MouseListener* Create(EventObj* obj, MouseFunc* func);
	virtual ~MouseListener();
	virtual void Notify(const F2D_MSG_INFO& msg);
	/*
	绑定回调函数
	*/
	void RegisterFunc(MouseFunc* func);

private:
	MouseFunc* _mouseFunc;
};

NS_F2D_END

#endif