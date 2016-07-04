#include "Tools.h"

bool Tools::CheckHit_Circle(Element* bullet, Element* plane)
{
	float bx = bullet->GetPositionX() + (0.5f - bullet->GetAnchorX()) * bullet->GetWidth();
	float by = bullet->GetPositionY() + (0.5f - bullet->GetAnchorY()) * bullet->GetHeight();
	float br = (bullet->GetWidth() + bullet->GetHeight()) / 4.0f;

	float px = plane->GetPositionX() + (0.5f - plane->GetAnchorX()) * plane->GetWidth();
	float py = plane->GetPositionY() + (0.5f - plane->GetAnchorY()) * plane->GetHeight();
	float pr = (plane->GetWidth() + plane->GetHeight()) / 4.0f;

	if ((px - bx) * (px - bx) + (py - by) * (py - by) <= (br + pr) * (br + pr))
	{
		return true;
	}

	return false;
}

bool Tools::CheckHit_Rectangle(Element* bullet, Element* plane)
{
	float bx = bullet->GetPositionX() + (0.5f - bullet->GetAnchorX()) * bullet->GetWidth();
	float by = bullet->GetPositionY() + (0.5f - bullet->GetAnchorY()) * bullet->GetHeight();

	float px = plane->GetPositionX() + (0.5f - plane->GetAnchorX()) * plane->GetWidth();
	float py = plane->GetPositionY() + (0.5f - plane->GetAnchorY()) * plane->GetHeight();

	if (px + plane->GetWidth() / 2.0f > bx - bullet->GetWidth() / 2.0f &&
		px - plane->GetWidth() / 2.0f < bx + bullet->GetWidth() / 2.0f)
	{
		if (py + plane->GetHeight() / 2.0f > by - bullet->GetHeight() / 2.0f &&
			py - plane->GetHeight() / 2.0f < by + bullet->GetHeight() / 2.0f)
		{

			return true;
		}
	}

	return false;
}

bool Tools::CheckHit_Point(Element* bullet, Element* plane)
{
	float bx = bullet->GetPositionX() + (0.5f - bullet->GetAnchorX()) * bullet->GetWidth();
	float by = bullet->GetPositionY() + (0.5f - bullet->GetAnchorY()) * bullet->GetHeight();

	float px = plane->GetPositionX() + (0.5f - plane->GetAnchorX()) * plane->GetWidth();
	float py = plane->GetPositionY() + (0.5f - plane->GetAnchorY()) * plane->GetHeight();

	if (px > bx - bullet->GetWidth() / 2.0f &&
		px < bx + bullet->GetWidth() / 2.0f)
	{
		if (py > by - bullet->GetHeight() / 2.0f &&
			py < by + bullet->GetHeight() / 2.0f)
		{
			return true;
		}
	}

	return false;
}

bool Tools::CheckHit_UnInclude(Element* e,
	const int& left, const int& top,
	const int& right, const int& bottom)
{
	float bx = e->GetPositionX() +(0.5f - e->GetAnchorX()) * e->GetWidth();
	float by = e->GetPositionY() + (0.5f - e->GetAnchorY()) * e->GetHeight();

	if (bx + e->GetWidth() / 2.0f < left ||
		bx - e->GetWidth() / 2.0f > right ||
		by + e->GetHeight() / 2.0f < top ||
		by - e->GetHeight() / 2.0f > bottom)
	{
		return true;
	}

	return false;
}
