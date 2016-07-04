#include "UserManager.h"

static UserManager* pInstance = 0;

UserManager* UserManager::getInstance()
{
	if (0 == pInstance)
	{
		pInstance = new UserManager();
	}

	return pInstance;
}

void UserManager::Release()
{
	Clear();

	delete this;

	pInstance = 0;
}

void UserManager::Clear()
{
	_score = 0;
	_stage = 1;
	_life = 0;
	_ownName = "";
}

int UserManager::GetScore() const
{
	return _score;
}

int UserManager::GetStage() const
{
	return _stage;
}

int UserManager::GetStageMax() const
{
	return _stageMax;
}

int UserManager::GetLife() const
{
	return _life;
}


string UserManager::GetOwn() const
{
	return _ownName;
}

void UserManager::SetScore(const int& score)
{
	_score = score;
}

void UserManager::SetStage(const int& stage)
{
	if (_stage <= _stageMax && _stage >= 0)
	{
		_stage = stage;
	}
}

void UserManager::SetStageMax(const int& stageMax)
{
	_stageMax = stageMax;
}

void UserManager::SetLife(const int& life)
{
	_life = life;
}

void UserManager::SetOwn(const string& ownName)
{
	_ownName = ownName;
}

