#ifndef _LOGIN_SCENE_H_H_
#define _LOGIN_SCENE_H_H_

#include <Frame2D.h>

class LoginScene : public Frame2D::Scene
{
public:
	static LoginScene* Create();

	virtual ~LoginScene();

	virtual bool Init();

	virtual void Update(const float& delta);

	void Fade(const float& delta);

	void onKeyboardPress(const Frame2D::ENUM_F2D_MESSAGE& msg, const Frame2D::ENUM_F2D_KEYCODE& code);

private:
	LoginScene()
		: _enter(0)
		, _logo(0)
		, _black(0)
		, _logoAlpha(0)
		, _enterAlpha(0)
		, _enterAlphaTemp(0)
		, _fade(0)
	{}

	LoginScene(LoginScene&);
	LoginScene& operator=(LoginScene&);

private:
	Frame2D::Sprite* _enter;
	Frame2D::Sprite* _logo;
	Frame2D::Sprite* _black;
	float _logoAlpha;
	float _enterAlpha;
	float _enterAlphaTemp;
	float _fade;
};

#endif