#ifndef TEXTURE_2D_H_H_
#define TEXTURE_2D_H_H_

#include "DX9.h"

struct TEXTURE2D_CUSTOMVERTEX
{
	D3DXVECTOR3 _position;
	DWORD _color;
	FLOAT _u, _v;

	static const DWORD D3DFVF_TEXTURE2D =
		D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1;
};

class Texture2D
{
public:
	/*
		函数功能:创建一个Texture2D对象并且自动调用初始化,最后返回这个对象
		返回值:已经创建并初始化过的Texture2D对象
		参数1:路径
		参数2:需要透明的颜色
	*/
	static Texture2D* CreateWithInit(const string& path, const D3DCOLOR& colorKey = 0);

	/*
		函数功能:通过文件初始化纹理
		返回值:如果初始化成功则返回真,否则返回假
		参数1:文件路径
		参数2:需要透明的颜色
	*/
	bool InitWithFile(const string& path, const D3DCOLOR& colorKey = 0);

	/*
		函数功能:释放所使用的内存空间,并delete自身
		说明:缓存的纹理不会在这里释放
	*/
	void Release();

	/*
		函数功能:常规渲染
		参数1~3:空间坐标(x,y,z)
		参数4~6:围绕(x,y,z)轴的旋转
		参数7~8:锚点
		参数9~10:缩放
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
		const float& scaleY
		);

	/*
		函数功能:设置渲染的目标矩形区域
		说明:使用该函数之后必须调用ResetVertex才能使之生效
		参数1:目标矩形区域
	*/
	void SetRenderRect(const RECT& destRect);

	/*
		函数功能:设置颜色
		说明:使用该函数之后必须调用ResetVertex才能使之生效
		参数1:左上角区域颜色
		参数2:右上角区域颜色
		参数3:右下角区域颜色
		参数4:左下角区域颜色
	*/
	void SetColor(
		const D3DCOLOR& colorLT,
		const D3DCOLOR& colorRT,
		const D3DCOLOR& colorRB,
		const D3DCOLOR& colorLB
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
	void SetColor(const BYTE& r, const BYTE& g, const BYTE& b);

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
		获得高
	*/
	int GetHeight() const;

	/*
	获得纹理的宽
	*/
	int GetTextureWidth() const;

	/*
	获得纹理的高
	*/
	int GetTextureHeight() const;

	// 设置是否开启纹理融合
	void SetTextureBlend(bool enable);

private:
	Texture2D()
	: mp_vertexBuffer(0)
	, mp_indexBuffer(0)
	, mp_texture(0)
	, _width(0)
	, _height(0)
	, _bTextureBlend(false)
	{}

	Texture2D(Texture2D&);
	Texture2D& operator=(Texture2D&);

private:
	TEXTURE2D_CUSTOMVERTEX _vertex[4];
	LPDIRECT3DVERTEXBUFFER9 mp_vertexBuffer;
	LPDIRECT3DINDEXBUFFER9 mp_indexBuffer;
	LPDIRECT3DTEXTURE9 mp_texture;
	int _width;
	int _height;
	int _textureWidth;
	int _textureHeight;
	bool _bTextureBlend;
};

#endif