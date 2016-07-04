#include "BulletLauncher.h"
#include <Frame2D.h>
#include "Plane.h"

// 子弹的实现头文件
#include "BulletRealize.h"

USING_NS_F2D

bool BulletLauncher::InitData(
	const Plane* plane,
	const string& bulletName,
	const float& offsetX,
	const float& offsetY,
	const float& offsetAngle,
	const float& shootInterval)
{
	_belongPlane = plane;
	_bulletName = bulletName;
	_offsetX = offsetX;
	_offsetY = offsetY;
	_offsetAngle = offsetAngle;
	_shootInterval = shootInterval;
	_shootIntervalTemp = _shootInterval;

	if (_belongPlane)
	{
		return true;
	}

	if (_bulletName.compare(""))
	{
		return true;
	}

	return false;
}

void BulletLauncher::Update(const float& delta)
{
	Element::Update(delta);

	// 根据飞机的旋转角度求出发射器的目标坐标
	float r = sqrt(_offsetX * _offsetX + _offsetY * _offsetY);
	float angle = _belongPlane->GetAngleZ() / 180.0f * D3DX_PI + atan2f(_offsetY, _offsetX);
	float destX = r * cosf(angle);
	float destY = r * sinf(angle);

	// 更新位置
	SetPosition(
		_belongPlane->GetPositionX() + destX,
		_belongPlane->GetPositionY() + destY,
		_belongPlane->GetPositionZ());

	// 更新角度
	SetAngleZ(_belongPlane->GetAngleZ() + _offsetAngle);

	if (true == _bRotate)
	{
		SetOffsetAngle(GetOffsetAngle() + _rotateValue);
	}

	// 如果发射间隔为0,那么不需要计算,直接标记可以发射
	if (_shootInterval <= 0)
	{
		_bShoot = true;
		return;
	}

	// 如果标记为可以发射子弹那么直接返回,只有不能发射的状态才计算时间
	if (_bShoot)
	{
		return;
	}

	// 临时变量加上每帧的间隔时间
	_shootIntervalTemp += delta;

	// 如果达到时间间隔那么可以发射子弹
	if (_shootIntervalTemp >= _shootInterval)
	{
		// 标记可以发射子弹
		_bShoot = true;

		// 让临时变量减去发射间隔的时间		
		_shootIntervalTemp = _shootIntervalTemp - _shootInterval;

		/*
		这里为了优化一种情况,如果减掉发射间隔仍然比间隔时间还要大
		那么进入这个循环,减掉这个时间,直到比间隔时间小为止,确保不
		会出现越来越满的堆积情况
		*/
		while (_shootIntervalTemp >= _shootInterval)
		{
			_shootIntervalTemp = _shootIntervalTemp - _shootInterval;
		}
	}
}

bool BulletLauncher::Shoot()
{
	// 如果标记可以射击才会发射出子弹
	if (_bShoot)
	{
		Bullet* bullet = CreateBullet();
		bullet->SetPosition(
			GetPositionX(),
			GetPositionY(),
			GetPositionZ());
		bullet->SetAngleZ(GetAngleZ());
		bullet->SetDirectionAngle(GetAngleZ());
		bullet->SetOrder(GetOrder());
		_belongPlane->GetScene()->Add(bullet);
		// 发射过了,标记为不可发射
		_bShoot = false;

		return true;
	}

	return false;
}

void BulletLauncher::SetOffsetPosition(
	const float& positionX,
	const float& positionY)
{
	SetOffsetPositionX(positionX);
	SetOffsetPositionY(positionY);
}

void BulletLauncher::SetOffsetPositionX(const float& positionX)
{
	_offsetX = positionX;
}

void BulletLauncher::SetOffsetPositionY(const float& positionY)
{
	_offsetY = positionY;
}

void BulletLauncher::SetOffsetAngle(const float& angle)
{
	_offsetAngle = angle;
}

void BulletLauncher::SetShootInterval(const float& interval)
{
	_shootInterval = interval;

	if (_shootInterval < 0)
	{
		_shootInterval = 0;
	}
}

void BulletLauncher::SetRotateValue(const float& value)
{
	_rotateValue = value;
}

void BulletLauncher::SetRotateEnable(bool enable)
{
	_bRotate = enable;
}

float BulletLauncher::GetOffsetPositionX() const
{
	return _offsetX;
}

float BulletLauncher::GetOffsetPositionY() const
{
	return _offsetY;
}

float BulletLauncher::GetOffsetAngle() const
{
	return _offsetAngle;
}

float BulletLauncher::GetShootInterval() const
{
	return _shootInterval;
}

float BulletLauncher::GetRotateValue() const
{
	return _rotateValue;
}

bool BulletLauncher::IsRotate() const
{
	return _bRotate;
}
