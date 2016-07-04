#ifndef _DX_POINT_H_H_
#define _DX_POINT_H_H_

#include "DX9.h"

struct POINT_CUSTOMVERTEX
{
	D3DXVECTOR3 _position;
	DWORD _color;

	static const DWORD D3DFVF_POINT =
		D3DFVF_XYZ | D3DFVF_DIFFUSE;
};

class DxPoint
{
public:
	/*
		函数功能:创建点,并初始化点
		返回值:返回初始化成功之后的对象
	*/
	static DxPoint* CreateWithInit();

	/*
		函数功能:创建带有纹理的点,并初始化点
		返回值:返回初始化成功之后的对象
		参数1:纹理路径
		参数2:需要透明的颜色值
	*/
	static DxPoint* CreateWithInit(const string& path, const D3DCOLOR& colorKey = 0);

	/*
		函数功能:初始化点
	*/
	bool Init();

	/*
		函数功能:通过纹理文件初始化点
		返回值:如果初始化成功则返回真,否则返回假
		参数1:纹理路径
		参数2:需要透明的颜色值
	*/
	bool InitWithFile(const string& path, const D3DCOLOR& colorKey = 0);

	/*
		函数功能:释放内存空间并delete自身
		说明:如果使用了纹理,那么不会清除缓存中的纹理对象
	*/
	void Release();

	/*
		函数功能:绘制点
		参数1~3:空间坐标
		参数4:缩放比例(1.0表示标准大小)
		参数5:是否执行纹理的或操作,纹理颜色融合在一起
	*/
	void Draw(
		const float& positionX,
		const float& positionY,
		const float& positionZ,
		const float& scale,
		bool textureBlend = false);

	/*
	函数功能:设置颜色混合
	说明:使用该函数之后必须调用ResetVertex才能使之生效
	参数1:整体颜色
	*/
	void SetColor(const D3DCOLOR& color);

	/*
		函数功能:设置颜色混合
		说明:使用该函数之后必须调用ResetVertex才能使之生效
		参数1:整体红色
		参数2:整体绿色
		参数3:整体蓝色
	*/
	void SetColor(const BYTE& r, const BYTE& g, const BYTE& b);

	/*
		函数功能:重新设置一下顶点
		说明:设置一下此次对顶点的更改,使之有效
	*/
	void ResetVertex();

private:
	DxPoint()
	: mp_vertexBuffer(0)
	, mp_texture(0)
	{}

	DxPoint(DxPoint&);
	DxPoint& operator=(DxPoint&);

private:
	POINT_CUSTOMVERTEX _vertex;
	LPDIRECT3DVERTEXBUFFER9 mp_vertexBuffer;
	LPDIRECT3DTEXTURE9 mp_texture;
};

#endif