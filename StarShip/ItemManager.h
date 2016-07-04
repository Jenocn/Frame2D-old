#ifndef _ITEM_MANAGER_H_H_
#define _ITEM_MANAGER_H_H_

#include <map>
#include <string>

using namespace std;

class ItemInfo
{
public:
	string imgPath;

	ItemInfo()
	: imgPath("")
	{}
};

class ItemManager
{
public:
	static ItemManager* getInstance();

	void startUp(const string& configPath);

	void shutDown();

	ItemInfo* GetItemInfo(const int& key) const;

	void Clear();

private:
	ItemManager()
	{}
	ItemManager(ItemManager&);
	ItemManager& operator=(ItemManager&);

private:
	map<int, ItemInfo*> m_itemInfo_list;
};

#endif