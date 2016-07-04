#include "Plane.h"
#include "BulletLauncher.h"
#include "Bomb.h"

USING_NS_F2D

Plane* Plane::Create()
{
	Plane* plane = new (nothrow) Plane();

	if (plane)
	{
		return plane;
	}

	return 0;
}

Plane* Plane::Create(
	const float& hpMax,
	const float& moveSpeed,
	const float& directionAngle,
	bool bMove, bool bGod)
{
	Plane* plane = new (nothrow) Plane(
		hpMax, hpMax, moveSpeed, directionAngle, bMove, bGod);

	if (plane)
	{
		return plane;
	}

	return 0;
}

Plane::~Plane()
{
	ClearBulletLauncher();
}

bool Plane::Attack()
{
	bool flag = false;

	for (int i = 0; i < m_bulletLaunch_list.size(); ++i)
	{
		if (m_bulletLaunch_list.at(i)->Shoot())
		{
			if (flag == false)
			{
				flag = true;
			}
		}
	}

	return flag;
}

bool Plane::MissileShoot()
{
	bool flag = false;

	for (int i = 0; i < m_missileLaunch_list.size(); ++i)
	{
		if (m_missileLaunch_list.at(i)->Shoot())
		{
			if (flag == false)
			{
				flag = true;
			}
		}
	}

	return flag;
}

void Plane::Move()
{
	// 如果移动状态则移动
	if (_bMove)
	{
		float angle = _directionAngle / 180.0f * D3DX_PI - D3DX_PI / 2.0f;
		SetPositionX(GetPositionX() - cosf(angle) * _moveSpeed);
		SetPositionY(GetPositionY() - sinf(angle) * _moveSpeed);

		while (_directionAngle > 360)
		{
			_directionAngle -= 360;
		}

		while (_directionAngle < 0)
		{
			_directionAngle += 360;
		}
	}
}

void Plane::Die()
{
	SetVisible(false);

	AudioManager::getInstance()->playSoundEffect("Sound/se/boom.mp3", 0.2);
}

void Plane::Update(const float& delta)
{
	Sprite::Update(delta);

	// 被攻击时机体变色
	{
		if (_bBruiseTemp == true)
		{
			SetColorRGB(255, 255, 255);
			ResetVertex();
			_bBruiseTemp = false;
		}
		if (_bBruise == true)
		{
			SetColorRGB(255, 64, 64);
			ResetVertex();
			_bBruise = false;
			_bBruiseTemp = true;
		}
	}

	for (int i=0; i<m_bulletLaunch_list.size(); ++i)
	{
		// 更新数据
		m_bulletLaunch_list.at(i)->Update(delta);
	}

	for (int i=0; i<m_missileLaunch_list.size(); ++i)
	{
		// 更新数据
		m_missileLaunch_list.at(i)->Update(delta);
	}
}

bool Plane::UseBomb()
{
	if (m_bomb_list.size() > 0)
	{
		m_bomb_list.at(0)->Use();
		RemoveBomb(m_bomb_list.at(0));

		return true;
	}

	return false;
}

void Plane::AddBomb(Bomb* bomb)
{
	m_bomb_list.push_back(bomb);
}

void Plane::RemoveBomb(Bomb* bomb)
{
	vector<Bomb*>::iterator ite = m_bomb_list.begin();

	while (ite != m_bomb_list.end())
	{
		if ((*ite) == bomb)
		{
			(*ite)->Release();
			m_bomb_list.erase(ite);
			return;
		}

		++ite;
	}
}

vector<Bomb*> Plane::GetBombList() const
{
	return m_bomb_list;
}

void Plane::ClearBomb()
{
	vector<Bomb*>::iterator ite = m_bomb_list.begin();

	while (ite != m_bomb_list.end())
	{
		(*ite)->Release();
		ite = m_bomb_list.erase(ite);
	}
}

void Plane::AddBulletLauncher(BulletLauncher* launcher)
{
	m_bulletLaunch_list.push_back(launcher);
}

void Plane::RemoveBulletLauncher(BulletLauncher* launcher)
{
	vector<BulletLauncher*>::iterator ite = m_bulletLaunch_list.begin();
	while (ite != m_bulletLaunch_list.end())
	{
		if ((*ite) == launcher)
		{
			(*ite)->Release();
			m_bulletLaunch_list.erase(ite);
			break;
		}

		++ite;
	}
}

void Plane::ClearBulletLauncher()
{
	vector<BulletLauncher*>::iterator ite = m_bulletLaunch_list.begin();
	while (ite != m_bulletLaunch_list.end())
	{
		(*ite)->Release();
		ite = m_bulletLaunch_list.erase(ite);
	}
}

vector<BulletLauncher*> Plane::GetBulletLauncherList() const
{
	return m_bulletLaunch_list;
}

void Plane::AddMissileLauncher(BulletLauncher* launcher)
{
	m_missileLaunch_list.push_back(launcher);
}

void Plane::RemoveMissileLauncher(BulletLauncher* launcher)
{
	vector<BulletLauncher*>::iterator ite = m_missileLaunch_list.begin();
	while (ite != m_missileLaunch_list.end())
	{
		if ((*ite) == launcher)
		{
			(*ite)->Release();
			m_missileLaunch_list.erase(ite);
			break;
		}

		++ite;
	}
}

void Plane::ClearMissileLauncher()
{
	vector<BulletLauncher*>::iterator ite = m_missileLaunch_list.begin();
	while (ite != m_missileLaunch_list.end())
	{
		(*ite)->Release();
		ite = m_missileLaunch_list.erase(ite);
	}
}

vector<BulletLauncher*> Plane::GetMissileLauncherList() const
{
	return m_missileLaunch_list;
}

void Plane::SetHp(const float& hp)
{
	_hp = hp;
	if (_hp > _hpMax)
	{
		_hp = _hpMax;
	}
	if (_hp < 0)
	{
		_hp = 0;
	}
}

void Plane::SetHpMax(const float& hpMax)
{
	_hpMax = hpMax;
	if (_hpMax < 0)
	{
		_hpMax = 0;
	}
}

void Plane::SetMoveSpeed(const float& moveSpeed)
{
	_moveSpeed = moveSpeed;
}

void Plane::SetDirectionAngle(const float& directionAngle)
{
	_directionAngle = directionAngle;
}

void Plane::SetMoveEnable(bool enable)
{
	_bMove = enable;
}

void Plane::SetGodEnable(bool enable)
{
	_bGod = enable;
}

void Plane::SetBruiseEnable(bool enable)
{
	_bBruise = enable;
}

float Plane::GetHp() const
{
	return _hp;
}

float Plane::GetHpMax() const
{
	return _hpMax;
}

float Plane::GetMoveSpeed() const
{
	return _moveSpeed;
}

float Plane::GetDirectionAngle() const
{
	return _directionAngle;
}

bool Plane::IsMove() const
{
	return _bMove;
}

bool Plane::IsGod() const
{
	return _bGod;
}

bool Plane::IsBruiseEnable() const
{
	return _bBruise;
}
