#ifndef _WINDOW_MANAGER_H_H_
#define _WINDOW_MANAGER_H_H_

#include "Win32.h"

/*
窗口管理器,用来初始化win32的窗口
*/
class WindowManager
{
public:
	static WindowManager* getInstance();

	static const int DEFAULT = -99;

	/*
	函数功能:启动窗口系统
	参数1:当前程序实例,通过winmain参数获取
	参数2:窗口的标题
	参数3~4:窗口大小
	参数5~6:初始坐标(默认居中)
	*/
	void startUp(
		const HINSTANCE& hInstance,
		const string& titleStr,
		const int& width = DEFAULT, const int& height = DEFAULT,
		const int& x = DEFAULT, const int& = DEFAULT);

	/*
	函数功能:释放内存,清除窗口,并delete自身
	*/
	void shutDown();

	/*
	函数功能:更新数据
	*/
	bool Update(const float& delta);

	const HWND getHWND() const;

	RECT getViewRect() const;

	MSG getMSG() const;

	void ClearMsg();

	int getWindowWidth() const;

	int getWindowHeight() const;

	void SetQuitMsg();

private:
	WindowManager()
		: _hWnd(0)
		, _hInstance(0)
		, _width(0)
		, _height(0)
	{}

	WindowManager(WindowManager&);
	WindowManager& operator=(WindowManager&);

private:
	// 窗口句柄
	HWND _hWnd;
	// 程序实例句柄
	HINSTANCE _hInstance;
	// 视图区域的大小
	RECT _viewRect;
	// windows消息
	MSG _msg;
	// 窗口的大小
	int _width;
	int _height;
};

#endif