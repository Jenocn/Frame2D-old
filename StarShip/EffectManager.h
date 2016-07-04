#ifndef _EFFECT_MANAGER_H_H_
#define _EFFECT_MANAGER_H_H_

#include <map>
#include <string>

using namespace std;

class EffectInfo
{
public:
	string imgPath;
	int row;
	int col;
	float interval;
	int count;
	float duration;
	float offsetX;
	float offsetY;
	float angleX;
	float angleY;
	float angleZ;
	int colorKeyR;
	int colorKeyG;
	int colorKeyB;
	bool textureBlend;

	EffectInfo()
	: imgPath("")
	, row(0)
	, col(0)
	, interval(0)
	, count(0)
	, duration(0)
	, offsetX(0)
	, offsetY(0)
	, angleX(0)
	, angleY(0)
	, angleZ(0)
	, colorKeyR(0)
	, colorKeyG(0)
	, colorKeyB(0)
	, textureBlend(false)
	{}
};

// 特效管理器
class EffectManager
{
public:
	static EffectManager* getInstance();

	void startUp(const string& configPath);

	void shutDown();

	EffectInfo* GetEffectInfo(const string& key) const;

	void Clear();

private:
	EffectManager()
	{}
	EffectManager(EffectManager&);
	EffectManager& operator=(EffectManager&);

private:
	map<string, EffectInfo*> m_effectInfo_list;
};

#endif