#include "AudioCache.h"
#include "FMODManager.h"

static AudioCache* pInstance = 0;

AudioCache* AudioCache::getInstance()
{
	if (pInstance == 0)
	{
		pInstance = new AudioCache();
	}

	return pInstance;
}

void AudioCache::Release()
{
	ClearAudioCache();
	delete this;
	pInstance = 0;
}

const AudioInfo* AudioCache::LoadSoundFromFile(const string& path)
{
	vector<AudioInfo*>::iterator ite = m_audio_list.begin();
	while (ite != m_audio_list.end())
	{
		if ((*ite)->getPath().compare(path) == 0)
		{
			return (*ite);
		}

		++ite;
	}

	FMOD::Sound* sound;

	FMODManager::getInstance()->getSystem()->createSound(
		path.c_str(), FMOD_HARDWARE, 0, &sound);

	AudioInfo* audioInfo = new AudioInfo(path, sound);
	m_audio_list.push_back(audioInfo);

	return audioInfo;
}

void AudioCache::ClearAudioCache()
{
	vector<AudioInfo*>::iterator ite = m_audio_list.begin();
	while (ite != m_audio_list.end())
	{
		(*ite)->getSound()->release();
		delete *ite;
		ite = m_audio_list.erase(ite);
	}
}

bool AudioCache::isExist(const string& path)
{
	vector<AudioInfo*>::iterator ite = m_audio_list.begin();
	while (ite != m_audio_list.end())
	{
		if ((*ite)->getPath().compare(path) == 0)
		{
			return true;
		}

		++ite;
	}

	return false;
}
