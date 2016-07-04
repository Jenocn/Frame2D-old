#ifndef _BULLET_REALIZE_H_H_
#define _BULLET_REALIZE_H_H_

#include "Bullet.h"

//==================
// 向前的
// 朝着角度的方向一直向前
//==================
class BulletOnward : public Bullet
{
public:
	BULLET_CREATE_FUNC(BulletOnward);

protected:
	//========================
	// 更新运动轨迹
	//========================
	virtual void TrackUpdate(const float& delta);

	BulletOnward() {}

private:
	BulletOnward(BulletOnward&);
	BulletOnward& operator=(BulletOnward&);
};

//==================
// 右偏曲线
// 朝着角度的方向走cos偏右曲线
//==================
class BulletCurveCosR : public Bullet
{
public:
	BULLET_CREATE_FUNC(BulletCurveCosR);

protected:
	//========================
	// 更新运动轨迹
	//========================
	virtual void TrackUpdate(const float& delta);

	BulletCurveCosR()
	: _curveTempAngle(0)
	, _beginAngle(0)
	, _bSave(false)
	{}

private:
	BulletCurveCosR(BulletCurveCosR&);
	BulletCurveCosR& operator=(BulletCurveCosR&);

protected:
	float _curveTempAngle;
	float _beginAngle;
	bool _bSave;
};

//==================
// 左偏曲线
// 朝着角度的方向走cos偏左曲线
//==================
class BulletCurveCosL : public Bullet
{
public:
	BULLET_CREATE_FUNC(BulletCurveCosL);

protected:
	//========================
	// 更新运动轨迹
	//========================
	virtual void TrackUpdate(const float& delta);

	BulletCurveCosL()
		: _curveTempAngle(0)
		, _beginAngle(0)
		, _bSave(false)
	{}

private:
	BulletCurveCosL(BulletCurveCosL&);
	BulletCurveCosL& operator=(BulletCurveCosL&);

protected:
	float _curveTempAngle;
	float _beginAngle;
	bool _bSave;
};

//=========================
// 导弹轨迹
//=========================
class BulletMissile : public Bullet
{
public:
	BULLET_CREATE_FUNC(BulletMissile);

protected:
	virtual void TrackUpdate(const float& delta);

	BulletMissile()
	: _stopTime(0.1)
	, _beginMoveSpeed(0)
	, _bSave(false)
	{}

private:
	BulletMissile(BulletMissile&);
	BulletMissile& operator=(BulletMissile&);

protected:
	float _stopTime;
	float _beginMoveSpeed;
	bool _bSave;

};

//=========================
// 散弹
//=========================
class BulletDisperse : public Bullet
{
public:
	BULLET_CREATE_FUNC(BulletDisperse);

protected:
	virtual void TrackUpdate(const float& delta);

	BulletDisperse()
		: _stopTime(0.05)
	{}

private:
	BulletDisperse(BulletDisperse&);
	BulletDisperse& operator=(BulletDisperse&);

protected:
	float _stopTime;
};

//====================
// 跟踪弹
//====================
class BulletFollow : public Bullet
{
public:
	BULLET_CREATE_FUNC(BulletFollow);

protected:
	virtual void TrackUpdate(const float& delta);

	BulletFollow()
		: _target(0)
		, _prepareTime(0.1)
		, _waitTime(1)
		, _followTime(5)
	{}

private:
	BulletFollow(BulletFollow&);
	BulletFollow& operator=(BulletFollow&);

protected:
	Element* _target; // 目标元素
	float _prepareTime; // 准备时间(准备时间中不跟随目标,一般是刚发射的一段时间)
	float _waitTime; // 等待时间(等待时间是从准备时间结束后开始,如果等待时间结束还没有目标那么再也不跟随)
	float _followTime; // 跟随直接(跟随一个目标的时间,如果时间内没有攻击到目标,那么不再追击)
};

//====================
// 反弹子弹
//====================
class BulletRebound : public BulletFollow
{
public:
	BULLET_CREATE_FUNC(BulletRebound);

	virtual void Die();

protected:
	virtual void TrackUpdate(const float& delta);

	BulletRebound()
	: _count(5)
	{}

	BulletRebound(const int& count)
	: _count(count)
	{}

private:
	BulletRebound(BulletRebound&);
	BulletRebound& operator=(BulletRebound&);

private:
	int _count;
};

//====================
// 先直线后反弹
//====================
class BulletReboundOnward : public BulletOnward
{
public:
	BULLET_CREATE_FUNC(BulletReboundOnward);

	virtual void Die();

protected:
	virtual void TrackUpdate(const float& delta);

	BulletReboundOnward()
		: _count(5)
	{}

	BulletReboundOnward(const int& count)
		: _count(count)
	{}

private:
	BulletReboundOnward(BulletReboundOnward&);
	BulletReboundOnward& operator=(BulletReboundOnward&);

private:
	int _count;
};

//====================
// 首次锁定
//====================
class BulletLockBeginPosition : public BulletOnward
{
public:
	BULLET_CREATE_FUNC(BulletLockBeginPosition);

protected:
	virtual void TrackUpdate(const float& delta);

	BulletLockBeginPosition()
	: _positionX(0)
	, _positionY(0)
	, _bLock(false)
	, _bSet(false)
	{}

private:
	BulletLockBeginPosition(BulletLockBeginPosition&);
	BulletLockBeginPosition& operator=(BulletLockBeginPosition&);

private:
	float _positionX;
	float _positionY;
	bool _bLock;
	bool _bSet;
};

#endif