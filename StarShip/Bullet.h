#ifndef _BULLET_H_H_
#define _BULLET_H_H_

#include <Frame2D.h>
#include "GameCommon.h"

//========================
// 创建子弹的Create函数
//========================
#define BULLET_CREATE_FUNC(__TYPE__) \
	static __TYPE__* Create(const string& name) \
	{ \
		__TYPE__* pRet = new (nothrow)__TYPE__(); \
		if (pRet && pRet->InitData(name)) \
		{ \
			return pRet; \
		} \
		return 0; \
	}

//===================
// 子弹基类
// 继承自Sprite类
//===================
class Bullet : public Frame2D::Sprite
{
public:
	//========================
	// 虚析构函数
	//========================
	virtual ~Bullet();

	//===================
	// 死亡
	//===================
	virtual void Die();

	//========================
	// 初始化子弹数据
	// 参数:子弹名称(管理器中的key值)
	//========================
	bool InitData(const string& name);

	//========================
	// 更新子弹数据
	//========================
	void Update(const float& delta) final;

	//========================
	// setter
	//========================
	void SetMoveSpeed(const float& moveSpeed);
	void SetMoveAcceleration(const float& acceleration);
	void SetAttack(const float& attack);
	void SetDirectionAngle(const float& angle);
	void SetCrossEnable(bool enable);

	//========================
	// getter
	//========================
	float GetMoveSpeed() const;
	float GetMoveAcceleration() const;
	float GetAttack() const;
	float GetDirectionAngle() const;
	bool IsCross() const;

protected:
	//========================
	// 更新子弹轨迹,纯虚函数
	//========================
	virtual void TrackUpdate(const float& delta) = 0;

	Bullet()
	: _moveSpeed(0)
	, _moveAcceleration(0)
	, _attack(0)
	, _directionAngle(0)
	, _bCross(false)
	{}

	Bullet(
		const float& moveSpeed,
		const float& moveAcceleration,
		const float& attack,
		const float& directionAngle,
		const bool bCross)
	: _moveSpeed(moveSpeed)
	, _moveAcceleration(moveAcceleration)
	, _attack(attack)
	, _directionAngle(directionAngle)
	, _bCross(bCross)
	{}

private:
	Bullet(Bullet&);
	Bullet& operator=(Bullet&);

private:
	float _moveSpeed; // 移动速度
	float _moveAcceleration; // 移动加速度
	float _attack; // 攻击力
	float _directionAngle; // 方向角度
	bool _bCross; // 是否穿透
};

#endif