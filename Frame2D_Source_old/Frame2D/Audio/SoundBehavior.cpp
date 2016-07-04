#include "SoundBehavior.h"
#include "Sound.h"

SoundDelay* SoundDelay::Create(const float& delay)
{
	SoundDelay* behavior = new SoundDelay(delay);

	return behavior;
}

void SoundDelay::Init()
{
	_sound->pause();
}

void SoundDelay::Update(const float& delta)
{
	if (_mb_finish)
	{
		return;
	}

	if (_delay <= 0)
	{
		_sound->play();
		_mb_finish = true;
		return;
	}

	_delay -= delta;
}


SoundVolumeChange* SoundVolumeChange::Create(const float& second, const float& volume)
{
	SoundVolumeChange* behavior = new SoundVolumeChange(second, volume);

	return behavior;
}

void SoundVolumeChange::Init()
{
	_changeNum = (_volume - _sound->getVolume()) / _time;

	if (_changeNum == 0)
	{
		_mb_finish = true;
	}

	_sound->play();
}

void SoundVolumeChange::Update(const float& delta)
{
	if (_mb_finish)
	{
		return;
	}

	if (_time <= 0)
	{
		if (_sound->getVolume() != _volume)
		{
			_sound->setVolume(_volume);
		}

		_mb_finish = true;

		return;
	}

	_time -= delta;

	_tempTime += delta;

	if (_tempTime >= 1)
	{
		float tempVolume = _sound->getVolume() + _changeNum;

		if (_changeNum > 0)
		{
			if (tempVolume > _volume)
			{
				tempVolume = _volume;
				_mb_finish = true;
			}
		}

		if (_changeNum < 0)
		{
			if (tempVolume < _volume)
			{
				tempVolume = _volume;
				_mb_finish = true;
			}
		}

		_sound->setVolume(tempVolume);
		_tempTime = 0;
	}
}