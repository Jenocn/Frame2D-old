#include "Enemy.h"
#include "BulletLauncherRealize.h"
#include "PlaneManager.h"
#include "MoveStateRealize.h"
#include "Effect.h"
#include "Item.h"

Enemy::~Enemy()
{
	_state->Release();
}

bool Enemy::InitData(const string& name)
{
	EnemyInfo* info = PlaneManager::getInstance()->GetEnemyInfo(name);
	SetName(name);
	ChangeBulletType(info->bulletType);
	SetHpMax(info->hpMax);
	SetHp(GetHpMax());
	_duration = info->duration;
	_stayTime = info->stayTime;
	SetMoveSpeed(info->moveSpeed);
	_score = info->score;
	_itemID = info->itemID;
	switch (info->layer)
	{
	case 1:
		SetOrder(LAYER_ENEMY_1);
		break;
	case 2:
		SetOrder(LAYER_ENEMY_2);
		break;
	case 3:
		SetOrder(LAYER_ENEMY_3);
		break;
	default:
		SetOrder(LAYER_ENEMY_1);
		break;
	}
	ChangeMoveState(info->moveStateID);
	SetMoveEnable(true);


	if (InitWithFile(info->imgPath))
	{
		return true;
	}

	return false;
}

bool Enemy::Attack()
{
	return Plane::Attack();
}

bool Enemy::MissileShoot()
{
	return Plane::MissileShoot();
}

void Enemy::Move()
{
	Plane::Move();
	SetAngleZ(GetDirectionAngle());
}

void Enemy::Die()
{
	Plane::Die();

	Effect* boom = Effect::Create("boom1");
	boom->SetPosition(GetPositionX(), GetPositionY(), GetPositionZ());
	boom->SetOrder(LAYER_ENEMY_BOOM);
	GetScene()->Add(boom);

	Effect* cool = Effect::Create("cool");
	cool->SetColorRGB(rand() % 128 + 128, rand() % 128 + 128, rand() % 128 + 128);
	cool->ResetVertex();
	cool->SetPosition(GetPositionX() + rand() % 21 - 10, GetPositionY() + rand() % 21 - 10, GetPositionZ());
	cool->RunAction(Frame2D::Move::Create(2.5, GetPositionX() + 50, GetPositionY()));
	cool->SetOrder(LAYER_UI_1);
	GetScene()->Add(cool);

	// 如果有道具那么掉落道具
	if (_itemID != 0)
	{
		Item* item = Item::Create(_itemID);
		item->SetPosition(GetPositionX(), GetPositionY(), GetPositionZ());
		item->SetOrder(LAYER_ITEM);
		GetScene()->Add(item);
		_itemID = 0;
	}
}

void Enemy::Update(const float& delta)
{
	Plane::Update(delta);

	Attack();
	MissileShoot();

	if (_duration > 0)
	{
		_duration -= delta;
		
		_state->Update(delta);
		Move();

		if (_duration < 0)
		{
			_duration = 0;
		}
	}
	else
	{
		if (_stayTime > 0)
		{
			_stayTime -= delta;

			if (_stayTime < 0)
			{
				_stayTime = 0;
			}
		}
		else
		{
			_state->Update(delta);
			Move();
		}
	}
}

void Enemy::ChangeMoveState(const int& stateID)
{
	if (_state != 0)
	{
		_state->Release();
		_state = 0;
	}
	switch (stateID)
	{
	case 1:
		_state = MoveStateOnward::Create(this);
		break;
	case 2:
		_state = MoveStateCircleL::Create(this);
		break;
	case 3:
		_state = MoveStateCircleR::Create(this);
		break;
	case 4:
		_state = MoveStateBack::Create(this);
		break;
	}
}


void Enemy::ChangeBulletType(const int& type)
{
	ClearBulletLauncher();

	switch (type)
	{
	case 1:
	{
			  BulletLauncher* launcher = BulletLauncherOnward::Create(
				  this, "normal_enemy", 0, 0, 0, 1.5);
			  launcher->SetOrder(LAYER_ENEMY_BULLET);
			  AddBulletLauncher(launcher);

			  BulletLauncher* launcher2 = BulletLauncherLockBeginPosition::Create(
				  this, "normal_enemy", 0, 0, 0, 3.5);
			  launcher2->SetOrder(LAYER_ENEMY_BULLET);
			  AddBulletLauncher(launcher2);
	}
		break;
	case 2:
	{
			 BulletLauncher* launcher = BulletLauncherDisperse::Create(
				  this, "normal_enemy", 0, 0, 0, 2);
			  launcher->SetOrder(LAYER_ENEMY_BULLET);
			  AddBulletLauncher(launcher);

			  for (int i = 0; i < 18; i++)
			  {
				  BulletLauncher* launcher = BulletLauncherOnward::Create(
					  this, "fire2", 10, 0, i * 20, 0.6);
				  launcher->SetOrder(LAYER_ENEMY_BULLET);
				  AddMissileLauncher(launcher);
			  }
	}
		break;
	case 3:
	{
			  BulletLauncher* launcher = BulletLauncherLockBeginPosition::Create(
				  this, "normal_enemy", 0, 0, 0, 1);
			  launcher->SetOrder(LAYER_ENEMY_BULLET);
			  AddBulletLauncher(launcher);
	}
		break;
	case 4:
	{
			  for (int i = 0; i < 18; i++)
			  {
				  BulletLauncher* launcher = BulletLauncherCurveCosL::Create(
					  this, "normal_enemy", 10, 0, i * 20, 1.5);
				  launcher->SetOrder(LAYER_ENEMY_BULLET);
				  AddMissileLauncher(launcher);
			  }
	}
		break;
	case 5:
	{
			  BulletLauncher* launcher = BulletLauncherFollow::Create(
				  this, "follow_enemy", -20, 0, 0, 3);
			  launcher->SetOrder(LAYER_ENEMY_BULLET);
			  AddMissileLauncher(launcher);

			  launcher = BulletLauncherFollow::Create(
				  this, "follow_enemy", 20, 0, 0, 3);
			  launcher->SetOrder(LAYER_ENEMY_BULLET);
			  AddMissileLauncher(launcher);
			  
	}
		break;
	case 100:
	{
				for (int i = 0; i < 10; i++)
				{
					BulletLauncher* launcher = BulletLauncherLockBeginPosition::Create(
						this, "fire2", i * 20 - (10 - 1) / 2.0f * 20, 0, 0, 5);
					launcher->SetOrder(LAYER_ENEMY_BULLET);
					AddBulletLauncher(launcher);
				}

				for (int i = 0; i < 2; i++)
				{
					BulletLauncher* launcher = BulletLauncherDisperse::Create(
						this, "normal_enemy", i * 60 - (3 - 1) / 2.0f * 60, 0, 0, 3.5);
					launcher->SetOrder(LAYER_ENEMY_BULLET);
					AddMissileLauncher(launcher);
				}

				for (int i = 0; i < 2; i++)
				{
					BulletLauncher* launcher = BulletLauncherDisperse::Create(
						this, "normal_enemy", i * 60 - (3 - 1) / 2.0f * 60, 20, 0, 3.5);
					launcher->SetOrder(LAYER_ENEMY_BULLET);
					AddMissileLauncher(launcher);
				}

				for (int i = 0; i < 36; i++)
				{
					BulletLauncher* launcher = BulletLauncherOnward::Create(
						this, "fire2", 10, 5, i * 10, 6);
					launcher->SetOrder(LAYER_ENEMY_BULLET);
					AddMissileLauncher(launcher);
				}

				for (int i = 0; i < 36; i++)
				{
					BulletLauncher* launcher = BulletLauncherOnward::Create(
						this, "fire2", 0, 10, i * 10, 6);
					launcher->SetOrder(LAYER_ENEMY_BULLET);
					AddMissileLauncher(launcher);
				}

				for (int i = 0; i < 36; i++)
				{
					BulletLauncher* launcher = BulletLauncherOnward::Create(
						this, "fire2", -10, 0, i * 10, 6);
					launcher->SetOrder(LAYER_ENEMY_BULLET);
					AddMissileLauncher(launcher);
				}

				for (int i = 0; i < 20; i++)
				{
					BulletLauncher* launcher = BulletLauncherLockBeginPosition::Create(
						this, "missile1", i * 10 - (20 - 1) / 2.0f * 10, 0, 0, i * 0.05 + 60);
					launcher->SetOrder(LAYER_ENEMY_BULLET);
					AddBulletLauncher(launcher);
				}
	}
		break;
	}

}

void Enemy::SetDuration(const float& duration)
{
	_duration = duration;
}

void Enemy::SetStayTime(const float& stayTime)
{
	_stayTime = stayTime;
}

void Enemy::SetScore(const int& score)
{
	_score = score;
}

void Enemy::SetItemID(const int& itemID)
{
	_itemID = itemID;
}

float Enemy::GetDuration() const
{
	return _duration;
}

float Enemy::GetStayTime() const
{
	return _stayTime;
}

int Enemy::GetScore() const
{
	return _score;
}

int Enemy::GetItemID() const
{
	return _itemID;
}

