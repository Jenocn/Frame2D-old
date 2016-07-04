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
	// 窗口管理器启动
	WindowManager::getInstance()->startUp(hInstance, _title, _width, _height, _x, _y);
	// 渲染管理器启动
	D3DManager::getInstance()->startUp(WindowManager::getInstance()->getHWND(), _bWindow);
	
#ifdef _AUDIO_MANAGER_H_H_
	// 音频管理器启动
	AudioManager::getInstance()->startUp();
#endif

	_bStart = true;
}

void Application::startScene(Scene* scene)
{
	// Director添加场景
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
		// 如果达到设置的间隔时间则进行绘制
		if (timeGetTime() - endTime >= _interval)
		{
			// 窗口running
			if (windowManager->Update(intervalTime) == false) break;
#ifdef _AUDIO_MANAGER_H_H_
			// 音频running
			audioManager->Update(intervalTime);
#endif
			// 时间分发器更新消息
			eventDispatcher->Notify(windowManager->getMSG());
			// 清空这一帧的消息
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
			// 上一帧结束,获得间隔的时间(毫秒转换成秒)
			intervalTime = (tempTime - endTime) / 1000.0f;
			// 新的一帧开始,重置起始时间
			endTime = tempTime;

			// 开始绘制,加1帧
			fpsCount++;
			// 累计时间
			fpsTime += intervalTime;
			// 累计的时间超过1秒则开始计算fps
			if (fpsTime >= 1.0f)
			{
				// 用累计的fps除以时间得到1秒fps的平均值
				_fps = fpsCount / fpsTime;
				// 累计变量清零
				fpsCount = 0;
				fpsTime = 0;
			}
		}
	}

	// 事件分发器释放
	eventDispatcher->Release();
	// Director停止
	director->Release();
#ifdef _AUDIO_MANAGER_H_H_
	// 音频管理器停止
	audioManager->shutDown();
#endif
	// 渲染管理器停止
	d3dManager->shutDown();
	// 窗口管理器停止
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
