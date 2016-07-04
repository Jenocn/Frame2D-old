#include "BulletManager.h"
#include "LuaManager.h"
#include <vector>
#include <Frame2D.h>

USING_NS_F2D

static BulletManager* pInstance = 0;

BulletManager* BulletManager::getInstance()
{
	if (pInstance == 0)
	{
		pInstance = new BulletManager();
	}

	return pInstance;
}

void BulletManager::startUp(const string& path)
{
	LuaManager* luaMgr = LuaManager::getInstance();

	// 读取配置文件路径
	luaMgr->open(path.c_str());
	int bulletNums = (int)luaMgr->getNumber("num");
	vector<string> bullet_config;
	for (int i=1; i<=bulletNums; ++i)
	{
		bullet_config.push_back(luaMgr->getTableString("path", i));
	}
	luaMgr->close();

	// 从对应路径读取子弹属性数据
	for (int i=0; i<bulletNums; ++i)
	{
		luaMgr->open(bullet_config.at(i).c_str());

		string key = luaMgr->getString("name");
		BulletInfo* info = new BulletInfo();

		info->imgPath = luaMgr->getString("imgPath");
		TextureCache::getInstance()->LoadTextureFromFile(info->imgPath);
		info->moveSpeed = (float)luaMgr->getNumber("moveSpeed");
		info->moveAcceleration = (float)luaMgr->getNumber("moveAcceleration");
		info->attack = (float)luaMgr->getNumber("attack");
		info->bCross = (bool)((short)luaMgr->getNumber("bCross"));
		info->bTextureBlend = (bool)((short)luaMgr->getNumber("bTextureBlend"));

		m_info_list.insert(pair<string, BulletInfo*>(key, info));

		luaMgr->close();
	}
}

void BulletManager::shutDown()
{
	Clear();

	delete this;

	pInstance = 0;
}

BulletInfo* BulletManager::GetBulletInfo(const string& key) const
{
	map<string, BulletInfo*>::const_iterator ite = m_info_list.find(key);
	if (ite != m_info_list.end())
	{
		return ite->second;
	}

	return 0;
}

void BulletManager::Clear()
{
	map<string, BulletInfo*>::iterator ite = m_info_list.begin();
	while (ite != m_info_list.end())
	{
		delete ite->second;
		ite = m_info_list.erase(ite);
	}
}
