#include "StageManager.h"
#include "LuaManager.h"
#include "Enemy.h"
#include "GameMap.h"
#include "GameCommon.h"
#include "Effect.h"

USING_NS_F2D

static StageManager* pInstance = 0;

StageManager* StageManager::getInstance()
{
	if (pInstance == 0)
	{
		pInstance = new StageManager();
	}

	return pInstance;
}

void StageManager::startUp(const string& stagePath, Frame2D::Scene* scene)
{
	LuaManager* luaMgr = LuaManager::getInstance();
	luaMgr->open(stagePath.c_str());

	int num = (int)luaMgr->getNumber("num");

	for (int i=0; i<num; ++i)
	{
		StageInfo* info = new StageInfo();
		info->type = (int)luaMgr->getTableNumber("data", 1 + 7 * i);
		info->name = luaMgr->getTableString("data", 2 + 7 * i);
		info->showTime = (float)luaMgr->getTableNumber("data", 3 + 7 * i);
		info->positionX = (float)luaMgr->getTableNumber("data", 4 + 7 * i);
		info->positionY = (float)luaMgr->getTableNumber("data", 5 + 7 * i);
		info->directionAngle = (float)luaMgr->getTableNumber("data", 6 + 7 * i);
		info->mapScrollSpeed = (float)luaMgr->getTableNumber("data", 7 + 7 * i);
		m_info_list.push_back(info);
	}

	string mapPath = luaMgr->getString("mapPath");

	_musicPath = luaMgr->getString("musicPath");
	_bossBgmPath = luaMgr->getString("bossBgmPath");

	luaMgr->close();

	_scene = scene;

	AudioManager::getInstance()->loadSoundForCache(_musicPath);
	AudioManager::getInstance()->loadSoundForCache(_bossBgmPath);
	TextureCache::getInstance()->LoadTextureFromFile(mapPath);

	// 装载地图
	_map = GameMap::Create(mapPath, LAYER_BACKGROUND_1);
	_map->SetScrollSpeed(1);
	_scene->Add(_map);

	// 如果有正在播放的停止
	AudioManager::getInstance()->stopSoundEffect();
	AudioManager::getInstance()->stopBGM();

	// 播放bgm
	AudioManager::getInstance()->playBGM(_musicPath, SoundVolumeChange::Create(2, 1), 0);
}

void StageManager::Update(const float& delta)
{
	vector<StageInfo*>::iterator ite = m_info_list.begin();

	while (ite != m_info_list.end())
	{
		(*ite)->showTime -= delta;
		
		if ((*ite)->showTime <= 0)
		{
			if ((*ite)->type == 0)
			{
				Enemy* enemy = Enemy::Create((*ite)->name);
				enemy->SetPosition((*ite)->positionX, (*ite)->positionY);
				enemy->SetDirectionAngle((*ite)->directionAngle);
				_scene->Add(enemy);
				AudioManager::getInstance()->playSoundEffect("Sound/se/fly.ogg", 0.5);
			}
			else if ((*ite)->type == 1)
			{
				// caption
				Effect* effect = Effect::Create((*ite)->name);
				effect->SetPosition((*ite)->positionX, (*ite)->positionY);
				effect->SetAngleZ((*ite)->directionAngle);
				_scene->Add(effect, LAYER_UI_1);
			}
			else if ((*ite)->type == 100)
			{
				// caption
				Effect* effect = Effect::Create((*ite)->name);
				effect->SetPosition((*ite)->positionX, (*ite)->positionY);
				effect->SetAngleZ((*ite)->directionAngle);
				_scene->Add(effect, LAYER_UI_1);
				AudioManager::getInstance()->playSoundEffect("Sound/se/se_warning.ogg", 1, 1);
				AudioManager::getInstance()->stopBGM();
				AudioManager::getInstance()->playBGM(_bossBgmPath, SoundDelay::Create(2));
			}

			_map->SetScrollSpeed((*ite)->mapScrollSpeed);

			ite = m_info_list.erase(ite);
		}
		else
		{
			++ite;
		}
	}
}

void StageManager::shutDown()
{
	Clear();

	AudioManager::getInstance()->ClearCache();

	delete this;

	pInstance = 0;
}

void StageManager::Clear()
{
	vector<StageInfo*>::iterator ite = m_info_list.begin();

	while (ite != m_info_list.end())
	{
		delete (*ite);
		ite = m_info_list.erase(ite);
	}
}
