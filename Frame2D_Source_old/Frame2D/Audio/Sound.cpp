#include "Sound.h"
#include "SoundBehavior.h"
#include "FMODManager.h"
#include "AudioCache.h"

static SoundHelper* helperInstance = 0;

SoundHelper* SoundHelper::getInstance()
{
	if (helperInstance == 0)
	{
		helperInstance = new SoundHelper();
	}

	return helperInstance;
}

void SoundHelper::Release()
{
	m_helper_list.clear();

	delete this;
}

void SoundHelper::Push(SoundHelperInfo* info)
{
	m_helper_list.push_back(info);
}

void SoundHelper::ReleaseSoundByChannel(FMOD::Channel* channel)
{
	vector<SoundHelperInfo*>::iterator ite = m_helper_list.begin();
	while (ite != m_helper_list.end())
	{
		if ((*ite)->getChannel() == channel)
		{
			(*ite)->getSound()->setEnable(false);
			m_helper_list.erase(ite);
			break;
		}

		++ite;
	}
}

Sound* Sound::Create()
{
	Sound* sound = new Sound();

	return sound;
}

Sound* Sound::CreateWithInit(const string& path)
{
	Sound* sound = new Sound();

	assert(sound->InitWithFile(path, false) && "Sound Init Failed!");

	return sound;
}

Sound* Sound::CreateWithInitAndCache(const string& path)
{
	Sound* sound = new Sound();

	assert(sound->InitWithFile(path, true) && "Sound Init Failed!");

	return sound;
}

FMOD_RESULT F_CALLBACK onSoundCompleteFunc(FMOD_CHANNEL* channel, FMOD_CHANNEL_CALLBACKTYPE type, void* cmd1, void* cmd2)
{
	if (type == FMOD_CHANNEL_CALLBACKTYPE_END)
	{
		FMOD::Channel* useChannel = (FMOD::Channel*)channel;
		SoundHelper::getInstance()->ReleaseSoundByChannel(useChannel);
	}

	return FMOD_OK;
}

bool Sound::InitWithFile(const string& path, bool bCache)
{
	_cacheEnable = bCache;

	if (path.compare("") == 0)
	{
		return false;
	}

	if (bCache)
	{
		const AudioInfo* audioInfo = AudioCache::getInstance()->LoadSoundFromFile(path);

		if (audioInfo == 0)
		{
			return false;
		}

		_sound = audioInfo->getSound();
	}
	else
	{
		FMODManager::getInstance()->getSystem()->createSound(
			path.c_str(), FMOD_HARDWARE, 0, &_sound);
	}

	FMODManager::getInstance()->getSystem()->playSound(
		FMOD_CHANNEL_FREE, _sound, true, &_channel);

	return true;
}

void Sound::AutoRelease()
{
	SoundHelper::getInstance()->Push(new SoundHelperInfo(this, _channel));
	_channel->setCallback(onSoundCompleteFunc);
}

void Sound::Release()
{
	vector<SoundBehavior*>::iterator ite = m_behavior_list.begin();
	while (ite != m_behavior_list.end())
	{
		(*ite)->Release();
		ite = m_behavior_list.erase(ite);
	}

	SoundHelper::getInstance()->ReleaseSoundByChannel(_channel);
	_channel->stop();
	_channel = 0;

	if (false == _cacheEnable)
	{
		if (_sound != 0)
		{
			_sound->release();
			_sound = 0;
		}
	}

	delete this;
}

void Sound::play()
{
	bool temp = false;

	_channel->getPaused(&temp);

	if (temp)
	{
		_channel->setPaused(false);
	}
}

void Sound::reset()
{
	_channel->setPosition(0, FMOD_TIMEUNIT_MS);
}

void Sound::playWithBehavior(SoundBehavior* soundBehavior)
{
	soundBehavior->RegisterSound(this);
	m_behavior_list.push_back(soundBehavior);
}

void Sound::stop()
{
	pause();
	reset();
}

void Sound::pause()
{
	bool temp = false;
	_channel->getPaused(&temp);

	if (temp == false)
	{
		_channel->setPaused(true);
	}
}

void Sound::Update(const float& delta)
{
	vector<SoundBehavior*>::iterator ite = m_behavior_list.begin();
	while (ite != m_behavior_list.end())
	{
		if ((*ite)->IsFinish())
		{
			(*ite)->Release();
			ite = m_behavior_list.erase(ite);
		}
		else
		{
			++ite;
		}
	}

	ite = m_behavior_list.begin();
	while (ite != m_behavior_list.end())
	{
		(*ite)->Update(delta);

		++ite;
	}
}

float Sound::getVolume() const
{
	return _volume;
}

void Sound::setVolume(const float& volume)
{
	_volume = volume;

	if (_volume > 1)
	{
		_volume = 1;
	}

	if (_volume < 0)
	{
		_volume = 0;
	}

	_channel->setVolume(_volume);
}

void Sound::setLoopCount(const int& loopCount)
{
	_channel->setMode(FMOD_LOOP_NORMAL);
	_channel->setLoopCount(loopCount);
}

void Sound::setEnable(bool enable)
{
	_soundEnable = enable;
}

bool Sound::isEnable()
{
	return _soundEnable;
}
