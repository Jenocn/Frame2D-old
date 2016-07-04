#ifndef _AUDIO_CACHE_H_H_
#define _AUDIO_CACHE_H_H_

#include "Fmod.h"

using namespace std;

// 音频信息
class AudioInfo
{
public:
	explicit AudioInfo(const string& path, FMOD::Sound*& sound)
	{
		this->path = path;
		this->_sound = sound;
	}

	// 获取文件路径名
	const string& getPath() const
	{
		return path;
	}

	// 获取FMOD声音对象指针
	FMOD::Sound* getSound() const
	{
		return _sound;
	}

private:
	string path;
	FMOD::Sound* _sound;
};

// 音频缓冲类
class AudioCache
{
public:
	static AudioCache* getInstance();

	/*
	函数功能:释放缓冲类使用的所有内存,并delete自身
	*/
	void Release();

	/*
		函数功能:通过文件加载声音
		返回值:如果加载成功,那么返回一个包含声音的音频信息结构体对象
		参数1:文件路径名
	*/
	const AudioInfo* LoadSoundFromFile(const string& path);

	/*
		函数功能:清空声音缓存列表
	*/
	void ClearAudioCache();

	/*
		函数功能:根据文件路径名在缓存容器中查找是否存在这个声音,如果存在返回真
		返回值:是否找到
		参数1:文件路径名
	*/
	bool isExist(const string& path);

private:
	AudioCache() {}
	AudioCache(AudioCache&);
	AudioCache& operator=(AudioCache&);

private:
	vector<AudioInfo*> m_audio_list;
};


#endif