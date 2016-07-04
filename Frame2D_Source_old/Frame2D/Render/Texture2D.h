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
		��������:����һ��Texture2D�������Զ����ó�ʼ��,��󷵻��������
		����ֵ:�Ѿ���������ʼ������Texture2D����
		����1:·��
		����2:��Ҫ͸������ɫ
	*/
	static Texture2D* CreateWithInit(const string& path, const D3DCOLOR& colorKey = 0);

	/*
		��������:ͨ���ļ���ʼ������
		����ֵ:�����ʼ���ɹ��򷵻���,���򷵻ؼ�
		����1:�ļ�·��
		����2:��Ҫ͸������ɫ
	*/
	bool InitWithFile(const string& path, const D3DCOLOR& colorKey = 0);

	/*
		��������:�ͷ���ʹ�õ��ڴ�ռ�,��delete����
		˵��:������������������ͷ�
	*/
	void Release();

	/*
		��������:������Ⱦ
		����1~3:�ռ�����(x,y,z)
		����4~6:Χ��(x,y,z)�����ת
		����7~8:ê��
		����9~10:����
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
		��������:������Ⱦ��Ŀ���������
		˵��:ʹ�øú���֮��������ResetVertex����ʹ֮��Ч
		����1:Ŀ���������
	*/
	void SetRenderRect(const RECT& destRect);

	/*
		��������:������ɫ
		˵��:ʹ�øú���֮��������ResetVertex����ʹ֮��Ч
		����1:���Ͻ�������ɫ
		����2:���Ͻ�������ɫ
		����3:���½�������ɫ
		����4:���½�������ɫ
	*/
	void SetColor(
		const D3DCOLOR& colorLT,
		const D3DCOLOR& colorRT,
		const D3DCOLOR& colorRB,
		const D3DCOLOR& colorLB
		);

	/*
	��������:������ɫ
	˵��:ʹ�øú���֮��������ResetVertex����ʹ֮��Ч
	����1:������ɫ
	*/
	void SetColor(const D3DCOLOR& color);

	/*
		��������:������ɫ
		˵��:ʹ�øú���֮��������ResetVertex����ʹ֮��Ч
		����1:�����ɫ
		����2:������ɫ
		����3:������ɫ
	*/
	void SetColor(const BYTE& r, const BYTE& g, const BYTE& b);

	/*
		��������:��������һ�¶���
		˵��:����һ�´˴ζԶ���ĸ���,ʹ֮��Ч
	*/
	void ResetVertex();

	/*
		��ÿ�
	*/
	int GetWidth() const;

	/*
		��ø�
	*/
	int GetHeight() const;

	/*
	�������Ŀ�
	*/
	int GetTextureWidth() const;

	/*
	�������ĸ�
	*/
	int GetTextureHeight() const;

	// �����Ƿ��������ں�
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