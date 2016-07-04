#include "EffectManager.h"
#include "LuaManager.h"
#include <vector>
#include <Frame2D.h>

USING_NS_F2D

static EffectManager* pInstance = 0;

EffectManager* EffectManager::getInstance()
{
	if (pInstance == 0)
	{
		pInstance = new EffectManager();
	}

	return pInstance;
}

void EffectManager::startUp(const string& configPath)
{
	LuaManager* luaMgr = LuaManager::getInstance();

	luaMgr->open(configPath.c_str());

	int nums = (int)luaMgr->getNumber("num");
	vector<string> config_list;
	for (int i=1; i<=nums; ++i)
	{
		config_list.push_back(luaMgr->getTableString("path", i));
	}
	luaMgr->close();

	for (int i=0; i<nums; ++i)
	{
		luaMgr->open(config_list.at(i).c_str());

		string key = luaMgr->getString("name");
		EffectInfo* info = new EffectInfo();

		info->imgPath = luaMgr->getString("imgPath");
		info->colorKeyR = (float)luaMgr->getNumber("colorKeyR");
		info->colorKeyG = (float)luaMgr->getNumber("colorKeyG");
		info->colorKeyB = (float)luaMgr->getNumber("colorKeyB");
		TextureCache::getInstance()->LoadTextureFromFile(info->imgPath,
			D3DCOLOR_XRGB(info->colorKeyR, info->colorKeyG, info->colorKeyB));
		info->row = (int)luaMgr->getNumber("row");
		info->col = (int)luaMgr->getNumber("col");
		info->interval = (float)luaMgr->getNumber("interval");
		info->count = (int)luaMgr->getNumber("count");
		info->duration = (float)luaMgr->getNumber("duration");
		info->offsetX = (float)luaMgr->getNumber("offsetX");
		info->offsetY = (float)luaMgr->getNumber("offsetY");
		info->angleX = (float)luaMgr->getNumber("angleX");
		info->angleY = (float)luaMgr->getNumber("angleY");
		info->angleZ = (float)luaMgr->getNumber("angleZ");
		info->textureBlend = (bool)(float)luaMgr->getNumber("textureBlend");

		m_effectInfo_list.insert(pair<string, EffectInfo*>(key, info));

		luaMgr->close();
	}
}

void EffectManager::shutDown()
{
	Clear();

	delete this;

	pInstance = 0;
}

EffectInfo* EffectManager::GetEffectInfo(const string& key) const
{
	map<string, EffectInfo*>::const_iterator ite = m_effectInfo_list.find(key);
	if (ite != m_effectInfo_list.end())
	{
		return ite->second;
	}

	return 0;
}

void EffectManager::Clear()
{
	map<string, EffectInfo*>::iterator ite = m_effectInfo_list.begin();
	while (ite != m_effectInfo_list.end())
	{
		delete ite->second;
		ite = m_effectInfo_list.erase(ite);
	}
}
