#ifndef _DX_TRIANGLE_H_H_
#define _DX_TRIANGLE_H_H_

#include "DX9.h"

struct TRIANGLE_CUSTOMVERTEX
{
	D3DXVECTOR3 _position;
	D3DCOLOR _color;
	FLOAT _u, _v;

	static const DWORD D3DFVF_TRIANGLE =
		D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1;
};

class DxTriangle
{
public:
	/*
		函数功能:通过宽和高创建三角形
		参数1~2:宽和高
	*/
	static DxTriangle* CreateWithInit(const int& width, const int& height);

	/*
		函数功能:通过纹理创建三角形
		说明:三角形的大小是纹理的宽和高
		参数1:纹理路径
		参数2:需要透明的颜色
	*/
	static DxTriangle* CreateWithInit(const string& path,
		const D3DCOLOR& colorKey = 0);

	/*
		函数功能:通过宽和高初始化三角形
		参数1~2:宽和高
	*/
	bool Init(const int& width, const int& height);

	/*
		函数功能:通过纹理初始化
		参数1:纹理路径
		参数2:需要透明的颜色值
	*/
	bool InitWithFile(const string& path,
		const D3DCOLOR& colorKey = 0);

	/*
		函数功能:释放内存,并delete自身
		说明:不会释放缓存的纹理
	*/
	void Release();

	/*
		函数功能:绘制三角形
		参数1~3:空间坐标
		参数4~6:x,y,z轴上的旋转角度
		参数7~8:锚点,中心点
		参数9~10:x,y轴上的缩放比例
		参数11:纹理颜色融合
	*/
	void Draw(
		const float& positionX,
		const float& positionY,
		const float& positionZ,
		const float& angleX,
		const float& angleY,
		const float& angleZ,
		const float& anchorX,
		const float& anchorY,
		const float& scaleX,
		const float& scaleY,
		bool textureBlend = false
		);

	/*
		函数功能:设置颜色
		说明:使用该函数之后必须调用ResetVertex才能使之生效
		参数1:A角区域颜色(上方的点)
		参数2:B角区域颜色(右下角)
		参数3:C角区域颜色(左下角)
	*/
	void SetColor(
		const D3DCOLOR& colorA,
		const D3DCOLOR& colorB,
		const D3DCOLOR& colorC
		);

	/*
	函数功能:设置颜色
	说明:使用该函数之后必须调用ResetVertex才能使之生效
	参数1:整体颜色
	*/
	void SetColor(const D3DCOLOR& color);

	/*
		函数功能:设置颜色
		说明:使用该函数之后必须调用ResetVertex才能使之生效
		参数1:整体红色
		参数2:整体绿色
		参数3:整体蓝色
	*/
	void SetColorRGB(const BYTE& r, const BYTE& g, const BYTE& b);

	/*
		函数功能:重新设置一下顶点
		说明:设置一下此次对顶点的更改,使之有效
	*/
	void ResetVertex();

	/*
		获得宽
	*/
	int GetWidth() const;

	/*
		设置宽
	*/
	void SetWidth(const int& width);

	/*
		设置高
	*/
	void SetHeight(const int& height);

	/*
		获得高
	*/
	int GetHeight() const;

private:
	DxTriangle()
	: mp_vertexBuffer(0)
	, mp_texture(0)
	, _width(0)
	, _height(0)
	{}

	DxTriangle(DxTriangle&);
	DxTriangle& operator=(DxTriangle&);

private:
	TRIANGLE_CUSTOMVERTEX _vertex[3];
	LPDIRECT3DVERTEXBUFFER9 mp_vertexBuffer;
	LPDIRECT3DTEXTURE9 mp_texture;
	int _width;
	int _height;
};

#endif