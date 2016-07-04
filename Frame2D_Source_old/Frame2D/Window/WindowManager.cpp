#include "WindowManager.h"
#include "..\Resource.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (message == WM_DESTROY)
	{
		PostQuitMessage(0);
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}

static WindowManager* pInstance = 0;

WindowManager* WindowManager::getInstance()
{
	if (pInstance == 0)
	{
		pInstance = new WindowManager();
	}

	return pInstance;
}

void WindowManager::startUp(
	const HINSTANCE& hInstance,
	const string& titleStr,
	const int& width, const int& height,
	const int& x, const int&y)
{
	WNDCLASSEX wndClass = { 0 };

	wndClass.cbSize = sizeof(WNDCLASSEX);
	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	wndClass.hInstance = hInstance;
	wndClass.lpfnWndProc = WndProc;
	wndClass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(WINDOW_ICON));
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndClass.lpszClassName = "Frame2D";

	RegisterClassEx(&wndClass);

	_width = width;
	_height = height;
	int tmpX = x;
	int tmpY = y;

	if (_width == WindowManager::DEFAULT)
	{
		_width = 800;
	}
	if (_height == WindowManager::DEFAULT)
	{
		_height = 600;
	}

	if (tmpX == WindowManager::DEFAULT)
	{
		tmpX = (GetSystemMetrics(SM_CXFULLSCREEN) - _width) / 2;
	}
	if (tmpY == WindowManager::DEFAULT)
	{
		tmpY = (GetSystemMetrics(SM_CYFULLSCREEN) - _height) / 2;
	}

	_hWnd = CreateWindow(
		wndClass.lpszClassName,
		titleStr.c_str(),
		WS_SYSMENU | WS_MINIMIZEBOX,
		tmpX, tmpY, _width, _height,
		NULL, NULL, hInstance, NULL);

	ShowWindow(_hWnd, SW_SHOWDEFAULT);
	UpdateWindow(_hWnd);

	_hInstance = hInstance;
	GetClientRect(_hWnd, &_viewRect);
}

void WindowManager::shutDown()
{
	UnregisterClass("Frame2D", _hInstance);

	delete this;
	pInstance = 0;
}

bool WindowManager::Update(const float& delta)
{
	if (_msg.message == WM_QUIT)
	{
		return false;
	}

	if (PeekMessage(&_msg, NULL, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&_msg);
		DispatchMessage(&_msg);
	}

	return true;
}

const HWND WindowManager::getHWND() const
{
	return _hWnd;
}

RECT WindowManager::getViewRect() const
{
	return _viewRect;
}

MSG WindowManager::getMSG() const
{
	return _msg;
}

void WindowManager::ClearMsg()
{
	if (_msg.message != WM_QUIT)
	{
		_msg = MSG();
	}
}

int WindowManager::getWindowWidth() const
{
	return _width;
}

int WindowManager::getWindowHeight() const
{
	return _height;
}

void WindowManager::SetQuitMsg()
{
	PostQuitMessage(0);
}
