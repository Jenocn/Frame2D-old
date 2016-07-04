#include "DxLine.h"
#include "D3DManager.h"

DxLine* DxLine::CreateWithInit(const int& length)
{
	DxLine* line = new(nothrow) DxLine();
	assert(line && line->Init(length) && "DxLine Create Failed!");

	return line;
}

bool DxLine::Init(const int& length)
{
	if (length <= 0)
	{
		return false;
	}

	LPDIRECT3DDEVICE9 pDevice = D3DManager::getInstance()->getDevice();

	_length = length;

	pDevice->CreateVertexBuffer(2 * sizeof(LINE_CUSTOMVERTEX), 0,
		LINE_CUSTOMVERTEX::D3DFVF_LINE,
		D3DPOOL_DEFAULT, &mp_vertexBuffer, NULL);

	_vertex[0]._position = D3DXVECTOR3(-length / 2.0f, 0.0f, 0.0f);
	_vertex[0]._color = 0xffffffff;

	_vertex[1]._position = D3DXVECTOR3(length / 2.0f, 0.0f, 0.0f);
	_vertex[1]._color = 0xffffffff;

	ResetVertex();

	return true;
}

void DxLine::Release()
{
	if (mp_vertexBuffer)
	{
		mp_vertexBuffer->Release();
		mp_vertexBuffer = 0;
	}

	delete this;
}

void DxLine::Draw(
	const float& positionX,
	const float& positionY,
	const float& positionZ,
	const float& angleY,
	const float& angleZ,
	const float& anchor,
	bool colorBlend)
{
	LPDIRECT3DDEVICE9 pDevice = D3DManager::getInstance()->getDevice();

	D3DXMATRIX world;

	D3DXMATRIX matAnchor;
	D3DXMatrixTranslation(&matAnchor, (0.5f - anchor) * _length, 0, 0);

	D3DXMATRIX matRy;
	D3DXMatrixRotationY(&matRy, angleY / 180.0f * D3DX_PI);

	D3DXMATRIX matRz;
	D3DXMatrixRotationZ(&matRz, angleZ / 180.0f * D3DX_PI);

	D3DXMATRIX matPos;
	D3DXMatrixTranslation(&matPos, positionX, positionY, positionZ);

	world = matAnchor * matRy * matRz * matPos;
	
	pDevice->SetTransform(D3DTS_WORLD, &world);

	pDevice->SetStreamSource(0, mp_vertexBuffer, 0, sizeof(LINE_CUSTOMVERTEX));
	pDevice->SetFVF(LINE_CUSTOMVERTEX::D3DFVF_LINE);

	if (colorBlend)
	{
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	}

	pDevice->DrawPrimitive(D3DPT_LINELIST, 0, 1);

	if (colorBlend)
	{
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	}
}

void DxLine::SetLength(const int& length)
{
	_length = length;
	_vertex[0]._position = D3DXVECTOR3(-length / 2.0f, 0.0f, 0.0f);
	_vertex[1]._position = D3DXVECTOR3(length / 2.0f, 0.0f, 0.0f);
}

void DxLine::SetColor(
	const D3DCOLOR& colorL,
	const D3DCOLOR& colorR)
{
	_vertex[0]._color = colorL;
	_vertex[1]._color = colorR;
}

void DxLine::SetColor(const D3DCOLOR& color)
{
	SetColor(color, color);
}

void DxLine::SetColor(const BYTE& r, const BYTE& g, const BYTE& b)
{
	SetColor(D3DCOLOR_XRGB(r, g, b));
}

void DxLine::ResetVertex()
{
	void* pVertex = 0;
	mp_vertexBuffer->Lock(0, sizeof(_vertex), (void**)&pVertex, 0);
	memcpy(pVertex, _vertex, sizeof(_vertex));
	mp_vertexBuffer->Unlock();
}
