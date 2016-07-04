#ifndef _FMOD_MANAGER_H_H_
#define _FMOD_MANAGER_H_H_

#include "Fmod.h"

/*
FMOD引擎管理类
说明:如果使用AudioManager的话,你不需要直接使用这个类
*/
class FMODManager
{
public:
	static FMODManager* getInstance();

	/*
	函数功能:启动FMOD管理器,初始化FMOD引擎
	说明:如果不启动它将无法使用音频功能
	*/
	void startUp();

	/*
	函数功能:停止FMOD管理器,释放FMOD引擎资源,并delete自身
	*/
	void shutDown();

	/*
	函数功能:更新数据
	说明:声音的回调函数,Sound的自动释放功能,那么就必须调用,否则那些功能将不生效
	*/
	void Update(const float& delta);

	// 获取引擎的system对象
	FMOD::System* getSystem() const;

private:
	FMODManager()
	: _system(0)
	{}
	FMODManager(FMODManager&);
	FMODManager& operator=(FMODManager&);

private:
	FMOD::System* _system;
};

#endif