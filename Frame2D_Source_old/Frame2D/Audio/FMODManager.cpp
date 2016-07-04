#include "FMODManager.h"

static FMODManager* pInstance = 0;

FMODManager* FMODManager::getInstance()
{
	if (pInstance == 0)
	{
		pInstance = new FMODManager();
	}

	return pInstance;
}

void FMODManager::startUp()
{
	FMOD_RESULT _result;
	unsigned int _version;
	int _numdrivers;
	FMOD_SPEAKERMODE _speakermode;
	FMOD_CAPS _caps;
	char _name[256];

	_result = FMOD::System_Create(&_system);
	assert(_result == FMOD_OK && "FMOD Create Failed!");

	_result = _system->getVersion(&_version);
	assert(_result == FMOD_OK && "FMOD Create Failed!");
	assert(_version >= FMOD_VERSION && "FMOD Create Failed!");

	_result = _system->getNumDrivers(&_numdrivers);
	assert(_result == FMOD_OK && "FMOD Create Failed!");
	if (0 == _numdrivers)
	{
		_result = _system->setOutput(FMOD_OUTPUTTYPE_NOSOUND);
		assert(_result == FMOD_OK && "FMOD Create Failed!");
	}
	else
	{
		_result = _system->getDriverCaps(0, &_caps, 0, 0, &_speakermode);
		assert(_result == FMOD_OK && "FMOD Create Failed!");

		_result = _system->setSpeakerMode(_speakermode);
		assert(_result == FMOD_OK && "FMOD Create Failed!");

		if (_caps & FMOD_CAPS_HARDWARE_EMULATED)
		{
			_result = _system->setDSPBufferSize(1025, 10);
			assert(_result == FMOD_OK && "FMOD Create Failed!");
		}

		_result = _system->getDriverInfo(0, _name, 256, 0);
		assert(_result == FMOD_OK && "FMOD Create Failed!");

		if (strstr(_name, "SigmaTel"))
		{
			_result = _system->setSoftwareFormat(48000, FMOD_SOUND_FORMAT_PCMFLOAT,
				0, 0, FMOD_DSP_RESAMPLER_LINEAR);
			assert(_result == FMOD_OK && "FMOD Create Failed!");
		}
	}

	_result = _system->init(100, FMOD_INIT_NORMAL, 0);
	if (_result == FMOD_ERR_OUTPUT_CREATEBUFFER)
	{
		_result = _system->setSpeakerMode(FMOD_SPEAKERMODE_STEREO);
		assert(_result == FMOD_OK && "FMOD Create Failed!");

		_result = _system->init(100, FMOD_INIT_NORMAL, 0);
		assert(_result == FMOD_OK && "FMOD Create Failed!");
	}
}

void FMODManager::shutDown()
{
	_system->close();
	_system->release();
	delete this;
	pInstance = 0;
}

void FMODManager::Update(const float& delta)
{
	getSystem()->update();
}

FMOD::System* FMODManager::getSystem() const
{
	return _system;
}