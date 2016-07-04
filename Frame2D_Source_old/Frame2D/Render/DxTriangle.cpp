#include "DxTriangle.h"
#include "D3DManager.h"
#include "TextureCache.h"

DxTriangle* DxTriangle::CreateWithInit(const int& width, const int& height)
{
	DxTriangle* triangle = new (nothrow)DxTriangle();
	assert(triangle && triangle->Init(width, height) && "DxTriangle Create Failed!");

	return triangle;
}

DxTriangle* DxTriangle::CreateWithInit(const string& path,
	const D3DCOLOR& colorKey)
{
	DxTriangle* triangle = new (nothrow)DxTriangle();
	assert(triangle && triangle->InitWithFile(path, colorKey) && "DxTriangle Create Failed!");

	return triangle;
}

bool DxTriangle::Init(const int& width, const int& height)
{
	if (width <= 0 || height <= 0)
	{
		return false;
	}

	LPDIRECT3DDEVICE9 pDevice = D3DManager::getInstance()->getDevice();

	_width = width;
	_height = height;

	pDevice->CreateVertexBuffer(3 * sizeof(TRIANGLE_CUSTOMVERTEX), 0,
		TRIANGLE_CUSTOMVERTEX::D3DFVF_TRIANGLE,
		D3DPOOL_DEFAULT, &mp_vertexBuffer, NULL);

	_vertex[0]._position = D3DXVECTOR3(0.0f, height / 2.0f, 0.0f);
	_vertex[0]._color = 0xffffffff;
	_vertex[0]._u = 0.5;
	_vertex[0]._v = 0;

	_vertex[1]._position = D3DXVECTOR3(width / 2.0f, -height / 2.0f, 0.0f);
	_vertex[1]._color = 0xffffffff;
	_vertex[1]._u = 1;
	_vertex[1]._v = 1;

	_vertex[2]._position = D3DXVECTOR3(-width / 2.0f, -height / 2.0f, 0.0f);
	_vertex[2]._color = 0xffffffff;
	_vertex[2]._u = 0;
	_vertex[2]._v = 1;

	ResetVertex();

	return true;
}

bool DxTriangle::InitWithFile(const string& path,
	const D3DCOLOR& colorKey)
{
	const TextureInfo* textureInfo =
		TextureCache::getInstance()->LoadTextureFromFile(path, colorKey);

	if (textureInfo == 0)
	{
		return false;
	}

	if (textureInfo->GetTextureInfo().Width <= 0 ||
		textureInfo->GetTextureInfo().Height <= 0)
	{
		return false;
	}

	mp_texture = textureInfo->GetTexture();

	return Init(textureInfo->GetTextureInfo().Width,
		textureInfo->GetTextureInfo().Height);
}

void DxTriangle::Release()
{
	if (mp_vertexBuffer)
	{
		mp_vertexBuffer->Release();
		mp_vertexBuffer = 0;
	}

	mp_texture = 0;

	delete this;
}

void DxTriangle::Draw(
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
	bool textureBlend)
{
	LPDIRECT3DDEVICE9 pDevice = D3DManager::getInstance()->getDevice();

	D3DXMATRIX world;

	D3DXMATRIX matAnchor;
	D3DXMatrixTranslation(&matAnchor, (0.5f - anchorX) * _width, (0.5f - anchorY) * _height, 0);

	D3DXMATRIX matRx;
	D3DXMatrixRotationX(&matRx, angleX / 180.0f * D3DX_PI);

	D3DXMATRIX matRy;
	D3DXMatrixRotationY(&matRy, angleY / 180.0f * D3DX_PI);

	D3DXMATRIX matRz;
	D3DXMatrixRotationZ(&matRz, angleZ / 180.0f * D3DX_PI);

	D3DXMATRIX matScale;
	D3DXMatrixScaling(&matScale, scaleX, scaleY, 1.0f);

	D3DXMATRIX matPos;
	D3DXMatrixTranslation(&matPos, positionX, positionY, positionZ);

	world = matAnchor * matRx * matRy * matRz * matScale * matPos;

	pDevice->SetTransform(D3DTS_WORLD, &world);

	if (textureBlend)
	{
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	}

	pDevice->SetStreamSource(0, mp_vertexBuffer, 0, sizeof(TRIANGLE_CUSTOMVERTEX));
	pDevice->SetFVF(TRIANGLE_CUSTOMVERTEX::D3DFVF_TRIANGLE);
	pDevice->SetTexture(0, mp_texture);

	pDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 1);

	if (textureBlend)
	{
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	}

}

void DxTriangle::SetColor(
	const D3DCOLOR& colorA,
	const D3DCOLOR& colorB,
	const D3DCOLOR& colorC)
{
	_vertex[0]._color = colorA;
	_vertex[1]._color = colorB;
	_vertex[2]._color = colorC;
}

void DxTriangle::SetColor(const D3DCOLOR& color)
{
	SetColor(color, color, color);
}

void DxTriangle::SetColorRGB(const BYTE& r, const BYTE& g, const BYTE& b)
{
	SetColor(D3DCOLOR_XRGB(r, g, b));
}

void DxTriangle::ResetVertex()
{
	void* pVertex = 0;
	mp_vertexBuffer->Lock(0, sizeof(_vertex), (void**)&pVertex, 0);
	memcpy(pVertex, _vertex, sizeof(_vertex));
	mp_vertexBuffer->Unlock();
}

int DxTriangle::GetWidth() const
{
	return _width;
}

void DxTriangle::SetWidth(const int& width)
{
	_vertex[1]._position.x = width / 2.0f;
	_vertex[2]._position.x = -width / 2.0f;
}

void DxTriangle::SetHeight(const int& height)
{
	_vertex[0]._position.y = height / 2.0f;
}

int DxTriangle::GetHeight() const
{
	return _height;
}