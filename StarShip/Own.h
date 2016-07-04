#ifndef _OWN_H_H_
#define _OWN_H_H_

#include "Plane.h"

class Item;

class Own : public Plane
{
public:
	static Own* Create(
		const string& path,
		const float& hpMax,
		const float& moveSpeed,
		const float& directionAngle,
		const int& bulletType,
		const int& bulletLevelMax,
		const int& missileType,
		const int& missileLevelMax);

	static Own* Create(const string& path);

	virtual ~Own();

	virtual bool InitData();

	virtual bool Attack();

	virtual bool MissileShoot();

	virtual void Move();

	virtual void Die();

	virtual void Update(const float& delta);

	void UseItem(const Item* item);

	// setter
	void SetBulletType(const int& type);
	void SetBulletLevel(const int& level);
	void SetBulletLevelMax(const int& levelMax);
	void SetMissileType(const int& type);
	void SetMissileLevel(const int& level);
	void SetMissileLevelMax(const int& levelMax);
	void SetShootEnable(bool enable);

	// getter
	int GetBulletType() const;
	int GetBulletLevel() const;
	int GetBulletLevelMax() const;
	int GetMissileType() const;
	int GetMissileLevel() const;
	int GetMissileLevelMax() const;
	bool IsShoot() const;

protected:
	//=======================
	// 切换子弹类型,
	// 并根据类型添加或删除对应发射器
	//=======================
	void ChangeBulletType();

	//=======================
	// 切换导弹类型,
	// 并根据类型添加或删除对应发射器
	//=======================
	void ChangeMissileType();
	
	Own()
	: _bulletType(1)
	, _bulletLevel(1)
	, _bulletLevelMax(1)
	, _missileType(1)
	, _missileLevel(1)
	, _missileLevelMax(1)
	, _bShoot(false)
	{}

	Own(
		const float& hp,
		const float& hpMax,
		const float& moveSpeed,
		const float& directionAngle,
		const int& bulletType,
		const int& bulletLevel,
		const int& bulletLevelMax,
		const int& missileType,
		const int& missileLevel,
		const int& missileLevelMax)
	: Plane(hp, hpMax, moveSpeed, directionAngle, false, true)
	, _bulletType(bulletType)
	, _bulletLevel(bulletLevel)
	, _bulletLevelMax(bulletLevelMax)
	, _missileType(missileType)
	, _missileLevel(missileLevel)
	, _missileLevelMax(missileLevelMax)
	, _bShoot(false)
	{}

private:
	Own(Own&);
	Own& operator=(Own&);

private:
	// 导弹类型
	int _missileType;
	// 导弹等级
	int _missileLevel;
	// 导弹等级上限
	int _missileLevelMax;

	// 子弹类型
	int _bulletType;
	// 子弹等级
	int _bulletLevel;
	// 子弹等级上限
	int _bulletLevelMax;

	// 是否可以射击
	bool _bShoot;
};

#endif