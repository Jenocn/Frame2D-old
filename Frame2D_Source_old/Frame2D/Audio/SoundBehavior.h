#ifndef _SOUND_BEHAVIOR_H_H_
#define _SOUND_BEHAVIOR_H_H_

#include "Fmod.h"

class Sound;

// 声音行为类
class SoundBehavior
{
public:
	virtual ~SoundBehavior() {}

	/*
		函数功能:绑定声音,即需要执行行为的声音对象
		参数:声音
	*/
	void RegisterSound(Sound* sound)
	{
		_sound = sound;
		Init();
	}

	/*
		函数功能:初始化
		说明:不需要手动调用
	*/
	virtual void Init() = 0;

	/*
		函数功能:释放这个行为中途产生的内存
		说明:这个函数自身已经执行delete,无需再次执行,否则会报错
	*/
	void Release()
	{
		delete this;
	}

	/*
		函数功能:更新数据
		参数1:每帧的时间间隔
	*/
	virtual void Update(const float& delta) = 0;

	/*
		函数功能:返回是否已经结束行为
	*/
	bool IsFinish()
	{
		return _mb_finish;
	}

protected:
	SoundBehavior()
		: _sound(0)
		, _mb_finish(false)
	{}

private:
	SoundBehavior(SoundBehavior&);
	SoundBehavior& operator=(SoundBehavior&);

protected:
	Sound* _sound;
	bool _mb_finish;
};

// 声音延迟播放
class SoundDelay : public SoundBehavior
{
public:
	/*
		函数功能:创建一个声音的延迟行为
		参数1:延迟时间,单位秒
	*/
	static SoundDelay* Create(const float& delay);

	virtual ~SoundDelay() {}

	virtual void Init();

	virtual void Update(const float& delta);

private:
	SoundDelay(const float& delay)
	: _delay(delay)
	{}
	SoundDelay(SoundDelay&);
	SoundDelay& operator=(SoundDelay&);

private:
	float _delay;
};

// 音量渐变
class SoundVolumeChange : public SoundBehavior
{
public:
	/*
		函数功能:创建一个音量渐变行为
		参数1:达到目标所需的时间,单位秒
		参数2:目标音量
	*/
	static SoundVolumeChange* Create(const float& second, const float& volume);

	virtual ~SoundVolumeChange() {}

	virtual void Init();

	virtual void Update(const float& delta);

private:
	SoundVolumeChange(const float& time, const float& volume)
	: _time(time)
	, _tempTime(0)
	, _volume(volume)
	, _changeNum(0) {}
	SoundVolumeChange(SoundVolumeChange&);
	SoundVolumeChange& operator=(SoundVolumeChange&);

private:
	float _time;
	float _tempTime;
	float _volume;
	float _changeNum;
};

#endif