#ifndef _GAME_MAP_H_H_
#define _GAME_MAP_H_H_

#include <Frame2D.h>

class GameMap : public Frame2D::SpriteGroup
{
public:
	static GameMap* Create(const string& path, const int& layer);

	bool InitData(const string& path);

	void Update(const float& delta);

	// setter
	void SetScrollSpeed(const float& speed);

	// getter
	float GetScrollSpeed() const;

protected:
	GameMap()
	{}

private:
	GameMap(GameMap&);
	GameMap& operator=(GameMap&);

private:
	Frame2D::Sprite* _background;
	Frame2D::Sprite* _tempBackground;

	float _scrollSpeed;
};

#endif