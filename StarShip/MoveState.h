#ifndef _MOVE_STATE_H_H_
#define _MOVE_STATE_H_H_

#include <new>

class Plane;

#define MOVESTATE_CREATE_FUNC(__TYPE__) \
	static __TYPE__* Create(Plane* plane) \
	{ \
		__TYPE__* pRet = new(std::nothrow) __TYPE__(); \
		if (pRet) \
		{ \
			pRet->RegisterPlane(plane); \
			return pRet; \
		} \
		return 0; \
	}

class MoveState
{
public:
	void RegisterPlane(Plane* plane)
	{
		_plane = plane;
	}

	void Release()
	{
		delete this;
	}

	virtual void Update(const float& delta) = 0;

protected:
	MoveState() {}

private:
	MoveState(MoveState&);
	MoveState& operator=(MoveState&);

protected:
	Plane* _plane;
};

#endif