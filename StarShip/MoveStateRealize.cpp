#include "MoveStateRealize.h"
#include "Plane.h"

void MoveStateOnward::Update(const float& delta)
{
}

void MoveStateCircleL::Update(const float& delta)
{
	_plane->SetDirectionAngle(_plane->GetDirectionAngle() - _angle);

	_angle += 1;

	if (_angle > 360)
	{
		_angle -= 360;
	}

	_plane->SetDirectionAngle(_plane->GetDirectionAngle() + _angle);
}

void MoveStateCircleR::Update(const float& delta)
{
	_plane->SetDirectionAngle(_plane->GetDirectionAngle() + _angle);

	_angle += 1;

	if (_angle > 360)
	{
		_angle -= 360;
	}

	_plane->SetDirectionAngle(_plane->GetDirectionAngle() - _angle);
}

void MoveStateBack::Update(const float& delta)
{
	if (_bSave == false)
	{
		_beginAngle = _plane->GetDirectionAngle();

		_bSave = true;
	}

	if (_backTime > 0)
	{
		_backTime -= delta;

		if (_backTime <= 0)
		{
			_plane->SetDirectionAngle(180 - _beginAngle);
		}
	}
}

void MoveStateWander::Update(const float& delta)
{

}