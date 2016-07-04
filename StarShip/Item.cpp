#include "Item.h"
#include "ItemManager.h"

USING_NS_F2D

Item* Item::Create(const int& itemID)
{
	Item* item = new (nothrow) Item();

	if (item && item->InitData(itemID))
	{
		return item;
	}

	return 0;
}

Item::~Item()
{

}

bool Item::InitData(const int& itemID)
{
	ItemInfo* info = ItemManager::getInstance()->GetItemInfo(itemID);

	if (false == InitWithFile(info->imgPath))
	{
		return false;
	}

	SetID(itemID);

	return true;
}

void Item::Update(const float& delta)
{
	Sprite::Update(delta);

	SetPositionY(GetPositionY() - 2);

	if (_changeTime < 0.5)
	{
		_changeTime += delta;

		SetPositionX(GetPositionX() + _changeTime * 2.0f);

		if (_bChange == false)
		{
			SetColor(D3DCOLOR_XRGB(32, 32, 32));
			ResetVertex();
			_bChange = true;
		}
	}
	else if(_changeTime < 1)
	{
		_changeTime += delta;

		SetPositionX(GetPositionX() - (_changeTime - 0.5) * 2.0f);

		if (_bChange == true)
		{
			SetColor(D3DCOLOR_XRGB(255, 255, 255));
			ResetVertex();
			_bChange = false;
		}
	}
	else
	{
		_changeTime = 0;
	}
}

void Item::Render()
{
	Sprite::Render();
}
