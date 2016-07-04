#include "BulletRealize.h"
#include "Tools.h"

void BulletOnward::TrackUpdate(const float& delta)
{
}

void BulletCurveCosR::TrackUpdate(const float& delta)
{
	if (_bSave == false)
	{
		_beginAngle = GetDirectionAngle();

		_bSave = true;
	}

	_curveTempAngle += 5;
	if (_curveTempAngle >= 360)
	{
		_curveTempAngle -= 360;
	}

	SetDirectionAngle(_beginAngle - cosf(_curveTempAngle / 180 * D3DX_PI) / D3DX_PI * 180);
}

void BulletCurveCosL::TrackUpdate(const float& delta)
{
	if (_bSave == false)
	{
		_beginAngle = GetDirectionAngle();

		_bSave = true;
	}

	_curveTempAngle += 5;
	if (_curveTempAngle >= 360)
	{
		_curveTempAngle -= 360;
	}

	SetDirectionAngle(_beginAngle + cosf(_curveTempAngle / 180 * D3DX_PI) / D3DX_PI * 180);
}

void BulletMissile::TrackUpdate(const float& delta)
{
	if (_bSave == false)
	{
		_beginMoveSpeed = GetMoveSpeed();
		_bSave = true;
	}

	if (_stopTime > 0)
	{
		_stopTime -= delta;
		SetMoveSpeed(-_beginMoveSpeed);

		if (_stopTime <= 0)
		{
			SetMoveSpeed(_beginMoveSpeed);
		}
	}
}

void BulletDisperse::TrackUpdate(const float& delta)
{
	if (_stopTime > 0)
	{
		_stopTime -= delta;

		if (_stopTime <= 0)
		{
			SetVisible(false);

			Bullet* bullet1 = BulletOnward::Create(GetName());
			Bullet* bullet2 = BulletOnward::Create(GetName());
			Bullet* bullet3 = BulletOnward::Create(GetName());
			Bullet* bullet4 = BulletOnward::Create(GetName());

			bullet1->SetPosition(GetPositionX() - rand() % 20, GetPositionY(), GetPositionZ());
			bullet2->SetPosition(GetPositionX() - rand() % 20, GetPositionY(), GetPositionZ());
			bullet3->SetPosition(GetPositionX() + rand() % 20, GetPositionY(), GetPositionZ());
			bullet4->SetPosition(GetPositionX() + rand() % 20, GetPositionY(), GetPositionZ());

			bullet1->SetDirectionAngle(GetDirectionAngle() + rand() % 35);
			bullet2->SetDirectionAngle(GetDirectionAngle() + rand() % 35);
			bullet3->SetDirectionAngle(GetDirectionAngle() -rand() % 35);
			bullet4->SetDirectionAngle(GetDirectionAngle() -rand() % 35);

			GetScene()->Add(bullet1, GetOrder());
			GetScene()->Add(bullet2, GetOrder());
			GetScene()->Add(bullet3, GetOrder());
			GetScene()->Add(bullet4, GetOrder());
		}
	}
}

void BulletFollow::TrackUpdate(const float& delta)
{
	if (_prepareTime > 0)
	{
		_prepareTime -= delta;
		return;
	}

	// 一直找目标
	if (_waitTime > 0)
	{
		_waitTime -= delta;
		
		if (_target == 0)
		{
			// 如果找到目标,那么锁定目标
			vector<Element*> list = GetScene()->GetElementList();

			for (int i = 0; i < list.size(); ++i)
			{
				Element* e = list.at(i);

				if (GetOrder() == LAYER_PLAYER_BULLET)
				{
					if (e->GetOrder() >= LAYER_ENEMY_1 &&
						e->GetOrder() <= LAYER_ENEMY_3)
					{
						_target = e;
						break;
					}
				}
				else
				{
					if (e->GetOrder() == LAYER_PLAYER)
					{
						_target = e;
						break;
					}
				}
			}

			if (_target != 0)
			{
				_waitTime = 0;
			}
		}
	}

	// 跟随目标
	if (_followTime > 0 && _target != 0)
	{
		_followTime -= delta;

		// 如果这个目标还存在,那么跟随
		vector<Element*> list = GetScene()->GetElementList();
		bool flag = false;
		for (int i = 0; i < list.size(); ++i)
		{
			if (_target == list.at(i))
			{
				float bx = GetPositionX() + (0.5f - GetAnchorX()) * GetWidth();
				float by = GetPositionY() + (0.5f - GetAnchorY()) * GetHeight();

				float px = _target->GetPositionX() + (0.5f - _target->GetAnchorX()) * _target->GetWidth();
				float py = _target->GetPositionY() + (0.5f - _target->GetAnchorY()) * _target->GetHeight();

				float tempX = px - bx;
				float tempY = py - by;

				float angle = atan2f(tempY, tempX) / D3DX_PI * 180 - 90;

				SetDirectionAngle(angle);

				flag = true;

				break;
			}
		}

		if (flag == false || _followTime <= 0)
		{
			_target = 0;
		}
	}
}

void BulletRebound::Die()
{
	Bullet::Die();

	if (_target != 0)
	{
		--_count;
		_target = 0;
		_followTime = 0;

		if (_count != 0)
		{
			Bullet* bullet = new BulletRebound(_count);
			bullet->InitData(GetName());
			bullet->SetDirectionAngle(GetDirectionAngle());
			bullet->SetPosition(GetPositionX(), GetPositionY(), GetPositionZ());
			GetScene()->Add(bullet, GetOrder());
		}
	}
}

void BulletRebound::TrackUpdate(const float& delta)
{
	BulletFollow::TrackUpdate(delta);
}

void BulletReboundOnward::Die()
{
	Bullet::Die();

	if (_count != 0)
	{
		Bullet* bullet = BulletRebound::Create(GetName());
		bullet->SetDirectionAngle(GetDirectionAngle());
		bullet->SetPosition(GetPositionX(), GetPositionY(), GetPositionZ());
		GetScene()->Add(bullet, GetOrder());
	}
}

void BulletReboundOnward::TrackUpdate(const float& delta)
{
	BulletOnward::TrackUpdate(delta);
}

void BulletLockBeginPosition::TrackUpdate(const float& delta)
{
	if (_bLock == false)
	{
		// 如果找到目标,那么锁定目标
		vector<Element*> list = GetScene()->GetElementList();

		for (int i = 0; i < list.size(); ++i)
		{
			Element* e = list.at(i);

			if (GetOrder() == LAYER_PLAYER_BULLET)
			{
				if (e->GetOrder() >= LAYER_ENEMY_1 &&
					e->GetOrder() <= LAYER_ENEMY_3)
				{
					_positionX = e->GetPositionX() + (0.5f - e->GetAnchorX()) * e->GetWidth();
					_positionY = e->GetPositionY() + (0.5f - e->GetAnchorY()) * e->GetHeight();
					_bLock = true;
					break;
				}
			}
			else
			{
				if (e->GetOrder() == LAYER_PLAYER)
				{
					_positionX = e->GetPositionX() + (0.5f - e->GetAnchorX()) * e->GetWidth();
					_positionY = e->GetPositionY() + (0.5f - e->GetAnchorY()) * e->GetHeight();
					_bLock = true;
					break;
				}
			}
		}
	}

	if (_bSet == false && _bLock == true)
	{
		float bx = GetPositionX() + (0.5f - GetAnchorX()) * GetWidth();
		float by = GetPositionY() + (0.5f - GetAnchorY()) * GetHeight();

		float tempX = _positionX - bx;
		float tempY = _positionY - by;

		float angle = atan2f(tempY, tempX) / D3DX_PI * 180 - 90;

		SetDirectionAngle(angle);

		_bSet = true;
	}
}