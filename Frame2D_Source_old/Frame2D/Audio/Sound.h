#ifndef _SOUND_H_H_
#define _SOUND_H_H_

#include "Fmod.h"

class SoundBehavior;
class Sound;

/*
帮助管理声音的信息结构体
*/
class SoundHelperInfo
{
public:
	SoundHelperInfo(Sound* sound, FMOD::Channel* channel)
	: _sound(sound)
	, _channel(channel)
	{}

	FMOD::Channel* getChannel() const
	{
		return _channel;
	}

	Sound* getSound() const
	{
		return _sound;
	}

private:
	Sound* _sound;
	FMOD::Channel* _channel;
};

// 帮助管理声音的类
class SoundHelper
{
public:
	static SoundHelper* getInstance();

	void Release();

	void Push(SoundHelperInfo* info);
	void ReleaseSoundByChannel(FMOD::Channel* channel);

private:
	SoundHelper() {}
	SoundHelper(SoundHelper&);
	SoundHelper& operator=(SoundHelper&);

private:
	vector<SoundHelperInfo*> m_helper_list;
};

/*
声音类:最多只能同时创建32个声音,同时超过32个将不会再播放
*/
class Sound
{
public:
	// 创建一个空声音
	static Sound* Create();

	/*
	函数功能:创建一个声音,并从文件初始化声音
	说明:不缓存
	*/
	static Sound* CreateWithInit(const string& path);

	/*
	函数功能:创建一个声音,并从文件初始化声音并且缓存这个声音
	*/
	static Sound* CreateWithInitAndCache(const string& path);

	/*
	函数功能:通过文件初始化声音
	返回值:如果找到文件并读取成功返回真,否则返回假
	参数1:文件路径
	参数2:是否缓存,true为缓存,false不缓存
	*/
	bool InitWithFile(const string& path, bool bCache);

	/*
	函数功能:自动释放内存
	说明:当调用这个函数之后,声音将会在播放完毕之后自动释放内存空间
	      该功能只会在调用FMODManager的Update之后才会生效
	*/
	void AutoRelease();

	/*
	函数功能:释放Sound所使用的内存空间,并delete自身
	说明:缓存的声音不会在这被释放,但仍会释放其他使用的空间
	*/
	void Release();

	/*
	函数功能:正常播放这个声音,执行后会立刻播放
	*/
	void play();

	/*
	函数功能:重置播放位置为初始位置
	*/
	void reset();

	/*
	函数功能:播放这个声音,并且执行一个行为
	参数1:声音行为
	*/
	void playWithBehavior(SoundBehavior* soundBehavior);

	// 停止播放(实际上等于暂停并重置为初始位置)
	void stop();

	// 暂停播放,仍然会记录播放的位置
	void pause();

	// 更新数据
	void Update(const float& delta);

	// 获得音量大小
	float getVolume() const;

	/*
	函数功能:设置音量大小
	参数1:音量,范围(0.0 - 1.0)
	*/
	void setVolume(const float& volume);

	/*
	函数功能:设置循环次数
	参数1:循环的次数(在播放的基础上增加的次数)
	*/
	void setLoopCount(const int& loopCount);

	/*
	函数功能:设置状态
	说明:这个函数的功能是帮助AudioManager来判断这个声音是否有效
		  如果使用了自动释放功能,那么一般情况下不用去修改它,除非你需要
	参数1:是否有效,true有效,false无效
	*/
	void setEnable(bool enable);

	/*
	函数功能:返回是否有效的状态
	*/
	bool isEnable();

private:
	Sound()
		: _sound(0)
		, _channel(0)
		, _volume(1)
		, _cacheEnable(false)
		, _soundEnable(true)
	{}
	Sound(Sound&);
	Sound& operator=(Sound&);

private:
	FMOD::Sound* _sound;
	FMOD::Channel* _channel;

	// 声音行为的容器
	vector<SoundBehavior*> m_behavior_list;

	// 音量
	float _volume;
	// 是否缓存
	bool _cacheEnable;
	// 是否有效
	bool _soundEnable;
};

#endif