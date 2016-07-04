#ifndef _APPLICATION_H_H_
#define _APPLICATION_H_H_

#include "_Use.h"
#include "F2DEnum.h"
#include "F2DMacros.h"

NS_F2D_BEGIN

class Scene;

class Application
{
public:
	static Application* getInstance();

	/*
	函数功能:设置窗口类型
	参数1:是否窗口模式,设置为全屏模式后宽高和坐标设置将无效(true为窗口模式,false为全屏模式)
	参数2:程序标题名称
	参数3~4:分辨率宽高
	参数5~6:左上角坐标
	*/
	void SetWindowStyle(
		bool bWindow,
		const string& title,
		const int& width = WindowManager::DEFAULT,
		const int& height = WindowManager::DEFAULT,
		const int& x = WindowManager::DEFAULT,
		const int& y = WindowManager::DEFAULT);

	/*
	函数功能:启动程序,Frame2D程序入口
	说明:设置窗口的属性信息必须在启动之前执行,否则无效
	参数1:程序的实例句柄
	参数2:是否窗口(默认窗口)
	*/
	void startSystem(HINSTANCE hInstance);

	/*
	函数功能:启动场景
	参数1:启动的场景
	*/
	void startScene(Scene* scene);

	/*
	函数功能:运行程序
	*/
	int Run();

	/*
	获得fps
	*/
	float GetFPS() const;

	/*
	设置循环的间隔,默认为0,当该值为0时是最大fps
	*/
	void SetInterval(const DWORD& interval = 0);

	/*
	是否暂停
	*/
	bool IsPause() const;

	/*
	设置程序暂停
	*/
	void SetPause(bool bPause);

	/*
	退出程序
	*/
	void ExitApplication();

private:
	Application()
		: _interval(0)
		, _fps(0)
		, _x(WindowManager::DEFAULT)
		, _y(WindowManager::DEFAULT)
		, _width(WindowManager::DEFAULT)
		, _height(WindowManager::DEFAULT)
		, _title("Frame2D")
		, _bWindow(true)
		, _bStart(false)
		, _pause(false)
	{}
	Application(Application&);
	Application& operator=(Application&);

private:
	// 时间间隔
	DWORD _interval;
	// fps
	float _fps;

	// 窗口的坐标
	int _x;
	int _y;
	// 窗口的宽和高
	int _width;
	int _height;

	// 窗口的标题
	string _title;

	// 是否窗口
	bool _bWindow;

	// 是否启动
	bool _bStart;

	// 程序暂停状态
	bool _pause;
};

NS_F2D_END

#endif