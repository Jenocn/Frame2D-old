#include "Own.h"
#include "BulletLauncherRealize.h"
#include "PlaneManager.h"
#include "Item.h"

USING_NS_F2D

Own* Own::Create(
	const string& path,
	const float& hpMax,
	const float& moveSpeed,
	const float& directionAngle,
	const int& bulletType,
	const int& bulletLevelMax,
	const int& missileType,
	const int& missileLevelMax)
{
	Own* own = new (nothrow) Own(
		hpMax, hpMax, moveSpeed, directionAngle,
		bulletType, 1, bulletLevelMax,
		missileType, 1, missileLevelMax);

	if (own && own->InitWithFile(path) && own->InitData())
	{
		own->SetHpMax(hpMax);
		own->SetHp(own->GetHpMax());
		own->SetBulletLevelMax(bulletLevelMax);
		own->ChangeBulletType();
		own->SetMissileLevelMax(missileLevelMax);
		own->ChangeMissileType();
		own->SetOrder(LAYER_PLAYER);

		return own;
	}

	return 0;
}

Own* Own::Create(const string& path)
{
	OwnInfo* info = PlaneManager::getInstance()->GetOwnInfo(path);

	return Own::Create(info->imgPath, info->hpMax,
		info->moveSpeed, 0, info->bulletType,
		info->bulletLevelMax, 0, info->missileLevelMax);
}

Own::~Own()
{

}

bool Own::InitData()
{
	return true;
}

bool Own::Attack()
{
	return Plane::Attack();
}

bool Own::MissileShoot()
{
	return Plane::MissileShoot();
}

void Own::Move()
{
	Plane::Move();

	if (IsMove())
	{
		if (GetDirectionAngle() > 0 && GetDirectionAngle() < 180 && GetAngleY() < 45)
		{
			SetAngleY(GetAngleY() + GetMoveSpeed());
		}
		else if (GetDirectionAngle() > 180 && GetDirectionAngle() < 360 && GetAngleY() > -45)
		{
			SetAngleY(GetAngleY() - GetMoveSpeed());
		}
	}
}

void Own::Die()
{
	Plane::Die();
}

void Own::Update(const float& delta)
{
	Plane::Update(delta);

	Move();

	if (true == _bShoot)
	{
		if (Attack())
		{
			switch (GetBulletType())
			{
			case 1:
				AudioManager::getInstance()->playSoundEffect("Sound/se/own_shoot1.ogg", 0.4);
				break;
			case 2:
				AudioManager::getInstance()->playSoundEffect("Sound/se/own_shoot2.mp3");
				break;
			case 3:
				AudioManager::getInstance()->playSoundEffect("Sound/se/own_shoot3.ogg");
				break;
			}
		}

		if (MissileShoot())
		{
			AudioManager::getInstance()->playSoundEffect("Sound/se/missile.mp3");
		}
	}

	if (false == IsMove())
	{
		float temp = GetMoveSpeed();
		if (GetAngleY() > 0)
		{
			SetAngleY(GetAngleY() - temp);

			if (GetAngleY() <= 0)
			{
				SetAngleY(0);
			}
		}
		else if (GetAngleY() < 0)
		{
			SetAngleY(GetAngleY() + temp);

			if (GetAngleY() >= 0)
			{
				SetAngleY(0);
			}
		}
	}
}

void Own::UseItem(const Item* item)
{
	int itemID = item->GetID();

	int itemType = itemID / 1000;
	int itemValue = itemID % 1000;

	switch (itemType)
	{
	case 1:
		SetBulletType(itemValue);
		break;
	case 2:
		SetMissileType(itemValue);
		break;
	case 3:
		break;
	case 9:

		break;
	}
}

void Own::ChangeBulletType()
{
	ClearBulletLauncher();

	switch (_bulletType)
	{
	case 1:
		for (int i=0; i<GetBulletLevel(); ++i)
		{
			BulletLauncher* launcher = BulletLauncherOnward::Create(
				this, "normal_p1", i * 12 - (GetBulletLevel() - 1) / 2.0f * 12, 0, 0,
				(GetBulletLevelMax() - GetBulletLevel() + 1) / 10.0f);
			launcher->SetOrder(LAYER_PLAYER_BULLET);
			AddBulletLauncher(launcher);
		}
		break;
	case 2:
		for (int i = 0; i<GetBulletLevel(); ++i)
		{
			BulletLauncher* launcher = BulletLauncherDisperse::Create(
				this, "fire1", i * 5 - (GetBulletLevel() - 1) / 2.0f * 5, 0, 0,
				(GetBulletLevelMax() - GetBulletLevel() + 3) / 10.0f);
			launcher->SetOrder(LAYER_PLAYER_BULLET);
			AddBulletLauncher(launcher);
		}
		break;
	case 3:
		for (int i = 0; i<GetBulletLevel(); ++i)
		{
			BulletLauncher* launcher = BulletLauncherReboundOnward::Create(
				this, "fire3", i * 10 - (GetBulletLevel() - 1) / 2.0f * 10, 0, 0,
				(GetBulletLevelMax() - GetBulletLevel() + 2) / 10.0f);
			launcher->SetOrder(LAYER_PLAYER_BULLET);
			AddBulletLauncher(launcher);
		}
		break;
	}
}

void Own::ChangeMissileType()
{
	ClearMissileLauncher();

	BulletLauncher* launcher = 0;

	switch (_missileType)
	{
	case 1:
		for (int i = 0; i<GetMissileLevel(); ++i)
		{
			launcher = BulletLauncherMissile::Create(
				this, "missile1", i * 15 - (GetMissileLevel() - 1) / 2.0f * 15, 0, 0,
				(GetMissileLevelMax() - GetMissileLevel() + 10) / 10.0f);
			launcher->SetOrder(LAYER_PLAYER_BULLET);
			AddMissileLauncher(launcher);
		}
		break;
	case 2:
		launcher = BulletLauncherFollow::Create(
			this, "missile2", 0, 0, 0, (GetMissileLevelMax() - GetMissileLevel() + 2.5f) / 10.0f);
		launcher->SetOrder(LAYER_PLAYER_BULLET);
		AddMissileLauncher(launcher);
		break;
		
	}
}

//void Own::UseBomb();

//void Own::AddBomb(Bomb* bomb);

//void Own::RemoveBomb(Bomb* bomb);

//vector<Bomb*> Own::GetBombList() const;

//void Own::ClearBomb();

void Own::SetBulletType(const int& type)
{
	if (_bulletType != type)
	{
		_bulletType = type;
		ChangeBulletType();
	}
	else
	{
		SetBulletLevel(GetBulletLevel() + 1);
	}
}

void Own::SetBulletLevel(const int& level)
{
	if (_bulletLevel == level)
	{
		return;
	}

	_bulletLevel = level;

	if (_bulletLevel > _bulletLevelMax)
	{
		_bulletLevel = _bulletLevelMax;
	}

	if (_bulletLevel < 1)
	{
		_bulletLevel = 1;
	}

	if (level <= _bulletLevelMax &&
		level >= 1)
	{
		ChangeBulletType();
	}
}

void Own::SetBulletLevelMax(const int& levelMax)
{
	_bulletLevelMax = levelMax;

	if (_bulletLevelMax < 1)
	{
		_bulletLevelMax = 1;
	}
}

void Own::SetMissileType(const int& type)
{
	if (_missileType != type)
	{
		_missileType = type;
		ChangeMissileType();
	}
	else
	{
		SetMissileLevel(GetMissileLevel() + 1);
	}
}

void Own::SetMissileLevel(const int& level)
{
	if (_missileLevel == level)
	{
		return;
	}

	_missileLevel = level;

	if (_missileLevel > _missileLevelMax)
	{
		_missileLevel = _missileLevelMax;
	}

	if (_missileLevel < 1)
	{
		_missileLevel = 1;
	}

	if (level <= _missileLevelMax &&
		level >= 1)
	{
		ChangeMissileType();
	}
}

void Own::SetMissileLevelMax(const int& levelMax)
{
	_missileLevelMax = levelMax;

	if (_missileLevelMax < 1)
	{
		_missileLevelMax = 1;
	}
}

void Own::SetShootEnable(bool enable)
{
	_bShoot = enable;
}

int Own::GetBulletType() const
{
	return _bulletType;
}

int Own::GetBulletLevel() const
{
	return _bulletLevel;
}

int Own::GetBulletLevelMax() const
{
	return _bulletLevelMax;
}

int Own::GetMissileType() const
{
	return _missileType;
}

int Own::GetMissileLevel() const
{
	return _missileLevel;
}

int Own::GetMissileLevelMax() const
{
	return _missileLevelMax;
}

bool Own::IsShoot() const
{
	return _bShoot;
}
