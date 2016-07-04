#include "Sprite.h"

USING_NS_F2D

Sprite* Sprite::Create(const string& path, const D3DCOLOR& colorKey)
{
	Sprite* sprite = new(nothrow) Sprite();
	assert(sprite && sprite->InitWithFile(path, colorKey) && "Sprite Create Failed!");

	return sprite;
}

Sprite::~Sprite()
{
	_texture2d->Release();
	_texture2d = 0;
}

bool Sprite::InitWithFile(const string& path, const D3DCOLOR& colorKey)
{
	_texture2d = Texture2D::CreateWithInit(path, colorKey);
	SetWidth(_texture2d->GetWidth());
	SetHeight(_texture2d->GetHeight());
	SetRenderRect(0, 0, GetWidth(), GetHeight());

	return true;
}

void Sprite::SetTexture(const string& path, const D3DCOLOR& colorKey)
{
	if (_texture2d != 0)
	{
		_texture2d->Release();
	}
	
	InitWithFile(path, colorKey);
}

void Sprite::SetTexture(Texture2D* texture)
{
	if (_texture2d != 0)
	{
		_texture2d->Release();
	}
	
	if (texture != 0)
	{
		_texture2d = texture;
	}

	SetWidth(_texture2d->GetWidth());
	SetHeight(_texture2d->GetHeight());
	SetRenderRect(0, 0, GetWidth(), GetHeight());
}

void Sprite::Update(const float& delta)
{
	Element::Update(delta);
}



void Sprite::Render()
{
	Element::Render();

	_texture2d->Draw(
		GetPositionX(),
		GetPositionY(),
		GetPositionZ(),
		GetAngleX(),
		GetAngleY(),
		GetAngleZ(),
		GetAnchorX(),
		GetAnchorY(),
		GetScaleX(),
		GetScaleY()
		);

}

void Sprite::ResetVertex()
{
	_texture2d->SetColor(
		GetColorLT(),
		GetColorRT(),
		GetColorRB(),
		GetColorLB()
		);

	_texture2d->SetRenderRect(
		GetRenderRect());

	_texture2d->ResetVertex();

	SetWidth(_texture2d->GetWidth());
	SetHeight(_texture2d->GetHeight());
}

D3DCOLOR Sprite::GetColorLT() const
{
	return D3DCOLOR_ARGB((BYTE)_aLT, (BYTE)_rLT, (BYTE)_gLT, (BYTE)_bLT);
}

D3DCOLOR Sprite::GetColorRT() const
{
	return D3DCOLOR_ARGB((BYTE)_aRT, (BYTE)_rRT, (BYTE)_gRT, (BYTE)_bRT);
}

D3DCOLOR Sprite::GetColorRB() const
{
	return D3DCOLOR_ARGB((BYTE)_aRB, (BYTE)_rRB, (BYTE)_gRB, (BYTE)_bRB);
}

D3DCOLOR Sprite::GetColorLB() const
{
	return D3DCOLOR_ARGB((BYTE)_aLB, (BYTE)_rLB, (BYTE)_gLB, (BYTE)_bLB);
}

void Sprite::SetColor(const D3DCOLOR& color)
{
	SetColor(color, color, color, color);
}

void Sprite::SetColor(
	const D3DCOLOR& colorLT,
	const D3DCOLOR& colorRT,
	const D3DCOLOR& colorRB,
	const D3DCOLOR& colorLB)
{
	_aLT = (unsigned char)(colorLT >> 24);
	_rLT = (unsigned char)(colorLT >> 16);
	_gLT = (unsigned char)(colorLT >> 8);
	_bLT = (unsigned char)colorLT;

	_aRT = (unsigned char)(colorRT >> 24);
	_rRT = (unsigned char)(colorRT >> 16);
	_gRT = (unsigned char)(colorRT >> 8);
	_bRT = (unsigned char)colorRT;

	_aLB = (unsigned char)(colorLB >> 24);
	_rLB = (unsigned char)(colorLB >> 16);
	_gLB = (unsigned char)(colorLB >> 8);
	_bLB = (unsigned char)colorLB;

	_aRB = (unsigned char)(colorRB >> 24);
	_rRB = (unsigned char)(colorRB >> 16);
	_gRB = (unsigned char)(colorRB >> 8);
	_bRB = (unsigned char)colorRB;
}

void Sprite::SetColorRGB(byte r, byte g, byte b)
{
	SetColor(D3DCOLOR_XRGB(r, g, b));
}

void Sprite::SetAlpha(byte alpha)
{
	_aLT = alpha;
	_aRT = alpha;
	_aLB = alpha;
	_aRB = alpha;
}

void Sprite::SetColor_LT(const D3DCOLOR& color)
{
	_aLT = (unsigned char)color >> 24;
	_rLT = (unsigned char)color >> 16;
	_gLT = (unsigned char)color >> 8;
	_bLT = (unsigned char)color;
}

void Sprite::SetColorRGB_LT(byte r, byte g, byte b)
{
	_rLT = r;
	_gLT = g;
	_bLT = b;
}

void Sprite::SetColorAlpha_LT(byte alpha)
{
	_aLT = alpha;
}

void Sprite::SetColor_RT(const D3DCOLOR& color)
{
	_aRT = (unsigned char)color >> 24;
	_rRT = (unsigned char)color >> 16;
	_gRT = (unsigned char)color >> 8;
	_bRT = (unsigned char)color;
}

void Sprite::SetColorRGB_RT(byte r, byte g, byte b)
{
	_rRT = r;
	_gRT = g;
	_bRT = b;
}

void Sprite::SetColorAlpha_RT(byte alpha)
{
	_aRT = alpha;
}

void Sprite::SetColor_RB(const D3DCOLOR& color)
{
	_aRB = (unsigned char)color >> 24;
	_rRB = (unsigned char)color >> 16;
	_gRB = (unsigned char)color >> 8;
	_bRB = (unsigned char)color;
}

void Sprite::SetColorRGB_RB(byte r, byte g, byte b)
{
	_rRB = r;
	_gRB = g;
	_bRB = b;
}

void Sprite::SetColorAlpha_RB(byte alpha)
{
	_aRB = alpha;
}

void Sprite::SetColor_LB(const D3DCOLOR& color)
{
	_aLB = (unsigned char)color >> 24;
	_rLB = (unsigned char)color >> 16;
	_gLB = (unsigned char)color >> 8;
	_bLB = (unsigned char)color;
}

void Sprite::SetColorRGB_LB(byte r, byte g, byte b)
{
	_rLB = r;
	_gLB = g;
	_bLB = b;
}

void Sprite::SetColorAlpha_LB(byte alpha)
{
	_aLB = alpha;
}

RECT Sprite::GetRenderRect() const
{
	return _renderRect;
}

void Sprite::SetRenderRect(const RECT& rect)
{
	_renderRect = rect;
}

void Sprite::SetRenderRect(
	const int& left,
	const int& top,
	const int& right,
	const int& bottom)
{
	_renderRect.left = left;
	_renderRect.right = right;
	_renderRect.top = top;
	_renderRect.bottom = bottom;
}

int Sprite::GetTextureWidth() const
{
	return _texture2d->GetTextureWidth();
}

int Sprite::GetTextureHeight() const
{
	return _texture2d->GetTextureHeight();
}

void Sprite::SetTextureBlend(bool enable)
{
	_texture2d->SetTextureBlend(enable);
}
