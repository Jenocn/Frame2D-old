#include "Effect.h"
#include "EffectManager.h"

Effect* Effect::Create(const string& name)
{
	Effect* effect = new (std::nothrow) Effect();

	if (effect && effect->InitData(name))
	{
		return effect;
	}

	return 0;
}

Effect::~Effect()
{

}

bool Effect::InitData(const string& name)
{
	EffectInfo* info = EffectManager::getInstance()->GetEffectInfo(name);

	if (false == InitWithFile(
		info->imgPath,
		D3DCOLOR_XRGB(
		info->colorKeyR,
		info->colorKeyG,
		info->colorKeyB)))
	{
		return false;
	}

	if (false == InitAnimation(
		info->row, info->col,
		info->interval, info->count))
	{
		return false;
	}

	SetDurationTime(info->duration);
	SetOffsetX(info->offsetX);
	SetOffsetY(info->offsetY);
	SetAngle(info->angleX, info->angleY, info->angleZ);
	SetTextureBlend(info->textureBlend);

	return true;
}

void Effect::Update(const float& delta)
{
	Animation::Update(delta);

	SetPosition(GetPositionX() + _offsetX, GetPositionY() + _offsetY);

	if (GetAnimationCount() == 0)
	{
		SetVisible(false);
	}

	if (GetAnimationCount() == -1)
	{
		_durationTime -= delta;

		if (_durationTime <= 0)
		{
			SetVisible(false);
		}
	}
}

void Effect::Render()
{
	Animation::Render();

	SetPosition(GetPositionX() - _offsetX, GetPositionY() - _offsetY);
}

void Effect::SetOffsetX(const float& x)
{
	_offsetX = x;
}

void Effect::SetOffsetY(const float& y)
{
	_offsetY = y;
}

void Effect::SetDurationTime(const float& duration)
{
	_durationTime = duration;
}

float Effect::GetOffsetX() const
{
	return _offsetX;
}

float Effect::GetOffsetY() const
{
	return _offsetY;
}

float Effect::GetDurationTime() const
{
	return _durationTime;
}
