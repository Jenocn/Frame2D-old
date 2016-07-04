#include "GameMap.h"

USING_NS_F2D

GameMap* GameMap::Create(const string& path, const int& layer)
{
	GameMap* map = new (nothrow) GameMap();

	if (map && map->InitData(path))
	{
		map->SetOrder(layer);
		return map;
	}

	return 0;
}

bool GameMap::InitData(const string& path)
{
	_background = Sprite::Create(path);
	_tempBackground = Sprite::Create(path);

	_background->SetPositionY(0);
	_tempBackground->SetPositionY(
		_background->GetPositionY() +
		_background->GetHeight());

	_background->SetOrder(GetOrder());
	_tempBackground->SetOrder(GetOrder());

	Add(_background);
	Add(_tempBackground);

	return true;
}

void GameMap::Update(const float& delta)
{
	SpriteGroup::Update(delta);

	RECT viewRect = Director::getInstance()->GetViewRect();
	D3DXVECTOR3 viewPos = Camera::getInstance()->GetViewPosition();

	if (_background->GetPositionY() <
		viewPos.y - viewRect.bottom / 2.0f - _background->GetHeight() / 2.0f)
	{
		_background->SetPositionY(
			_tempBackground->GetPositionY() +
			_tempBackground->GetHeight() / 2.0f +
			_background->GetHeight() / 2.0f);
	}

	if (_tempBackground->GetPositionY() <
		viewPos.y - viewRect.bottom / 2.0f - _tempBackground->GetHeight() / 2.0f)
	{
		_tempBackground->SetPositionY(
			_background->GetPositionY() +
			_background->GetHeight() / 2.0f +
			_tempBackground->GetHeight() / 2.0f);
	}

	_background->SetPositionY(
		_background->GetPositionY() - _scrollSpeed);

	_tempBackground->SetPositionY(
		_tempBackground->GetPositionY() - _scrollSpeed);
}

void GameMap::SetScrollSpeed(const float& speed)
{
	_scrollSpeed = speed;
}

float GameMap::GetScrollSpeed() const
{
	return _scrollSpeed;
}