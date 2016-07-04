#ifndef _MOVE_STATE_REALIZE_H_H_
#define _MOVE_STATE_REALIZE_H_H_

#include "MoveState.h"

class MoveStateOnward : public MoveState
{
public:
	MOVESTATE_CREATE_FUNC(MoveStateOnward);

	virtual void Update(const float& delta);

protected:
	MoveStateOnward() {}

private:
	MoveStateOnward(MoveStateOnward&);
	MoveStateOnward& operator=(MoveStateOnward&);
};

class MoveStateCircleL : public MoveState
{
public:
	MOVESTATE_CREATE_FUNC(MoveStateCircleL);

	virtual void Update(const float& delta);

protected:
	MoveStateCircleL()
		: _angle(0)
	{}

private:
	MoveStateCircleL(MoveStateCircleL&);
	MoveStateCircleL& operator=(MoveStateCircleL&);

private:
	float _angle;
};

class MoveStateCircleR : public MoveState
{
public:
	MOVESTATE_CREATE_FUNC(MoveStateCircleR);

	virtual void Update(const float& delta);

protected:
	MoveStateCircleR()
		: _angle(0)
	{}

private:
	MoveStateCircleR(MoveStateCircleR&);
	MoveStateCircleR& operator=(MoveStateCircleR&);

private:
	float _angle;
};

class MoveStateBack : public MoveState
{
public:
	MOVESTATE_CREATE_FUNC(MoveStateBack);

	virtual void Update(const float& delta);

protected:
	MoveStateBack()
		: _backTime(1)
		, _beginAngle(0)
		, _bSave(false)
	{}

private:
	MoveStateBack(MoveStateBack&);
	MoveStateBack& operator=(MoveStateBack&);

private:
	float _backTime;
	float _beginAngle;
	bool _bSave;
};

class MoveStateWander : public MoveState
{
public:
	MOVESTATE_CREATE_FUNC(MoveStateWander);

	virtual void Update(const float& delta);

protected:
	MoveStateWander() {}

private:
	MoveStateWander(MoveStateWander&);
	MoveStateWander& operator=(MoveStateWander&);
};

#endif