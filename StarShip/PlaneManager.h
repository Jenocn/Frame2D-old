#ifndef _ENEMY_MANAGER_H_H_
#define _ENEMY_MANAGER_H_H_

#include <map>
#include <string>

using namespace std;

class EnemyInfo
{
public:
	string imgPath;
	int bulletType;
	float hpMax;
	// 朝着方向移动的持续时间
	float duration;
	// 在持续时间后停留的时间(停留后会继续先前的轨迹)
	float stayTime;
	float moveSpeed;
	int score;
	int itemID;
	int layer; // 范围1~3,分别从下到上
	int moveStateID; // 移动状态ID

	EnemyInfo()
	: imgPath("")
	, bulletType(0)
	, hpMax(0)
	, duration(0)
	, stayTime(0)
	, moveSpeed(0)
	, score(0)
	, itemID(0)
	, layer(0)
	{}
};

class OwnInfo
{
public:
	string imgPath;
	int bulletType;
	float hpMax;
	float moveSpeed;
	int bulletLevelMax;
	int missileLevelMax;

	OwnInfo()
	: imgPath("")
	, bulletType(0)
	, hpMax(0)
	, moveSpeed(0)
	, bulletLevelMax(0)
	, missileLevelMax(0)
	{}
};

class PlaneManager
{
public:
	static PlaneManager* getInstance();

	//======================
	// 启动敌人管理器
	// 参数:敌人配置文件路径
	//======================
	void startUp(const string& path);

	//======================
	// 停止敌人管理器,释放内存,delete自身
	//======================
	void shutDown();

	//======================
	// 根据关键词查找对应的敌人
	// 参数:关键词,敌人名称
	//======================
	EnemyInfo* GetEnemyInfo(const string& key) const;

	//======================
	// 根据关键词查找对应的主角
	// 参数:关键词,主角名称
	//======================
	OwnInfo* GetOwnInfo(const string& key) const;

	//======================
	// 清空所有敌人数据
	//======================
	void Clear();

private:
	PlaneManager() {}
	PlaneManager(PlaneManager&);
	PlaneManager& operator=(PlaneManager&);

private:
	map<string, EnemyInfo*> m_enemyInfo_list;
	map<string, OwnInfo*> m_ownInfo_list;	

};

#endif