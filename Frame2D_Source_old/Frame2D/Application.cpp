#include "Application.h"
#include "Frame2D.h"

USING_NS_F2D;

static Application* pInstance = 0;

Application* Application::getInstance()
{
	if (pInstance == 0)
	{
		pInstance = new Application();
	}

	return pInstance;
}

void Application::SetWindowStyle(
	bool bWindow,
	const string& title,
	const int& width,
	const int& height,
	const int& x,
	const int& y)
{
	_bWindow = bWindow;
	_title = title;
	_width = width;
	_height = height;
	_x = x;
	_y = y;
}

void Application::startSystem(HINSTANCE hInstance)
{
	// ���ڹ���������
	WindowManager::getInstance()->startUp(hInstance, _title, _width, _height, _x, _y);
	// ��Ⱦ����������
	D3DManager::getInstance()->startUp(WindowManager::getInstance()->getHWND(), _bWindow);
	
#ifdef _AUDIO_MANAGER_H_H_
	// ��Ƶ����������
	AudioManager::getInstance()->startUp();
#endif

	_bStart = true;
}

void Application::startScene(Scene* scene)
{
	// Director��ӳ���
	Director::getInstance()->PushScene(scene);
}

int Application::Run()
{
	DWORD endTime = timeGetTime();
	float intervalTime = 0;
	int fpsCount = 0;
	float fpsTime = 0;

	WindowManager* windowManager = WindowManager::getInstance();
#ifdef _AUDIO_MANAGER_H_H_
	AudioManager* audioManager = AudioManager::getInstance();
#endif
	D3DManager* d3dManager = D3DManager::getInstance();
	Director* director = Director::getInstance();
	EventDispatcher* eventDispatcher = EventDispatcher::getInstance();

	while (true)
	{
		// ����ﵽ���õļ��ʱ������л���
		if (timeGetTime() - endTime >= _interval)
		{
			// ����running
			if (windowManager->Update(intervalTime) == false) break;
#ifdef _AUDIO_MANAGER_H_H_
			// ��Ƶrunning
			audioManager->Update(intervalTime);
#endif
			// ʱ��ַ���������Ϣ
			eventDispatcher->Notify(windowManager->getMSG());
			// �����һ֡����Ϣ
			windowManager->ClearMsg();
			// D3D running begin
			d3dManager->BeginDraw();
			if (_pause == false)
			{
				// Director running
				director->Update(intervalTime);
				// D3D running end
				d3dManager->EndDraw();
			}

			DWORD tempTime = timeGetTime();
			// ��һ֡����,��ü����ʱ��(����ת������)
			intervalTime = (tempTime - endTime) / 1000.0f;
			// �µ�һ֡��ʼ,������ʼʱ��
			endTime = tempTime;

			// ��ʼ����,��1֡
			fpsCount++;
			// �ۼ�ʱ��
			fpsTime += intervalTime;
			// �ۼƵ�ʱ�䳬��1����ʼ����fps
			if (fpsTime >= 1.0f)
			{
				// ���ۼƵ�fps����ʱ��õ�1��fps��ƽ��ֵ
				_fps = fpsCount / fpsTime;
				// �ۼƱ�������
				fpsCount = 0;
				fpsTime = 0;
			}
		}
	}

	// �¼��ַ����ͷ�
	eventDispatcher->Release();
	// Directorֹͣ
	director->Release();
#ifdef _AUDIO_MANAGER_H_H_
	// ��Ƶ������ֹͣ
	audioManager->shutDown();
#endif
	// ��Ⱦ������ֹͣ
	d3dManager->shutDown();
	// ���ڹ�����ֹͣ
	windowManager->shutDown();

	return 0;
}

float Application::GetFPS() const
{
	return _fps;
}

void Application::SetInterval(const DWORD& interval)
{
	this->_interval = interval;
}

bool Application::IsPause() const
{
	return _pause;
}

void Application::SetPause(bool bPause)
{
	_pause = bPause;
}

void Application::ExitApplication()
{
	WindowManager::getInstance()->SetQuitMsg();
}
