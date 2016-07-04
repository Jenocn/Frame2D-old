#ifndef _BULLET_LAUNCHER_H_H_
#define _BULLET_LAUNCHER_H_H_

#include <Frame2D.h>
#include "GameCommon.h"

class Plane;
class Bullet;

//=====================
// 创建自身对象
// 参数1:绑定的飞机
// 参数2:子弹名称
// 参数3:偏移坐标X
// 参数4:偏移坐标Y
// 参数5:偏移角度
// 参数6:发射时间间隔
//=====================
#define BULLETLAUNCHER_CREATEFUNC(__TYPE__) \
	static __TYPE__* Create(\
	const Plane* plane, \
	const string& bulletName, \
	const float& offsetX, \
	const float& offsetY, \
	const float& offsetAngle, \
	const float& shootInterval) \
	{ \
		__TYPE__* pRet = new (nothrow)__TYPE__(); \
		if (pRet && pRet->InitData(plane, bulletName, \
				offsetX, offsetY, offsetAngle, shootInterval)) \
		{ \
			return pRet; \
		} \
		return 0; \
	}

//=====================
// 子弹发射器基类
// 发射器一次只能发射一颗子弹,飞机可以装载N个发射器
//=====================
class BulletLauncher : public Frame2D::Element
{
public:
	//=====================
	// 初始化数据
	//=====================
	bool InitData(
		const Plane* plane,
		const string& bulletName,
		const float& offsetX,
		const float& offsetY,
		const float& offsetAngle,
		const float& shootInterval);

	//=====================
	// 更新数据
	//=====================
	void Update(const float& delta);

	//=====================
	// 发射子弹
	//=====================
	bool Shoot();

	//=====================
	// setter
	//=====================
	void SetOffsetPosition(
		const float& positionX,
		const float& positionY);
	void SetOffsetPositionX(
		const float& positionX);
	void SetOffsetPositionY(
		const float& positionY);
	void SetOffsetAngle(const float& angle);
	void SetShootInterval(const float& interval);
	void SetRotateValue(const float& value);
	void SetRotateEnable(bool enable);

	//=====================
	// getter
	//=====================
	float GetOffsetPositionX() const;
	float GetOffsetPositionY() const;
	float GetOffsetAngle() const;
	float GetShootInterval() const;
	float GetRotateValue() const;
	bool IsRotate() const;

protected:
	virtual Bullet* CreateBullet() = 0;

	BulletLauncher()
	: _belongPlane(0)
	, _bulletName("")
	, _offsetX(0)
	, _offsetY(0)
	, _offsetAngle(0)
	, _shootInterval(0)
	, _shootIntervalTemp(0)
	, _rotateValue(0)
	, _bRotate(false)
	, _bShoot(false)
	{}

	BulletLauncher(
		const Plane* plane,
		const string& bulletName,
		const float& offsetX,
		const float& offsetY,
		const float& offsetAngle,
		const float& shootInterval)
	: _belongPlane(plane)
	, _bulletName(bulletName)
	, _offsetX(offsetX)
	, _offsetY(offsetY)
	, _offsetAngle(offsetAngle)
	, _shootInterval(shootInterval)
	, _shootIntervalTemp(0)
	, _rotateValue(0)
	, _bRotate(false)
	, _bShoot(false)
	{}

private:
	BulletLauncher(BulletLauncher&);
	BulletLauncher& operator=(BulletLauncher&);

protected:
	string _bulletName; // 子弹的名称,即key值

private:
	const Plane* _belongPlane; // 所属飞机(创建时绑定,根据这个来实时设置发射器的坐标,方向)
	// 会根据本身坐标和偏移量以及旋转角度计算出子弹的坐标
	float _offsetX; // x轴偏移量
	float _offsetY; // y轴偏移量
	float _offsetAngle; // z轴旋转角度偏移量
	float _shootInterval; // 发射时间间隔(秒)
	float _shootIntervalTemp; // 用于计算间隔时间的临时变量

	float _rotateValue; // 旋转的量
	bool _bRotate; // 是否旋转

	bool _bShoot; // 是否可以发射
};

#endif