#include "ParticleSystem.h"
#include "Particle.h"

USING_NS_F2D

ParticleSystem* ParticleSystem::Create()
{
	ParticleSystem* system = new (nothrow)ParticleSystem();

	assert(system && system->Init() && "ParticleSystem Create Failed!");

	return system;
}

ParticleSystem* ParticleSystem::Create(
	const float& positionX,
	const float& positionY,
	const float& positionZ,
	const float& launcherDuration,
	const float& launcherInterval,
	const float& systemDuration,
	const int& maxNums,
	const int& boundBoxPositionX,
	const int& boundBoxPositionY,
	const int& boundBoxWidth,
	const int& boundBoxHeight)
{
	ParticleSystem* system = new (nothrow)ParticleSystem();
	if (system == 0 || false == system->Init())
	{
		return false;
	}
	system->SetPosition(positionX, positionY, positionZ);
	system->SetDuration(launcherDuration, systemDuration);
	system->SetMaxNums(maxNums);
	system->SetLaunchInterval(launcherInterval);
	system->SetBoundBox(
		boundBoxPositionX,
		boundBoxPositionY,
		boundBoxWidth,
		boundBoxHeight);

	return system;
}

void ParticleSystem::AddParticleTexture(
	const string& texturePath)
{
	if (texturePath.compare("") != 0)
	{
		m_texturePath_list.push_back(texturePath);
	}
}

void ParticleSystem::SetParticleData(
	const float& duration,
	const float& velocityX,
	const float& velocityY,
	const float& velocityZ,
	const float& accelerationX,
	const float& accelerationY,
	const float& accelerationZ,
	float alpha, float r, float g, float b,
	const float& scale,
	bool textureBlendEnable)
{
	_particleDuration = duration;
	_velocityX = velocityX;
	_velocityY = velocityY;
	_velocityZ = velocityZ;
	_accelerationX = accelerationX;
	_accelerationY = accelerationY;
	_accelerationZ = accelerationZ;
	_alpha = alpha;
	_r = r;
	_g = g;
	_b = b;
	_scale = scale;
	_textureBlend = textureBlendEnable;
}

void ParticleSystem::SetParticleOffsetData(
	const float& durationOffset,
	const float& positionOffsetX,
	const float& positionOffsetY,
	const float& positionOffsetZ,
	const float& velocityOffsetX,
	const float& velocityOffsetY,
	const float& velocityOffsetZ,
	const float& accelerationOffsetX,
	const float& accelerationOffsetY,
	const float& accelerationOffsetZ,
	float alphaOffset, float rOffset,
	float gOffset, float bOffset,
	const float& scaleOffset)
{
	_particleDurationOffset = durationOffset;
	_positionOffsetX = positionOffsetX;
	_positionOffsetY = positionOffsetY;
	_positionOffsetZ = positionOffsetZ;
	_velocityOffsetX = velocityOffsetX;
	_velocityOffsetY = velocityOffsetY;
	_velocityOffsetZ = velocityOffsetZ;
	_accelerationOffsetX = accelerationOffsetX;
	_accelerationOffsetY = accelerationOffsetY;
	_accelerationOffsetZ = accelerationOffsetZ;
	_alphaOffset = alphaOffset;
	_rOffset = rOffset;
	_gOffset = gOffset;
	_bOffset = bOffset;
	_scaleOffset = scaleOffset;
}

ParticleSystem::~ParticleSystem()
{

}

bool ParticleSystem::Init()
{
	return true;
}

void ParticleSystem::Release()
{
	Clear();

	m_texturePath_list.clear();

	delete this;
}

void ParticleSystem::Update(const float& delta)
{
	// 如果粒子系统的时间已经归零,那么不再更新,也不会渲染,并且清空所有粒子
	if (_duration <= 0)
	{
		_visible = false;
		Clear();
		return;
	}

	if (_launchDuration <= 0)
	{
		_launchEnable = false;
	}

	// 如果当前粒子数量少于最大值,那么发射粒子
	if (m_particle_list.size() <= _maxParticleNums && _launchEnable)
	{
		_tempInterval += delta;

		if (_tempInterval >= _launchInterval)
		{
			int num = 0;

			if (_launchInterval >= 0.001f)
			{
				num = _tempInterval / _launchInterval;
			}
			else
			{
				num = 1;
			}

			for (int i = 0; i < num; ++i)
			{
				_AutoPush();
			}
			
			_tempInterval = 0;
		}
	}

	// 如果粒子无效了或者超出范围了,那么删除这个粒子
	list<Particle*>::iterator particleIte = m_particle_list.begin();
	while (particleIte != m_particle_list.end())
	{
		if ((*particleIte)->IsVisible() == false ||
			(*particleIte)->GetPositionX() < GetPositionX() + _boundBoxPositionX ||
			(*particleIte)->GetPositionX() > GetPositionX() + _boundBoxPositionX + _boundBoxWidth ||
			(*particleIte)->GetPositionY() < GetPositionY() + _boundBoxPositionY ||
			(*particleIte)->GetPositionY() > GetPositionY() + _boundBoxPositionY + _boundBoxHeight)
		{
			(*particleIte)->Release();
			particleIte = m_particle_list.erase(particleIte);
			//particleIte = m_particle_list.begin();
		}
		else
		{
			++particleIte;
		}
	}

	// 更新粒子数据
	particleIte = m_particle_list.begin();
	while (particleIte != m_particle_list.end())
	{
		(*particleIte)->Update(delta);

		++particleIte;
	}

	if (_launchDuration > 0)
	{
		_launchDuration -= delta;
	}
	_duration -= delta;
}

void ParticleSystem::Render()
{
	if (_visible == false)
	{
		return;
	}

	list<Particle*>::iterator partileIte = m_particle_list.begin();
	while (partileIte != m_particle_list.end())
	{
		(*partileIte)->Render();

		++partileIte;
	}
}

void ParticleSystem::Clear()
{
	list<Particle*>::iterator partileIte = m_particle_list.begin();
	while (partileIte != m_particle_list.end())
	{
		(*partileIte)->Release();
		m_particle_list.erase(partileIte);
		partileIte = m_particle_list.begin();
	}
}

void ParticleSystem::SetPosition(
	const float& positionX,
	const float& positionY,
	const float& positionZ)
{
	SetPositionX(positionX);
	SetPositionY(positionY);
	SetPositionZ(positionZ);
}

void ParticleSystem::SetPosition(
	const float& positionX,
	const float& positionY)
{
	SetPositionX(positionX);
	SetPositionY(positionY);
}

void ParticleSystem::SetPositionX(
	const float& positionX)
{
	_positionX = positionX;
}

void ParticleSystem::SetPositionY(
	const float& positionY)
{
	_positionY = positionY;
}

void ParticleSystem::SetPositionZ(
	const float& positionZ)
{
	_positionZ = positionZ;
}

float ParticleSystem::GetPositionX() const
{
	return _positionX;
}

float ParticleSystem::GetPositionY() const
{
	return _positionY;
}

float ParticleSystem::GetPositionZ() const
{
	return _positionZ;
}

void ParticleSystem::SetMaxNums(const int& maxNums)
{
	_maxParticleNums = maxNums;
}

void ParticleSystem::SetBoundBox(
	const int& positionX,
	const int& positionY,
	const int& width,
	const int& height)
{
	_boundBoxPositionX = positionX;
	_boundBoxPositionY = positionY;
	_boundBoxWidth = width;
	_boundBoxHeight = height;
}

void ParticleSystem::SetDuration(
	const float& launcherDuration,
	const float& duration)
{
	_launchDuration = launcherDuration;
	_duration = duration;
}

void ParticleSystem::SetLaunchInterval(const float& interval)
{
	_launchInterval = interval;
}

bool ParticleSystem::IsLaunch() const
{
	return _launchEnable;
}

bool ParticleSystem::IsVisible() const
{
	return _visible;
}

void ParticleSystem::SetLaunch(bool enable)
{
	_launchEnable = enable;
}

void ParticleSystem::SetVisible(bool visible)
{
	_visible = visible;
}

void ParticleSystem::_AutoPush()
{
	Particle* particle = 0;

	int num = 0;

	if (m_texturePath_list.size() > 0)
	{
		num = rand() % m_texturePath_list.size();
		particle = Particle::Create(m_texturePath_list.at(num));
	}
	else
	{
		particle = Particle::Create();
	}

	float particleDurationOffset = rand() % (int)(_particleDurationOffset * 20 + 1) / 10.0f - _particleDurationOffset;
	float positionOffsetX = rand() % (int)(_positionOffsetX * 20 + 1) / 10.0f - _positionOffsetX;
	float positionOffsetY = rand() % (int)(_positionOffsetY * 20 + 1) / 10.0f - _positionOffsetY;
	float positionOffsetZ = rand() % (int)(_positionOffsetZ * 20 + 1) / 10.0f - _positionOffsetZ;
	float velocityOffsetX = rand() % (int)(_velocityOffsetX * 20 + 1) / 10.0f - _velocityOffsetX;
	float velocityOffsetY = rand() % (int)(_velocityOffsetY * 20 + 1) / 10.0f - _velocityOffsetY;
	float velocityOffsetZ = rand() % (int)(_velocityOffsetZ * 20 + 1) / 10.0f - _velocityOffsetZ;
	float accelerationOffsetX = rand() % (int)(_accelerationOffsetX * 20 + 1) / 10.0f - _accelerationOffsetX;
	float accelerationOffsetY = rand() % (int)(_accelerationOffsetY * 20 + 1) / 10.0f - _accelerationOffsetY;
	float accelerationOffsetZ = rand() % (int)(_accelerationOffsetZ * 20 + 1) / 10.0f - _accelerationOffsetZ;
	float scaleOffset = rand() % (int)(_scaleOffset * 20 + 1) / 10.0f - _scaleOffset;
	float alpha = rand() % ((int)_alphaOffset + 1);
	float r = rand() % ((int)_rOffset + 1);
	float g = rand() % ((int)_gOffset + 1);
	float b = rand() % ((int)_bOffset + 1);

	particle->SetPosition(
		_positionX + positionOffsetX,
		_positionY + positionOffsetY,
		_positionZ + positionOffsetZ);
	if (alpha != 0 || r != 0 || g != 0 || b != 0)
	{
		particle->SetColor(D3DCOLOR_ARGB((byte)(_alpha + alpha), (byte)(_r + r), (byte)(_g + g), (byte)(_b + b)));
	}
	particle->SetVelocity(
		_velocityX + velocityOffsetX,
		_velocityY + velocityOffsetY,
		_velocityZ + velocityOffsetZ);
	particle->SetAcceleration(
		_accelerationX + accelerationOffsetX,
		_accelerationY + accelerationOffsetY,
		_accelerationZ + accelerationOffsetZ);
	particle->SetDuration(_particleDuration + particleDurationOffset);
	particle->SetScale(_scale + scaleOffset);
	particle->SetTextureBlend(_textureBlend);

	m_particle_list.push_back(particle);
}
