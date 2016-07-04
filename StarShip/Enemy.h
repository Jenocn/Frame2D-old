#ifndef _ENEMY_H_H_
#define _ENEMY_H_H_

#include "Plane.h"

//========================
// 创建敌人的Create函数
//========================
#define ENEMY_CREATE_FUNC(__TYPE__) \
	static __TYPE__* Create(const string& name) \
	{ \
		__TYPE__* pRet = new (nothrow)__TYPE__(); \
		if (pRet && pRet->InitData(name)) \
		{ \
			return pRet; \
		} \
		return 0; \
	}

class MoveState;

// 敌人类
class Enemy : public Plane
{
public:
	ENEMY_CREATE_FUNC(Enemy);

	virtual ~Enemy();

	virtual bool InitData(const string& name);

	virtual bool Attack();

	virtual bool MissileShoot();

	virtual void Move();

	virtual void Die();

	virtual void Update(const float& delta);

	void ChangeMoveState(const int& stateID);

	// setter
	void SetDuration(const float& duration);
	void SetStayTime(const float& stayTime);
	void SetScore(const int& score);
	void SetItemID(const int& itemID);

	// getter
	float GetDuration() const;
	float GetStayTime() const;
	int GetScore() const;
	int GetItemID() const;

protected:
	Enemy()
	: _state(0)
	, _duration(0)
	, _stayTime(0)
	, _score(0)
	, _itemID(0)
	{}

	Enemy(
	const float& hp,
	const float& hpMax,
	const float& moveSpeed,
	const float& directionAngle)
	: Plane(hp, hpMax, moveSpeed, directionAngle, false, false)
	, _state(0)
	, _duration(0)
	, _stayTime(0)
	, _score(0)
	, _itemID(0)
	{}

	void ChangeBulletType(const int& type);

private:
	Enemy(Enemy&);
	Enemy& operator=(Enemy&);

private:
	MoveState* _state;
	// 持续的时间
	float _duration;
	// 持续时间后停留的时间
	float _stayTime;
	// 携带分数
	int _score;
	// 携带道具id
	int _itemID;
};

#endif