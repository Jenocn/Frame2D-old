#ifndef _BULLET_MANAGER_H_H_
#define _BULLET_MANAGER_H_H_

#include <map>
#include <string>

using namespace std;

class BulletInfo
{
public:
	// 常规属性
	string imgPath;
	float moveSpeed;
	float moveAcceleration;
	float attack;
	bool bCross;
	bool bTextureBlend;

	BulletInfo()
		: imgPath("")
		, moveSpeed(0)
		, moveAcceleration(0)
		, attack(0)
		, bCross(false)
		, bTextureBlend(false)
	{}
};

// 子弹管理器单例类
class BulletManager
{
public:
	static BulletManager* getInstance();

	//======================
	// 启动子弹管理器
	// 说明:子弹管理器管理所有类型子弹
	// 参数:子弹配置文件路径
	//======================
	void startUp(const string& path);

	//======================
	// 停止子弹管理器,释放内存,delete自身
	//======================
	void shutDown();

	//======================
	// 根据关键词查找对应的子弹
	// 参数:关键词,子弹名称
	//======================
	BulletInfo* GetBulletInfo(const string& key) const;

	//======================
	// 清空所有子弹数据
	//======================
	void Clear();

private:
	BulletManager()
	{}
	BulletManager(BulletManager&);
	BulletManager& operator=(BulletManager&);

private:
	map<string, BulletInfo*> m_info_list;
};

#endif