#include "ItemManager.h"
#include "LuaManager.h"
#include <vector>
#include <Frame2D.h>

USING_NS_F2D

static ItemManager* pInstance = 0;

ItemManager* ItemManager::getInstance()
{
	if (0 == pInstance)
	{
		pInstance = new ItemManager();
	}

	return pInstance;
}

void ItemManager::startUp(const string& configPath)
{
	LuaManager* luaMgr = LuaManager::getInstance();

	luaMgr->open(configPath.c_str());

	int num = (int)luaMgr->getNumber("num");
	vector<string> config_list;
	for (int i=1; i<=num; ++i)
	{
		config_list.push_back(luaMgr->getTableString("path", i));
	}
	luaMgr->close();

	for (int i=0; i<num; ++i)
	{
		luaMgr->open(config_list.at(i).c_str());

		ItemInfo* info = new ItemInfo();

		int key = (int)luaMgr->getNumber("id");

		info->imgPath = luaMgr->getString("imgPath");
		TextureCache::getInstance()->LoadTextureFromFile(info->imgPath);

		m_itemInfo_list.insert(pair<int, ItemInfo*>(key, info));

		luaMgr->close();
	}
}

void ItemManager::shutDown()
{
	Clear();

	delete this;

	pInstance = 0;
}

ItemInfo* ItemManager::GetItemInfo(const int& key) const
{
	map<int, ItemInfo*>::const_iterator ite = m_itemInfo_list.find(key);

	if (ite != m_itemInfo_list.end())
	{
		return ite->second;
	}

	return 0;
}

void ItemManager::Clear()
{
	map<int, ItemInfo*>::iterator ite = m_itemInfo_list.begin();

	while (ite != m_itemInfo_list.end())
	{
		delete ite->second;
		ite = m_itemInfo_list.erase(ite);
	}
}
