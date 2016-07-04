#ifndef _MAIN_SCENE_H_H_
#define _MAIN_SCENE_H_H_

#include <Frame2D.h>

class Own;

class MainScene : public Frame2D::Scene
{
public:
	static MainScene* Create();

	~MainScene();

	bool Init();

	void UpdateData(const float& delta);

	void Fade(const float& delta);

	void onkey(const Frame2D::ENUM_F2D_MESSAGE& msg, const Frame2D::ENUM_F2D_KEYCODE& code);

private:
	MainScene()
		: _own(0)
		, _scoreText(0)
		, _black(0)
		, _fade(0)
	{}

private:
	Own* _own;
	Frame2D::TextSprite* _scoreText;
	Frame2D::Sprite* _black;
	float _fade;
};

#endif