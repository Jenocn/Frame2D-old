#include "Bullet.h"
#include "BulletManager.h"
#include "Tools.h"

USING_NS_F2D

Bullet::~Bullet()
{

}

void Bullet::Die()
{
	if (false == IsCross())
	{
		SetVisible(false);
	}
}

bool Bullet::InitData(const string& name)
{
	BulletInfo* info = BulletManager::getInstance()->GetBulletInfo(name);
	SetName(name);
	_moveSpeed = info->moveSpeed;
	_moveAcceleration = info->moveAcceleration;
	_attack = info->attack;
	_bCross = info->bCross;
	if (InitWithFile(info->imgPath))
	{
		SetTextureBlend(info->bTextureBlend);
		return true;
	}

	return false;
}

void Bullet::Update(const float& delta)
{
	Sprite::Update(delta);

	// 保存上一次坐标
	float tempX = GetPositionX();
	float tempY = GetPositionY();

	// 执行扩展的轨迹
	TrackUpdate(delta);

	// 加速度计算
	SetMoveSpeed(GetMoveSpeed() + GetMoveAcceleration());
	// 计算x轴和y轴的分速度
	float angle = GetDirectionAngle() / 180.0f * D3DX_PI - D3DX_PI / 2.0f;
	SetPositionX(GetPositionX() - cosf(angle) * GetMoveSpeed());
	SetPositionY(GetPositionY() - sinf(angle) * GetMoveSpeed());
	// 计算轨迹前后的z轴角度
	float destAngle = atan2f(GetPositionY() - tempY, GetPositionX() - tempX) / D3DX_PI * 180 - 90;
	
	if (GetMoveSpeed() > 0)
	{
		SetAngleZ(destAngle);
	}
}

void Bullet::SetMoveSpeed(const float& moveSpeed)
{
	_moveSpeed = moveSpeed;
}

void Bullet::SetMoveAcceleration(const float& acceleration)
{
	_moveAcceleration = acceleration;
}

void Bullet::SetAttack(const float& attack)
{
	_attack = attack;
}

void Bullet::SetDirectionAngle(const float& angle)
{
	_directionAngle = angle;
}

void Bullet::SetCrossEnable(bool enable)
{
	_bCross = enable;
}

float Bullet::GetMoveSpeed() const
{
	return _moveSpeed;
}

float Bullet::GetMoveAcceleration() const
{
	return _moveAcceleration;
}

float Bullet::GetAttack() const
{
	return _attack;
}

float Bullet::GetDirectionAngle() const
{
	return _directionAngle;
}

bool Bullet::IsCross() const
{
	return _bCross;
}
