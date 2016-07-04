#ifndef _ACTION_REALIZE_H_H_
#define _ACTION_REALIZE_H_H_

#include "Action.h"

NS_F2D_BEGIN

class Jump : public Action
{
public:
	/*
	函数功能:创建一个跳跃的动作
	参数1:执行这个跳跃过程所需的时间
	参数2:跳跃的高度
	*/
	static Jump* Create(const float& duration,
		const float& height);

	virtual ~Jump();

	virtual void Init();

	virtual bool InitJump(const float& duration,
		const float& height);
	virtual void Update(const float& delta);

protected:
	Jump()
		: _duration(0)
		, _height(0)
		, _speed(0)
		, _startPosY(0)
		, _bTop(false)
	{}

private:
	Jump(Jump&);
	Jump& operator=(Jump&);

private:
	float _duration;
	float _height;

	float _speed;
	float _startPosY;
	bool _bTop;
};

class Move : public Action
{
public:
	static Move* Create(const float& duration,
		const float& positionX,
		const float& positionY);

	virtual ~Move();

	virtual void Init();

	virtual bool InitMove(const float& duration,
		const float& positionX,
		const float& positionY);

	virtual void Update(const float& delta);

protected:
	Move() {}

private:
	Move(Move&);
	Move& operator=(Move&);

private:
	float _duration;
	float _positionX;
	float _positionY;
	float _speedX;
	float _speedY;
};

NS_F2D_END

#endif