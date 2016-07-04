#include "D3DManager.h"
#include "Camera.h"
#include "TextureCache.h"
#include "DxFontCache.h"

static D3DManager* pInstance = 0;

D3DManager* D3DManager::getInstance()
{
	if (pInstance == 0)
	{
		pInstance = new D3DManager();
	}

	return pInstance;
}

void D3DManager::startUp(HWND hWnd, bool bWindow)
{
	this->_window = bWindow;

	LPDIRECT3D9 pD3D = 0;
	pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	if (_window)
	{
		// 根据窗口的视图区域初始化渲染窗口的矩形区域
		GetClientRect(hWnd, &_renderWindowRect);
	}
	else
	{
		// 获取当前全屏的分辨率
		D3DDISPLAYMODE mode;
		pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &mode);

		_renderWindowRect.left = 0;
		_renderWindowRect.top = 0;
		_renderWindowRect.right = mode.Width;
		_renderWindowRect.bottom = mode.Height;
	}

	D3DCAPS9 caps;
	DWORD behaviorFlags = 0;
	pD3D->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &caps);

	// 如果支持硬件顶点运算就设置使用硬件,否则使用软件模拟
	if (caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
	{
		behaviorFlags = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	}
	else
	{
		behaviorFlags = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
	}

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	// 显示器刷新频率
	// 参数1:D3DPRESENT_INTERVAL_IMMEDIATE 实时刷新
	// 参数2:D3DPRESENT_INTERVAL_DEFAULT 根据显示器的刷新率刷新
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;
	d3dpp.Windowed = _window;
	d3dpp.hDeviceWindow = hWnd;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT; // 窗口模式这个值必须是0

	// 窗口模式这两个值可以不填,默认是窗口大小,全屏下必须指定一个显卡所支持的分辨率
	d3dpp.BackBufferWidth = _renderWindowRect.right - _renderWindowRect.left;
	d3dpp.BackBufferHeight = _renderWindowRect.bottom - _renderWindowRect.top;
	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
	d3dpp.BackBufferCount = 1;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
	d3dpp.MultiSampleQuality = 0;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;
	d3dpp.Flags = 0;
	pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL,
		hWnd, behaviorFlags, &d3dpp, &mp_device);

	// 设置摄像机默认位置
	//float tempW = d3dpp.BackBufferWidth;
	//float tempH = d3dpp.BackBufferHeight;

	//float tempZ = -(tempW + tempH) / 2019 * 1000;

	// 1176 843 1000
	//float tempZ = -((tempW / 1176.0f) + (tempH / 843.0f)) / 2.0f * 1000;
	Camera::getInstance()->SetCameraPosition(0.0f, 0.0f, -666.67);
	//Camera::getInstance()->SetCameraPosition(0.0f, 0.0f, -666.67f);

	// 设置视点位置
	Camera::getInstance()->SetViewPosition(0, 0, 0);

	// 设置Z轴可视距离
	Camera::getInstance()->SetVisibleRange(1500);

	// 设置渲染窗口默认大小
	SetRenderWindow(0, 0, _renderWindowRect.right - _renderWindowRect.left,
		_renderWindowRect.bottom - _renderWindowRect.top);

	// 开启alpha混合
	mp_device->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	mp_device->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	mp_device->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
	mp_device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	// 颜色混合(用于粒子效果非常好)
	//mp_device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	// alpha透明
	mp_device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	mp_device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	//关闭背面消隐
	mp_device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	// 关闭光照效果的开光
	mp_device->SetRenderState(D3DRS_LIGHTING, FALSE);
	// 设置高洛德着色模式
	mp_device->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_GOURAUD);
	// 设置为实体渲染
	mp_device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	// 设置为线性纹理过滤(d3d默认的是临近点采样)
	if (behaviorFlags == D3DCREATE_HARDWARE_VERTEXPROCESSING)
	{
		mp_device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
		mp_device->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	}

	pD3D->Release();
}

void D3DManager::shutDown()
{
	TextureCache::getInstance()->Release();
	DxFontCache::getInstance()->Release();

	if (mp_device != 0)
	{
		mp_device->Release();
		mp_device = 0;
	}

	delete this;
	pInstance = 0;
}

void D3DManager::BeginDraw()
{
	mp_device->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
	mp_device->BeginScene();
}

void D3DManager::EndDraw()
{
	mp_device->EndScene();
	mp_device->Present(0, 0, 0, 0);
}

LPDIRECT3DDEVICE9 D3DManager::getDevice() const
{
	return mp_device;
}

void D3DManager::SetRenderWindow(
	const DWORD& positionX,
	const DWORD& positionY,
	const DWORD& width,
	const DWORD& height)
{
	D3DVIEWPORT9 vp; //实例化一个D3DVIEWPORT9结构体，然后做填空题给各个参数赋值就可以了
	vp.X = positionX;		//表示视口相对于窗口的X坐标
	vp.Y = positionY;		//视口相对对窗口的Y坐标
	vp.Width = width;	//视口的宽度
	vp.Height = height; //视口的高度
	vp.MinZ = 0.0f; //视口在深度缓存中的最小深度值
	vp.MaxZ = 1.0f;	//视口在深度缓存中的最大深度值
	mp_device->SetViewport(&vp); //视口的设置
}

RECT D3DManager::GetRenderWindow() const
{
	return _renderWindowRect;
}

