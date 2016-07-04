#include "MainScene.h"
#include "BulletLauncherRealize.h"
#include "BulletManager.h"
#include "Own.h"
#include "Enemy.h"
#include "Tools.h"
#include "Bullet.h"
#include "Enemy.h"
#include "PlaneManager.h"
#include "StageManager.h"
#include "EffectManager.h"
#include "ItemManager.h"
#include "Effect.h"
#include "Item.h"
#include "UserManager.h"

MainScene* MainScene::Create()
{
	MainScene* scene = new MainScene();
	scene->Init();

	return scene;
}

MainScene::~MainScene()
{
	
}

bool MainScene::Init()
{
	// ����û�
	UserManager* userMgr = UserManager::getInstance();
	// �����ӵ�ϵͳ
	BulletManager::getInstance()->startUp("Data/bulletConfig.lua");
	// ��������ϵͳ
	ItemManager::getInstance()->startUp("Data/itemConfig.lua");
	// �����ɻ�ϵͳ
	PlaneManager::getInstance()->startUp("Data/planeConfig.lua");
	// ������Чϵͳ
	EffectManager::getInstance()->startUp("Data/effectConfig.lua");

	// �����������z��λ��
	Camera::getInstance()->SetCameraPosition(0, 0, -600);

	// ������Ч
	AudioManager* audioMgr = AudioManager::getInstance();
	audioMgr->loadSoundForCache("Sound/se/beiji.ogg");
	audioMgr->loadSoundForCache("Sound/se/boom.mp3");
	audioMgr->loadSoundForCache("Sound/se/fly.ogg");
	audioMgr->loadSoundForCache("Sound/se/get_item.mp3");
	audioMgr->loadSoundForCache("Sound/se/missile.mp3");
	audioMgr->loadSoundForCache("Sound/se/own_shoot1.ogg");
	audioMgr->loadSoundForCache("Sound/se/own_shoot2.mp3");
	audioMgr->loadSoundForCache("Sound/se/own_shoot3.ogg");
	audioMgr->loadSoundForCache("Sound/se/se_warning.ogg");

	// ��ʼ�����Ƿɻ�
	_own = Own::Create(userMgr->GetOwn());
	_own->SetPosition(0, -150, 0);
	Add(_own, LAYER_PLAYER);

	// ����
	_scoreText = TextSprite::Create("SCORE:0", "΢���ź�", 16);
	Add(_scoreText);

	// �����ؿ�ϵͳ
	StageManager::getInstance()->startUp("Data/stage" + to_string(userMgr->GetStage()) + ".lua", this);

	// �������ݸ��º���
	AddUpdateFunc(UpdateFunc::Create(CALLBACK_PARAMETER_1(MainScene::UpdateData, this)));
	EventDispatcher::getInstance()->Add(
		KeyboardListener::Create(
		this, KeyboardFunc::Create(
		CALLBACK_PARAMETER_2(MainScene::onkey, this))));

	return true;
}

void MainScene::UpdateData(const float& delta)
{
	// �ؿ����ݸ���
	StageManager::getInstance()->Update(delta);

	vector<Element*> list = GetElementList();
	for (int i = 0; i < list.size(); ++i)
	{
		list.at(i)->SetPositionZ(-list.at(i)->GetOrder() * 2);

		if (list.at(i)->GetOrder() == LAYER_PLAYER_BULLET ||
			list.at(i)->GetOrder() == LAYER_ENEMY_BULLET)
		{
			RECT viewRect = Director::getInstance()->GetViewRect();
			D3DXVECTOR3 viewPos = Camera::getInstance()->GetViewPosition();
			if (Tools::CheckHit_UnInclude(list.at(i),
				viewPos.x - viewRect.right / 2.0f,
				viewPos.y - viewRect.bottom / 2.0f,
				viewPos.x + viewRect.right / 2.0f,
				viewPos.y + viewRect.bottom / 2.0f))
			{
				list.at(i)->SetVisible(false);
			}
		}
		else if (list.at(i)->GetOrder() == LAYER_ENEMY_1 ||
			list.at(i)->GetOrder() == LAYER_ENEMY_2 ||
			list.at(i)->GetOrder() == LAYER_ENEMY_3)
		{
			RECT viewRect = Director::getInstance()->GetViewRect();
			D3DXVECTOR3 viewPos = Camera::getInstance()->GetViewPosition();
			if (list.at(i)->GetPositionY() + (0.5f - list.at(i)->GetAnchorY()) * list.at(i)->GetHeight() <
				viewPos.y + viewRect.bottom / 2.0f &&
				list.at(i)->GetPositionY() - (0.5f - list.at(i)->GetAnchorY()) * list.at(i)->GetHeight() >
				viewPos.y - viewRect.bottom / 2.0f)
			{
				for (int j = 0; j < list.size(); ++j)
				{
					if (list.at(j)->GetOrder() == LAYER_PLAYER_BULLET)
					{
						if (Tools::CheckHit_Circle(list.at(j), list.at(i)) && ((Enemy*)list.at(i))->GetHp() > 0)
						{
							Bullet* bullet = (Bullet*)list.at(j);
							if (bullet->IsCross() == false)
							{
								bullet->Die();
							}
							Enemy* enemy = (Enemy*)list.at(i);
							enemy->SetHp(enemy->GetHp() - bullet->GetAttack());
							enemy->SetBruiseEnable(true);
							
							if (enemy->GetHp() <= 0)
							{
								enemy->Die();
								//��������
								UserManager* userMgr = UserManager::getInstance();
								userMgr->SetScore(userMgr->GetScore() + enemy->GetScore());
								enemy->SetScore(0);
								_scoreText->SetText("SCORE:" + to_string(userMgr->GetScore()));

								if (enemy->GetName().substr(0, 4).compare("boss") == 0)
								{
									if (userMgr->GetStage() < userMgr->GetStageMax())
									{
										userMgr->SetStage(userMgr->GetStage() + 1);
										if (_black == 0)
										{
											_black = Sprite::Create("Res/Login/black.png");
											_black->SetScale(500);
											Add(_black);
											ClearUpdateFunc();
											AddUpdateFunc(UpdateFunc::Create(CALLBACK_PARAMETER_1(MainScene::Fade, this)));
											AudioManager::getInstance()->stopBGM();
											AudioManager::getInstance()->playSoundEffect("Sound/se/clear.mp3");
											return;
										}
									}
									else
									{

									}
								}
							}
							else
							{
								Effect* boom = Effect::Create("fire1");
								boom->SetTextureBlend(true);
								boom->SetPosition(bullet->GetPositionX(), bullet->GetPositionY(), bullet->GetPositionZ());
								boom->SetOrder(LAYER_ENEMY_BOOM);
								Add(boom);
								AudioManager::getInstance()->playSoundEffect("Sound/se/beiji.ogg");
							}
						}
					}
				}
			}
			else if (Tools::CheckHit_UnInclude(list.at(i),
				viewPos.x - viewRect.right / 2.0f - 300,
				viewPos.y - viewRect.bottom / 2.0f - 300,
				viewPos.x + viewRect.right / 2.0f + 300,
				viewPos.y + viewRect.bottom / 2.0f + 300))
			{
				list.at(i)->SetVisible(false);
			}
		}
		else if (list.at(i)->GetOrder() == LAYER_PLAYER)
		{
			for (int j = 0; j < list.size(); ++j)
			{
				if (list.at(j)->GetOrder() == LAYER_ENEMY_BULLET)
				{
					if (Tools::CheckHit_Point(list.at(j), list.at(i)))
					{
						Bullet* bullet = (Bullet*)list.at(j);
						if (bullet->IsCross() == false)
						{
							bullet->Die();
						}
						Own* own = (Own*)list.at(i);
						if (own->GetBulletLevel() > 1)
						{
							if (rand() % 2 == 1)
							{
								own->SetBulletLevel(own->GetBulletLevel() - 1);
							}
						}
						else
						{
							own->SetHp(own->GetHp() - bullet->GetAttack());
						}
						own->SetBruiseEnable(true);
						if (own->GetHp() <= 0)
						{
							//Director::getInstance()->SetPause(true);
						}
					}
				}
				else if (list.at(j)->GetOrder() == LAYER_ITEM)
				{
					if (Tools::CheckHit_Circle(list.at(j), list.at(i)))
					{
						Own* own = (Own*)list.at(i);
						Item* item = (Item*)list.at(j);
						own->UseItem(item);
						item->SetVisible(false);
						AudioManager::getInstance()->playSoundEffect("Sound/se/get_item.mp3");
					}
				}
			}
		}
	}
}

void MainScene::Fade(const float& delta)
{
	if (_fade < 255)
	{
		_fade += 3;

		_black->SetAlpha(_fade);
		_black->ResetVertex();

		if (_fade >= 255)
		{
			// �ͷŻ�������
			AudioManager::getInstance()->ClearCache();
			TextureCache::getInstance()->ClearTextureCache();

			// ���������ĵ���ֹͣ��ϵͳ
			StageManager::getInstance()->shutDown();
			EffectManager::getInstance()->shutDown();
			PlaneManager::getInstance()->shutDown();
			ItemManager::getInstance()->shutDown();
			BulletManager::getInstance()->shutDown();
			Director::getInstance()->ReplaceScene(MainScene::Create());
		}
	}
}

void MainScene::onkey(const ENUM_F2D_MESSAGE& msg, const ENUM_F2D_KEYCODE& code)
{
	static bool bUp = false;
	static bool bDown = false;
	static bool bLeft = false;
	static bool bRight = false;

	if (msg == F2D_MESSAGE_KEYDOWN)
	{
		if (code == F2D_KEYCODE_J)
		{
			_own->SetShootEnable(true);
		}

		if (code == F2D_KEYCODE_W)
		{
			bUp = true;
		}
		if (code == F2D_KEYCODE_S)
		{
			bDown = true;
		}
		if (code == F2D_KEYCODE_A)
		{
			bLeft = true;
		}
		if (code == F2D_KEYCODE_D)
		{
			bRight = true;
		}
	}

	if (msg == F2D_MESSAGE_KEYUP)
	{
		if (code == F2D_KEYCODE_J)
		{
			_own->SetShootEnable(false);
		}
		if (code == F2D_KEYCODE_W)
		{
			bUp = false;
		}
		if (code == F2D_KEYCODE_S)
		{
			bDown = false;
		}
		if (code == F2D_KEYCODE_A)
		{
			bLeft = false;
		}
		if (code == F2D_KEYCODE_D)
		{
			bRight = false;
		}
	}

	RECT viewRect = Director::getInstance()->GetViewRect();
	D3DXVECTOR3 viewPos = Camera::getInstance()->GetViewPosition();

	float bx = _own->GetPositionX() + (0.5f - _own->GetAnchorX()) * _own->GetWidth();
	float by = _own->GetPositionY() + (0.5f - _own->GetAnchorY()) * _own->GetHeight();

	if (bx - _own->GetWidth() / 2.0f < viewPos.x - viewRect.right / 2.0f + 10)
	{
		bLeft = false;
	}

	if (bx + _own->GetWidth() / 2.0f > viewPos.x + viewRect.right / 2.0f - 10)
	{
		bRight = false;
	}

	if (by + _own->GetHeight() / 2.0f > viewPos.y + viewRect.bottom / 2.0f - 10)
	{
		bUp = false;
	}

	if (by - _own->GetHeight() / 2.0f < viewPos.y - viewRect.bottom / 2.0f + 10)
	{
		bDown = false;
	}

	_own->SetMoveEnable(bUp || bDown || bLeft || bRight);

	if (bLeft)
	{
		_own->SetDirectionAngle(90);
	}
	if (bRight)
	{
		_own->SetDirectionAngle(270);
	}

	if (bUp)
	{
		_own->SetDirectionAngle(0);
		if (bLeft)
		{
			_own->SetDirectionAngle(45);
		}
		if (bRight)
		{
			_own->SetDirectionAngle(-45);
		}
	}

	if (bDown)
	{
		_own->SetDirectionAngle(180);
		if (bLeft)
		{
			_own->SetDirectionAngle(180 - 45);
		}
		if (bRight)
		{
			_own->SetDirectionAngle(180 + 45);
		}
	}
}
