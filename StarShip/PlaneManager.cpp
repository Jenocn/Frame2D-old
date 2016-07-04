#include "PlaneManager.h"
#include "LuaManager.h"
#include <vector>
#include <Frame2D.h>

USING_NS_F2D

static PlaneManager* pInstance = 0;

PlaneManager* PlaneManager::getInstance()
{
	if (pInstance == 0)
	{
		pInstance = new PlaneManager();
	}

	return pInstance;
}

void PlaneManager::startUp(const string& path)
{
	LuaManager* luaMgr = LuaManager::getInstance();

	// 读取配置文件路径
	luaMgr->open(path.c_str());
	int enemyNums = (int)luaMgr->getNumber("enemyNums");
	vector<string> enemy_config;
	for (int i=1; i<=enemyNums; ++i)
	{
		enemy_config.push_back(luaMgr->getTableString("enemyPath", i));
	}

	int ownNums = (int)luaMgr->getNumber("ownNums");
	vector<string> own_config;
	for (int i=1; i<=ownNums; ++i)
	{
		own_config.push_back(luaMgr->getTableString("ownPath", i));
	}
	luaMgr->close();

	// 从对应路径读取敌人属性数据
	for (int i=0; i<enemyNums; ++i)
	{
		luaMgr->open(enemy_config.at(i).c_str());

		string key = luaMgr->getString("name");
		EnemyInfo* info = new EnemyInfo();

		info->imgPath = luaMgr->getString("imgPath");
		TextureCache::getInstance()->LoadTextureFromFile(info->imgPath);
		info->bulletType = (int)luaMgr->getNumber("bulletType");
		info->hpMax = (float)luaMgr->getNumber("hpMax");
		info->duration = (float)luaMgr->getNumber("duration");
		info->stayTime = (float)luaMgr->getNumber("stayTime");
		info->moveSpeed = (float)luaMgr->getNumber("moveSpeed");
		info->score = (int)luaMgr->getNumber("score");
		info->itemID = (int)luaMgr->getNumber("itemID");
		info->layer = (int)luaMgr->getNumber("layer");
		info->moveStateID = (int)luaMgr->getNumber("moveStateID");

		m_enemyInfo_list.insert(pair<string, EnemyInfo*>(key, info));

		luaMgr->close();
	}

	// 从对应路径读取主角属性数据
	for (int i=0; i<ownNums; ++i)
	{
		luaMgr->open(own_config.at(i).c_str());

		string key = luaMgr->getString("name");
		OwnInfo* info = new OwnInfo();
		info->imgPath = luaMgr->getString("imgPath");
		TextureCache::getInstance()->LoadTextureFromFile(info->imgPath);
		info->bulletType = (int)luaMgr->getNumber("bulletType");
		info->hpMax = (float)luaMgr->getNumber("hpMax");
		info->moveSpeed = (float)luaMgr->getNumber("moveSpeed");
		info->bulletLevelMax = (float)luaMgr->getNumber("bulletLevelMax");
		info->missileLevelMax = (float)luaMgr->getNumber("missileLevelMax");
		m_ownInfo_list.insert(pair<string, OwnInfo*>(key, info));

		luaMgr->close();
	}
}

void PlaneManager::shutDown()
{
	Clear();

	delete this;

	pInstance = 0;
}

EnemyInfo* PlaneManager::GetEnemyInfo(const string& key) const
{
	map<string, EnemyInfo*>::const_iterator ite = m_enemyInfo_list.find(key);
	if (ite != m_enemyInfo_list.end())
	{
		return ite->second;
	}

	return 0;
}

OwnInfo* PlaneManager::GetOwnInfo(const string& key) const
{
	map<string, OwnInfo*>::const_iterator ite = m_ownInfo_list.find(key);
	if (ite != m_ownInfo_list.end())
	{
		return ite->second;
	}

	return 0;
}

void PlaneManager::Clear()
{
	map<string, EnemyInfo*>::iterator eite = m_enemyInfo_list.begin();
	while (eite != m_enemyInfo_list.end())
	{
		delete eite->second;
		eite = m_enemyInfo_list.erase(eite);
	}

	map<string, OwnInfo*>::iterator oite = m_ownInfo_list.begin();
	while (oite != m_ownInfo_list.end())
	{
		delete oite->second;
		oite = m_ownInfo_list.erase(oite);
	}
}

