#include "DxPoint.h"
#include "TextureCache.h"
#include "D3DManager.h"

DxPoint* DxPoint::CreateWithInit()
{
	DxPoint* point = new(nothrow) DxPoint();
	assert(point && point->Init() && "DxPoint Create Failed!");

	return point;
}

DxPoint* DxPoint::CreateWithInit(const string& path, const D3DCOLOR& colorKey)
{
	DxPoint* point = new(nothrow) DxPoint();
	assert(point && point->InitWithFile(path, colorKey) && "DxPoint Create Failed!");

	return point;	
}

bool DxPoint::Init()
{
	LPDIRECT3DDEVICE9 pDevice = D3DManager::getInstance()->getDevice();

	pDevice->CreateVertexBuffer(sizeof(POINT_CUSTOMVERTEX), 0,
		POINT_CUSTOMVERTEX::D3DFVF_POINT,
		D3DPOOL_DEFAULT, &mp_vertexBuffer, NULL);

	_vertex._position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	_vertex._color = 0xffffffff;

	ResetVertex();

	return true;
}

bool DxPoint::InitWithFile(const string& path, const D3DCOLOR& colorKey)
{
	if (path.compare("") == 0)
	{
		return false;
	}

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

	return Init();
}

void DxPoint::Release()
{
	if (mp_vertexBuffer)
	{
		mp_vertexBuffer->Release();
		mp_vertexBuffer = 0;
	}

	mp_texture = 0;

	delete this;
}

void DxPoint::Draw(
	const float& positionX,
	const float& positionY,
	const float& positionZ,
	const float& scale,
	bool textureBlend)
{
	LPDIRECT3DDEVICE9 pDevice = D3DManager::getInstance()->getDevice();

	D3DXMATRIX matPos;
	D3DXMatrixTranslation(&matPos, positionX, positionY, positionZ);

	pDevice->SetTransform(D3DTS_WORLD, &matPos);

	pDevice->SetRenderState(D3DRS_POINTSCALEENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_POINTSCALE_A, 0);
	pDevice->SetRenderState(D3DRS_POINTSCALE_B, 0);
	pDevice->SetRenderState(D3DRS_POINTSCALE_C, 1036831949);
	pDevice->SetRenderState(D3DRS_POINTSIZE, *((DWORD*)&scale));

	if (textureBlend)
	{
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	}

	pDevice->SetStreamSource(0, mp_vertexBuffer, 0, sizeof(POINT_CUSTOMVERTEX));
	pDevice->SetFVF(POINT_CUSTOMVERTEX::D3DFVF_POINT);
	if (mp_texture)
	{
		pDevice->SetRenderState(D3DRS_POINTSPRITEENABLE, TRUE);
		pDevice->SetTexture(0, mp_texture);
	}
	pDevice->DrawPrimitive(D3DPT_POINTLIST, 0, 1);

	if (mp_texture)
	{
		pDevice->SetRenderState(D3DRS_POINTSPRITEENABLE, FALSE);
	}
	pDevice->SetRenderState(D3DRS_POINTSCALEENABLE, FALSE);

	if (textureBlend)
	{
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	}
}

void DxPoint::SetColor(const D3DCOLOR& color)
{
	_vertex._color = color;
}

void DxPoint::SetColor(const BYTE& r, const BYTE& g, const BYTE& b)
{
	SetColor(D3DCOLOR_XRGB(r, g, b));
}

void DxPoint::ResetVertex()
{
	void* pVertex = 0;
	mp_vertexBuffer->Lock(0, sizeof(_vertex), (void**)&pVertex, 0);
	memcpy(pVertex, &_vertex, sizeof(_vertex));
	mp_vertexBuffer->Unlock();
}
