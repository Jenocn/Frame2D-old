#ifndef _D3D_MANAGER_H_H_
#define _D3D_MANAGER_H_H_

#include "DX9.h"

class D3DManager
{
public:
	static D3DManager* getInstance();

	/*
		函数功能:初始化D3D
		参数1:窗口句柄
		参数2:是否窗口化,默认(true)
	*/
	void startUp(HWND hWnd, bool bWindow = true);

	/*
		停止D3D,并且会调用各缓存的Release,并delete自身
	*/
	void shutDown();

	/*
		绘制之前的操作,绘制前必须调用
	*/
	void BeginDraw();

	/*
		绘制完毕后的操作
	*/
	void EndDraw();

	/*
		获取Device
	*/
	LPDIRECT3DDEVICE9 getDevice() const;

	/*
		函数功能:设置D3D渲染窗口在屏幕中的位置和大小
		参数1,2:坐标
		参数3,4:大小
	*/
	void SetRenderWindow(
		const DWORD& positionX,
		const DWORD& positionY,
		const DWORD& width,
		const DWORD& height);

	/*
		函数功能:获得屏幕中的渲染窗口的RECT
	*/
	RECT GetRenderWindow() const;

private:
	D3DManager()
	: mp_device(0)
	, _window(true)
	{}
	D3DManager(D3DManager&);
	D3DManager& operator=(D3DManager&);

private:
	LPDIRECT3DDEVICE9 mp_device;
	RECT _renderWindowRect;
	bool _window;
};

#endif