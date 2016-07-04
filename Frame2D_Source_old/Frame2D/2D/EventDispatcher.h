#ifndef _EVENT_DISPATCHER_H_H_
#define _EVENT_DISPATCHER_H_H_

#include "Object.h"

NS_F2D_BEGIN

class Listener;
class EventObj;

class EventDispatcher
{
public:
	static EventDispatcher* getInstance();

	void Release();

	void Notify(const MSG& msg);

	void Add(Listener* listener);
	void Remove(Listener* listener);

	void RemoveByEventObj(EventObj* obj);

	void Clear();

private:
	EventDispatcher(){}
	EventDispatcher(EventDispatcher&);
	EventDispatcher& operator=(EventDispatcher&);

private:
	F2D_MSG_INFO _msgInfo;
	vector<Listener*> m_listener_list;
};

NS_F2D_END

#endif