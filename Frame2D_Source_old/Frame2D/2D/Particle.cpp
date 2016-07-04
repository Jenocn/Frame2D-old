#include "Particle.h"

USING_NS_F2D

Particle* Particle::Create()
{
	Particle* particle = new (nothrow)Particle();

	assert(particle && particle->Init() && "Particle Create Failed!");

	return particle;
}

Particle* Particle::Create(const string& path, const D3DCOLOR& colorKey)
{
	Particle* particle = new (nothrow)Particle();

	assert(particle && particle->InitWithFile(path, colorKey) && "Particle Create Failed!");

	return particle;
}

bool Particle::Init()
{
	_pointSprite = DxPoint::CreateWithInit();

	return true;
}

bool Particle::InitWithFile(const string& path, const D3DCOLOR& colorKey)
{
	_pointSprite = DxPoint::CreateWithInit(path, colorKey);

	return true;
}

Particle::~Particle()
{

}

void Particle::Update(const float& delta)
{
	if (_duration <= 0)
	{
		_visible = false;
		return;
	}

	// 求出当前时间间隔在一秒里的百分比
	float percent = delta / 1.0f;

	_velocityX = _velocityX + _accelerationX * percent;
	_velocityY = _velocityY + _accelerationY * percent;
	_velocityZ = _velocityZ + _accelerationZ * percent;
	_positionX = _positionX + _velocityX * percent;
	_positionY = _positionY + _velocityY * percent;
	_positionZ = _positionZ + _velocityZ * percent;

	_duration -= delta;
}

void Particle::Render()
{
	if (_visible == false)
	{
		return;
	}

	_pointSprite->Draw(
		_positionX,
		_positionY,
		_positionZ,
		_scale, _textureBlend);
}

void Particle::Release()
{
	if (_pointSprite)
	{
		_pointSprite->Release();
	}

	delete this;
}

void Particle::SetVisible(bool visible)
{
	_visible = visible;
}

bool Particle::IsVisible()
{
	return _visible;
}

void Particle::SetPosition(
	const float& positionX,
	const float& positionY)
{
	SetPositionX(positionX);
	SetPositionY(positionY);
}

void Particle::SetPosition(
	const float& positionX,
	const float& positionY,
	const float& positionZ)
{
	SetPositionX(positionX);
	SetPositionY(positionY);
	SetPositionZ(positionZ);
}

void Particle::SetPositionX(const float& positionX)
{
	_positionX = positionX;
}

void Particle::SetPositionY(const float& positionY)
{
	_positionY = positionY;
}

void Particle::SetPositionZ(const float& positionZ)
{
	_positionZ = positionZ;
}

void Particle::SetColor(byte r, byte g, byte b)
{
	SetColor(D3DCOLOR_XRGB(r, g, b));
}

void Particle::SetColor(const D3DCOLOR& color)
{
	_alpha = (byte)(color >> 24);
	_r = (byte)(color >> 16);
	_g = (byte)(color >> 8);
	_b = (byte)color;
	_pointSprite->SetColor(color);
	_pointSprite->ResetVertex();
}

void Particle::SetAlpha(byte alpha)
{
	SetColor(GetColor() & D3DCOLOR_ARGB(alpha, 255, 255, 255));
}

void Particle::SetColorR(byte r)
{
	SetColor(GetColor() & D3DCOLOR_ARGB(255, r, 255, 255));
}

void Particle::SetColorG(byte g)
{
	SetColor(GetColor() & D3DCOLOR_ARGB(255, 255, g, 255));
}

void Particle::SetColorB(byte b)
{
	SetColor(GetColor() & D3DCOLOR_ARGB(255, 255, 255, b));
}

void Particle::SetVelocity(
	const float& x,
	const float& y)
{
	SetVelocityX(x);
	SetVelocityY(y);
}

void Particle::SetVelocity(
	const float& x,
	const float& y,
	const float& z)
{
	SetVelocityX(x);
	SetVelocityY(y);
	SetVelocityZ(z);
}

void Particle::SetVelocityX(const float& x)
{
	_velocityX = x;
}
void Particle::SetVelocityY(const float& y)
{
	_velocityY = y;
}
void Particle::SetVelocityZ(const float& z)
{
	_velocityZ = z;
}

void Particle::SetAcceleration(
	const float& x,
	const float& y)
{
	SetAccelerationX(x);
	SetAccelerationY(y);
}

void Particle::SetAcceleration(
	const float& x,
	const float& y,
	const float& z)
{
	SetAccelerationX(x);
	SetAccelerationY(y);
	SetAccelerationZ(z);
}

void Particle::SetAccelerationX(const float& x)
{
	_accelerationX = x;
}

void Particle::SetAccelerationY(const float& y)
{
	_accelerationY = y;
}

void Particle::SetAccelerationZ(const float& z)
{
	_accelerationZ = z;
}

void Particle::SetDuration(const float& duration)
{
	_duration = duration;
}

void Particle::SetScale(const float& scale)
{
	_scale = scale;
}

float Particle::GetPositionX() const
{
	return _positionX;
}

float Particle::GetPositionY() const
{
	return _positionY;
}

float Particle::GetPositionZ() const
{
	return _positionZ;
}

D3DCOLOR Particle::GetColor() const
{
	return D3DCOLOR_ARGB(_alpha, _r, _g, _b);
}

byte Particle::GetAlpha() const
{
	return _alpha;
}

byte Particle::GetColorR() const
{
	return _r;
}

byte Particle::GetColorG() const
{
	return _g;
}

byte Particle::GetColorB() const
{
	return _b;
}

float Particle::GetVelocityX() const
{
	return _velocityX;
}

float Particle::GetVelocityY() const
{
	return _velocityY;
}

float Particle::GetVelocityZ() const
{
	return _velocityZ;
}

float Particle::GetAccelerationX() const
{
	return _accelerationX;
}

float Particle::GetAccelerationY() const
{
	return _accelerationY;
}

float Particle::GetAccelerationZ() const
{
	return _accelerationZ;
}

float Particle::GetDuration() const
{
	return _duration;
}

float Particle::GetScale() const
{
	return _scale;
}

void Particle::SetTextureBlend(bool enable)
{
	_textureBlend = enable;
}

bool Particle::IsTextureBlend() const
{
	return _textureBlend;
}
