#include "AudioManager.h"
#include "Sound.h"
#include "SoundBehavior.h"
#include "AudioCache.h"
#include "FMODManager.h"

static AudioManager* pInstance = 0;

AudioManager* AudioManager::getInstance()
{
	if (pInstance == 0)
	{
		pInstance = new AudioManager();
	}

	return pInstance;
}

void AudioManager::startUp()
{
	FMODManager::getInstance()->startUp();
}

void AudioManager::shutDown()
{
	if (_bgm)
	{
		_bgm->Release();
	}

	ClearSoundEffect();
	ClearCache();

	FMODManager::getInstance()->shutDown();

	delete this;

	pInstance = 0;
}

void AudioManager::Update(const float& delta)
{
	FMODManager::getInstance()->Update(delta);

	if (_bgm != 0)
	{
		if (_bgm->isEnable() == false)
		{
			_bgm->Release();
			_bgm = 0;
		}
	}

	if (_bgm != 0)
	{
		_bgm->Update(delta);
	}

	vector<Sound*>::iterator ite = m_sound_list.begin();
	while (ite != m_sound_list.end())
	{
		if ((*ite)->isEnable() == false)
		{
			(*ite)->Release();
			ite = m_sound_list.erase(ite);
		}
		else
		{
			++ite;
		}
	}

	ite = m_sound_list.begin();
	while (ite != m_sound_list.end())
	{
		(*ite)->Update(delta);

		++ite;
	}
}

Sound* AudioManager::CreateSoundWithInit(const string& path)
{
	Sound* sound = Sound::CreateWithInit(path);
	sound->AutoRelease();
	m_sound_list.push_back(sound);

	return sound;
}

Sound* AudioManager::CreateSoundWithInitAndCache(const string& path)
{
	Sound* sound = Sound::CreateWithInitAndCache(path);
	sound->AutoRelease();
	m_sound_list.push_back(sound);

	return sound;
}

void AudioManager::playSoundEffect(const string& path, const float& volume, const int& loopCount)
{
	if (isOpenSoundEffect() == false)
	{
		return;
	}

	Sound* sound = 0;
	if (AudioCache::getInstance()->isExist(path))
	{
		sound = Sound::CreateWithInitAndCache(path);
	}
	else
	{
		sound = Sound::CreateWithInit(path);
	}

	sound->AutoRelease();

	m_sound_list.push_back(sound);

	sound->setVolume(volume);
	sound->setLoopCount(loopCount);

	sound->play();
}

void AudioManager::playSoundEffect(const string& path, SoundBehavior* behavior, const float& volume, const int& loopCount)
{
	if (isOpenSoundEffect() == false)
	{
		return;
	}

	Sound* sound = 0;
	if (AudioCache::getInstance()->isExist(path))
	{
		sound = Sound::CreateWithInitAndCache(path);
	}
	else
	{
		sound = Sound::CreateWithInit(path);
	}

	sound->AutoRelease();

	m_sound_list.push_back(sound);

	sound->setVolume(volume);
	sound->setLoopCount(loopCount);

	sound->playWithBehavior(behavior);
}

void AudioManager::stopSoundEffect()
{
	vector<Sound*>::iterator ite = m_sound_list.begin();
	while (ite != m_sound_list.end())
	{
		(*ite)->stop();

		++ite;
	}
}

void AudioManager::setSoundEffectVolumeOffset(const float& offset)
{
	vector<Sound*>::iterator ite = m_sound_list.begin();
	while (ite != m_sound_list.end())
	{
		(*ite)->setVolume((*ite)->getVolume() + offset);

		++ite;
	}
}

bool AudioManager::isOpenSoundEffect()
{
	return _openSoundEffect;
}

void AudioManager::setOpenSoundEffect(bool open)
{
	_openSoundEffect = open;

	if (_openSoundEffect == false)
	{
		ClearSoundEffect();
	}
}

void AudioManager::playBGM(const string& path, const float& volume, const int& loopCount)
{
	if (_bgm != 0)
	{
		_bgm->Release();
		_bgm = 0;
	}

	if (AudioCache::getInstance()->isExist(path))
	{
		_bgm = Sound::CreateWithInitAndCache(path);
	}
	else
	{
		_bgm = Sound::CreateWithInit(path);
	}

	_bgm->AutoRelease();

	_bgm->setVolume(volume);
	if (loopCount == -1)
	{
		_bgm->setLoopCount(255);
	}
	else
	{
		_bgm->setLoopCount(loopCount);
	}

	if (isOpenBGM())
	{
		_bgm->play();
	}
}

void AudioManager::playBGM(const string& path, SoundBehavior* behavior, const float& volume, const int& loopCount)
{
	if (_bgm != 0)
	{
		_bgm->Release();
		_bgm = 0;
	}

	if (AudioCache::getInstance()->isExist(path))
	{
		_bgm = Sound::CreateWithInitAndCache(path);
	}
	else
	{
		_bgm = Sound::CreateWithInit(path);
	}

	_bgm->AutoRelease();

	_bgm->setVolume(volume);
	if (loopCount == -1)
	{
		_bgm->setLoopCount(255);
	}
	else
	{
		_bgm->setLoopCount(loopCount);
	}

	if (isOpenBGM())
	{
		_bgm->playWithBehavior(behavior);
	}
}

void AudioManager::playBGM()
{
	if (isOpenBGM())
	{
		if (_bgm != 0)
		{
			_bgm->play();
		}
	}
}

void AudioManager::pauseBGM()
{
	if (_bgm != 0)
	{
		_bgm->pause();
	}
}

void AudioManager::stopBGM()
{
	if (_bgm != 0)
	{
		_bgm->stop();
	}
}

Sound* AudioManager::getBGM()
{
	return _bgm;
}

void AudioManager::setBGMVolume(const float& volume)
{
	if (_bgm != 0)
	{
		_bgm->setVolume(volume);
	}
}

float AudioManager::getBGMVolume() const
{
	if (_bgm != 0)
	{
		return _bgm->getVolume();
	}

	return 1.0f;
}

bool AudioManager::isOpenBGM()
{
	return _openBGM;
}

void AudioManager::setOpenBGM(bool enable)
{
	_openBGM = enable;

	if (_openBGM == false)
	{
		if (_bgm != 0)
		{
			stopBGM();
		}
	}
	else
	{
		if (_bgm != 0)
		{
			playBGM();
		}
	}
}

void AudioManager::loadSoundForCache(const string& path)
{
	AudioCache::getInstance()->LoadSoundFromFile(path);
}

void AudioManager::ClearCache()
{
	AudioCache::getInstance()->ClearAudioCache();
}

void AudioManager::ClearSoundEffect()
{
	vector<Sound*>::iterator ite = m_sound_list.begin();
	while (ite != m_sound_list.end())
	{
		(*ite)->Release();
		ite = m_sound_list.erase(ite);
	}
}
