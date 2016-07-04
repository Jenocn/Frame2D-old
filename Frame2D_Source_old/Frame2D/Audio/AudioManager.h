#ifndef _AUDIO_MANAGER_H_H_
#define _AUDIO_MANAGER_H_H_

#include "Fmod.h"

class Sound;
class SoundBehavior;

/*
音频管理器
说明:这里是将封装好的所有声音进行一个最后的管理,
	通过这个可以实现大部分简单的声音播放
*/
class AudioManager
{
public:
	static AudioManager* getInstance();

	/*
	函数功能:启动音频功能,初始化FMOD引擎
	*/
	void startUp();

	/*
	函数功能:停止音频功能,并delete自身
	*/
	void shutDown();

	/*
	函数功能:数据更新
	说明:声音的行为,回调函数,自动释放功能都依赖Update
	*/
	void Update(const float& delta);
	
	/*
	函数功能:创建并初始化一个声音,并返回它
	注意:因为将声音对象返回出去了,所以对它的播放操作将不会受到AudioManager的开关约束
	说明:这个声音在创建的同时会被自动管理,在播放一次后会释放内存
	如果你想要创建一个与AudioManager无关的声音文件,请直接用Sound创建
	返回值:Sound对象
	参数1:文件路径名
	*/
	Sound* CreateSoundWithInit(const string& path);

	/*
	函数功能:创建一个声音,并且初始化和缓存这个声音,最后返回它
	注意:因为将声音对象返回出去了,所以对它的播放操作将不会受到AudioManager的开关约束
	说明:这个声音在创建的同时会被自动管理,在播放一次后会释放内存
	如果你想要创建一个与AudioManager无关的声音文件,请直接用Sound创建
	返回值:Sound对象
	参数1:文件路径名
	*/
	Sound* CreateSoundWithInitAndCache(const string& path);

	/*
	函数功能:播放一个音效
	说明:该函数用于从指定路径播放一个音效,如果这个声音之前没有缓存那么在这里也不会缓存,播放完毕后自动释放
	参数1:文件路径名
	参数2:音量(0.0 - 1.0)
	参数3:循环次数(在播放一次的基础上加上这个次数)
	*/
	void playSoundEffect(const string& path, const float& volume = 1, const int& loopCount = 0);

	/*
	函数功能:播放一个音效
	说明:该函数用于从指定路径播放一个音效,如果这个声音之前没有缓存那么在这里也不会缓存,播放完毕后自动释放
	参数1:文件路径名
	参数2:声音行为
	参数3:音量(0.0 - 1.0)
	参数4:循环次数(在播放一次的基础上加上这个次数)
	*/
	void playSoundEffect(const string& path, SoundBehavior* behavior, const float& volume = 1, const int& loopCount = 0);

	/*
	函数功能:停止正在播放的所有音效
	*/
	void stopSoundEffect();

	/*
	函数功能:设置音效的偏移值
	说明:会在原本指定的音量大小上加上这个数值
	参数1:偏移值,大于0增加音量,小于0减小音量
	*/
	void setSoundEffectVolumeOffset(const float& offset);

	/*
	函数功能:返回音效开关的状态
	*/
	bool isOpenSoundEffect();

	/*
	函数功能:设置音效状态是否打开
	参数1:是否打开,true打开,false关闭
	*/
	void setOpenSoundEffect(bool open);

	/*
	函数功能:播放BGM
	说明:该函数用于指定路径播放一个BGM,如果之前没有缓存,那么在这里也不会缓存,播放完毕后自动释放
	同时只能播放一首BGM
	该函数具备指定行为的功能
	参数1:文件路径名
	参数2:声音行为
	参数3:音量(0.0 - 1.0)
	参数4:循环次数(-1为默认无限循环)
	注:目前无限循环并没有实现,而是设置循环255次,伪无限循环
	*/
	void playBGM(const string& path, SoundBehavior* behavior, const float& volume = 1, const int& loopCount = -1);

	/*
	函数功能:播放一个BGM,默认无限循环
	说明:该函数用于指定路径播放一个BGM,如果之前没有缓存,那么在这里也不会缓存,播放完毕后自动释放
	      同时只能播放一首BGM
	参数1:文件路径名
	参数2:音量大小(0.0 - 1.0)
	参数3:循环次数(-1为默认无限循环)
	注:目前无限循环并没有实现,而是设置循环255次,伪无限循环
	*/
	void playBGM(const string& path, const float& volume = 1, const int& loopCount = -1);

	/*
	函数功能:播放已存在的BGM,暂停或者是停止的BGM
	说明:如果没有则不会播放
	*/
	void playBGM();

	/*
	函数功能:暂停正在播放的BGM
	*/
	void pauseBGM();

	/*
	函数功能:停止正在播放的BGM
	说明:停止后,该BGM下次播放将会从初始位置开始
	*/
	void stopBGM();

	/*
	函数功能:获取BGM的Sound对象
	说明:如果当前没有正在播放的BGM,将会返回0
	*/
	Sound* getBGM();

	/*
	函数功能:设置BGM的音量大小
	参数1:音量大小(0.0 - 1.0)
	*/
	void setBGMVolume(const float& volume);

	/*
	函数功能:获得BGM音量
	*/
	float getBGMVolume() const;

	// 函数功能:是否打开BGM开关
	bool isOpenBGM();

	/*
	函数功能:设置BGM是否打开
	参数1:是否打开,true打开,false关闭
	*/
	void setOpenBGM(bool enable);

	/*
	函数功能:缓存一个声音
	参数1:文件路径名
	*/
	void loadSoundForCache(const string& path);

	// 函数功能:清空缓存
	void ClearCache();

private:
	AudioManager()
	: _bgm(0)
	, _openSoundEffect(true)
	, _openBGM(true)
	{}
	AudioManager(AudioManager&);
	AudioManager& operator=(AudioManager&);

	void ClearSoundEffect();

private:
	vector<Sound*> m_sound_list;

	Sound* _bgm;

	bool _openSoundEffect;
	bool _openBGM;
};

#endif