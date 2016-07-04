#ifndef _STAGE_MANAGER_H_H_
#define _STAGE_MANAGER_H_H_

#include <vector>
#include <Frame2D.h>

using namespace std;

class GameMap;

class StageInfo
{
public:
	// 0表示敌人,1表示标签
	int type;
	// 敌人/标签的名称
	string name;
	// 敌人/标签出现时间
	float showTime;
	// 敌人/标签坐标
	float positionX;
	float positionY;
	// 移动的方向
	float directionAngle;
	// 地图滚动速度
	float mapScrollSpeed;

	StageInfo()
	: type(0)
	, name("")
	, showTime(0)
	, positionX(0)
	, positionY(0)
	, directionAngle(0)
	, mapScrollSpeed(0)
	{}
};

class StageManager
{
public:
	static StageManager* getInstance();

	void startUp(const string& stagePath, Frame2D::Scene* scene);

	void Update(const float& delta);

	void shutDown();

	void Clear();

private:
	StageManager()
	: _map(0)
	, _musicPath("")
	, _bossBgmPath("")
	, _scene(0)
	{}
	StageManager(StageManager&);
	StageManager& operator=(StageManager&);
private:
	vector<StageInfo*> m_info_list;

	GameMap* _map;

	string _musicPath;
	string _bossBgmPath;

	// 绑定场景
	Frame2D::Scene* _scene;
};

#endif