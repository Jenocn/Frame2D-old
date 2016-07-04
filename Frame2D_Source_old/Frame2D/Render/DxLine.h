#ifndef _DX_LINE_H_H_
#define _DX_LINE_H_H_

#include "DX9.h"

struct LINE_CUSTOMVERTEX
{
	D3DXVECTOR3 _position;
	D3DCOLOR _color;

	static const DWORD D3DFVF_LINE =
		D3DFVF_XYZ | D3DFVF_DIFFUSE;
};

class DxLine
{
public:
	/*
		函数功能:创建一条先线,并初始化
		返回值:返回初始化成功的对象
		参数1:线的长度
	*/
	static DxLine* CreateWithInit(const int& length);

	/*
		函数功能:初始化线
		参数1:线的长度
	*/
	bool Init(const int& length);

	/*
		函数功能:释放内存空间,并delete自身
	*/
	void Release();

	/*
		函数功能:绘制这条线
		参数1~3:空间坐标
		参数4~5:围绕对应的坐标轴旋转的角度
		参数6:线的锚点,绘制中心点
	*/
	void Draw(
		const float& positionX,
		const float& positionY,
		const float& positionZ,
		const float& angleY,
		const float& angleZ,
		const float& anchor,
		bool colorBlend = false
		);

	/*
		函数功能:设置线的长度
		说明:调用此函数必须要调用ResetVertex之后才能生效
	*/
	void SetLength(const int& length);

	/*
		函数功能:设置线的颜色表现
		参数1:左端颜色
		参数2:右端颜色
		说明:调用此函数必须要调用ResetVertex之后才能生效
	*/
	void SetColor(
		const D3DCOLOR& colorL,
		const D3DCOLOR& colorR);

	/*
		函数功能:设置线的颜色表现
		参数1:颜色值
		说明:调用此函数必须要调用ResetVertex之后才能生效
	*/
	void SetColor(const D3DCOLOR& color);

	/*
		函数功能:设置线的颜色表现
		参数1~3:RGB颜色值
		说明:调用此函数必须要调用ResetVertex之后才能生效
	*/
	void SetColor(const BYTE& r, const BYTE& g, const BYTE& b);

	/*
		函数功能:重新设置一下顶点
		说明:设置一下此次对顶点的更改,使之有效
	*/
	void ResetVertex();

private:
	DxLine()
	: mp_vertexBuffer(0)
	, _length(0)
	{}

	DxLine(DxLine&);
	DxLine& operator=(DxLine&);

private:
	LINE_CUSTOMVERTEX _vertex[2];
	LPDIRECT3DVERTEXBUFFER9 mp_vertexBuffer;
	int _length;
};

#endif