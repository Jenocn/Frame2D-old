#include "Animation.h"

USING_NS_F2D

Animation* Animation::Create(const string& path,
	const int& row, const int& col,
	const float& animationInterval,
	const int& count,
	const DWORD& colorKey)
{
	Animation* animation = new (nothrow)Animation();

	assert(animation &&
		animation->InitWithFile(path, colorKey) &&
	  "Animation Create Failed!");

	assert(animation->InitAnimation(
		row, col, animationInterval, count) &&
	 "Animation Create Failed!");

	return animation;
}

Animation::~Animation()
{

}

bool Animation::InitAnimation(const int& row, const int& col,
	const float& animationInterval, const int& count)
{
	_row = row;
	_col = col;
	_animationInterval = animationInterval;
	_count = count;

	ResetAnimation();

	return true;
}

void Animation::Update(const float& delta)
{
	Sprite::Update(delta);

	if (_pause == false && _count != 0)
	{
		SetRenderRect(
			_framePosX * (GetTextureWidth() / _col),
			_framePosY * (GetTextureHeight() / _row),
			_framePosX * GetTextureWidth() / _col + GetTextureWidth() / _col,
			_framePosY * GetTextureHeight() / _row + GetTextureHeight() / _row);
		ResetVertex();

		if (_tempInterval >= _animationInterval)
		{
			if (_framePosX < _col - 1)
			{
				++_framePosX;
			}
			else
			{
				_framePosX = 0;

				if (_framePosY < _row - 1)
				{
					++_framePosY;
				}
				else
				{
					_framePosY = 0;

					if (_count != -1)
					{
						--_count;
					}
				}
			}

			_tempInterval = 0;
		}

		_tempInterval += delta;
	}
}

void Animation::SetAnimationInterval(const float& second)
{
	_animationInterval = second;

	if (_animationInterval < 0)
	{
		_animationInterval = 0;
	}
}

void Animation::PauseAnimation()
{
	_pause = true;
}

void Animation::PlayAnimation()
{
	_pause = false;
}

bool Animation::IsPause() const
{
	return _pause;
}

void Animation::ResetAnimation()
{
	_framePosX = 0;
	_framePosY = 0;
	SetRenderRect(0, 0, GetTextureWidth() / _col, GetTextureHeight() / _row);
	SetWidth(GetTextureWidth() / _col);
	SetHeight(GetTextureHeight() / _row);

	ResetVertex();
}

void Animation::SetAnimationCount(const int& count)
{
	_count = count;

	if (_count < -1)
	{
		_count = -1;
	}
}

int Animation::GetFrameX() const
{
	return _framePosX;
}

int Animation::GetFrameY() const
{
	return _framePosY;
}

int Animation::GetAnimationCount() const
{
	return _count;
}

