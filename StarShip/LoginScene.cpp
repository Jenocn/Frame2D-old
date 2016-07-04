#include "LoginScene.h"
#include "UserManager.h"
#include "MainScene.h"

USING_NS_F2D

LoginScene* LoginScene::Create()
{
	LoginScene* scene = new (nothrow)LoginScene();

	if (scene && scene->Init())
	{
		return scene;
	}

	return 0;
}

LoginScene::~LoginScene()
{

}

bool LoginScene::Init()
{
	UserManager* userMgr = UserManager::getInstance();
	userMgr->SetLife(3);
	userMgr->SetScore(0);
	userMgr->SetOwn("own1");
	userMgr->SetStageMax(2);
	userMgr->SetStage(1);

	Sprite* background = Sprite::Create("Res/Login/bg.jpg");
	Add(background);

	_logo = Sprite::Create("Res/Login/logo.png");
	_logo->SetAlpha(0);
	_logo->ResetVertex();
	_logo->SetPositionY(Director::getInstance()->GetViewRect().bottom / 3.0f);
	Add(_logo);

	_enter = Sprite::Create("Res/Login/enter.png");
	_enter->SetPositionY(-Director::getInstance()->GetViewRect().bottom / 3.0f);
	Add(_enter);

	AudioManager::getInstance()->playBGM("Sound/bgm/login.ogg", SoundVolumeChange::Create(5, 1), 0);

	EventDispatcher::getInstance()->Add(
		KeyboardListener::Create(this, KeyboardFunc::Create(
		CALLBACK_PARAMETER_2(LoginScene::onKeyboardPress, this))));

	return true;
}

void LoginScene::Update(const float& delta)
{
	Scene::Update(delta);

	if (_logoAlpha < 255)
	{
		_logo->SetAlpha(_logoAlpha);
		_logo->ResetVertex();
		_logoAlpha += 5;
	}

	if (_enterAlpha == 0)
	{
		_enterAlphaTemp = 3;
	}

	if (_enterAlpha == 255)
	{
		_enterAlphaTemp = -3;
	}

	_enterAlpha += _enterAlphaTemp;

	_enter->SetAlpha(_enterAlpha);
	_enter->ResetVertex();

}

void LoginScene::Fade(const float& delta)
{
	if (_fade < 255)
	{
		_fade += 3;

		_black->SetAlpha(_fade);
		_black->ResetVertex();

		if (_fade >= 255)
		{
			AudioManager::getInstance()->ClearCache();
			TextureCache::getInstance()->ClearTextureCache();
			Director::getInstance()->ReplaceScene(MainScene::Create());
		}
	}
}

void LoginScene::onKeyboardPress(const Frame2D::ENUM_F2D_MESSAGE& msg, const Frame2D::ENUM_F2D_KEYCODE& code)
{
	if (msg == F2D_MESSAGE_KEYUP)
	{
		if (code == F2D_KEYCODE_J || code == F2D_KEYCODE_ENTER)
		{
			if (_black == 0)
			{
				AudioManager::getInstance()->playSoundEffect("Sound/se/enter.ogg");
				_black = Sprite::Create("Res/Login/black.png");
				_black->SetScale(500);
				Add(_black);
				AddUpdateFunc(UpdateFunc::Create(CALLBACK_PARAMETER_1(LoginScene::Fade, this)));
			}
		}
	}
}
