#include "ActionRealize.h"
#include "Element.h"

USING_NS_F2D

/////////////////////
// Jump
/////////////////////
Jump* Jump::Create(const float& duration,
	const float& height)
{
	Jump* jump = new (nothrow)Jump();
	assert(jump && jump->InitJump(duration, height) && "Jump Create Failed!");

	return jump;
}

Jump::~Jump()
{}

void Jump::Init()
{
	_startPosY = _element->GetPositionY();
	_speed = _height / _duration * 2.0f;
}

bool Jump::InitJump(const float& duration,
	const float& height)
{
	_duration = duration;
	_height = height;

	return true;
}

void Jump::Update(const float& delta)
{
	if (IsFinish())
	{
		return;
	}

	if (_bTop == false)
	{
		_element->SetPositionY(
			_element->GetPositionY() + _speed * (delta / 1.0f));

		if (_height > 0)
		{
			if (_element->GetPositionY() > _startPosY + _height)
			{
				_element->SetPositionY(_startPosY + _height);
				_bTop = true;
			}
		}
		else
		{
			if (_element->GetPositionY() < _startPosY + _height)
			{
				_element->SetPositionY(_startPosY + _height);
				_bTop = true;
			}
		}
	}
	else
	{
		_element->SetPositionY(
			_element->GetPositionY() - _speed * (delta / 1.0f));

		if (_height > 0)
		{
			if (_element->GetPositionY() < _startPosY)
			{
				_element->SetPositionY(_startPosY);
				_finish = true;
				return;
			}
		}
		else
		{
			if (_element->GetPositionY() > _startPosY)
			{
				_element->SetPositionY(_startPosY);
				_finish = true;
				return;
			}
		}
	}
}


//////////////////
// Move
//////////////////
Move* Move::Create(const float& duration,
	const float& positionX,
	const float& positionY)
{
	Move* move = new Move();
	assert(move && move->InitMove(duration, positionX, positionY) &&
		"Move Create Failed!");

	return move;
}

Move::~Move()
{

}

void Move::Init()
{
	_speedX = (_positionX - _element->GetPositionX()) / _duration;
	_speedY = (_positionY - _element->GetPositionY()) / _duration;
}

bool Move::InitMove(const float& duration,
	const float& positionX,
	const float& positionY)
{
	_duration = duration;
	_positionX = positionX;
	_positionY = positionY;

	return true;
}

void Move::Update(const float& delta)
{
	if (IsFinish())
	{
		return;
	}

	_element->SetPositionX(
		_element->GetPositionX() + _speedX * (delta / 1.0f));
	_element->SetPositionY(
		_element->GetPositionY() + _speedY * (delta / 1.0f));

	if (_speedX > 0)
	{
		if (_element->GetPositionX()> _positionX)
		{
			_element->SetPositionX(_positionX);
			_speedX = 0;
		}
	}
	else if (_speedX < 0)
	{
		if (_element->GetPositionX() < _positionX)
		{
			_element->SetPositionX(_positionX);
			_speedX = 0;
		}
	}

	if (_speedY > 0)
	{
		if (_element->GetPositionY() > _positionY)
		{
			_element->SetPositionY(_positionY);
			_speedY = 0;
		}
	}
	else if (_speedY < 0)
	{
		if (_element->GetPositionY() < _positionY)
		{
			_element->SetPositionY(_positionY);
			_speedY = 0;
		}
	}

	if ((_speedX == 0) && (_speedY == 0))
	{
		_finish = true;
	}
}


