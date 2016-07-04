#include "Texture2D.h"
#include "TextureCache.h"
#include "D3DManager.h"

Texture2D* Texture2D::CreateWithInit(const string& path, const D3DCOLOR& colorKey)
{
	Texture2D* texture = new(std::nothrow) Texture2D();
	assert(texture && texture->InitWithFile(path, colorKey) && "Texture2D Create Failed!");

	return texture;
}

bool Texture2D::InitWithFile(const string& path, const D3DCOLOR& colorKey)
{
	if (path.compare("") == 0)
	{
		return false;
	}

	// 创建纹理并获取纹理
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

	LPDIRECT3DDEVICE9 pDevice = D3DManager::getInstance()->getDevice();

	// 创建顶点缓存,目标是两个三角形拼成的四边形
	pDevice->CreateVertexBuffer(4 * sizeof(TEXTURE2D_CUSTOMVERTEX), 0,
		TEXTURE2D_CUSTOMVERTEX::D3DFVF_TEXTURE2D,
		D3DPOOL_DEFAULT, &mp_vertexBuffer, NULL);
	// 创建索引缓存
	pDevice->CreateIndexBuffer(6 * sizeof(WORD), 0,
		D3DFMT_INDEX16, D3DPOOL_DEFAULT, &mp_indexBuffer, NULL);

	// 获取纹理的宽高
	_width = _textureWidth = textureInfo->GetTextureInfo().Width;
	_height = _textureHeight = textureInfo->GetTextureInfo().Height;

	// 左上角
	_vertex[0]._position = D3DXVECTOR3(-_width / 2.0f, _height / 2.0f, 0);
	_vertex[0]._color = 0xffffffff;
	_vertex[0]._u = 0;
	_vertex[0]._v = 0;
	// 右上角
	_vertex[1]._position = D3DXVECTOR3(_width / 2.0f, _height / 2.0f, 0);
	_vertex[1]._color = 0xffffffff;
	_vertex[1]._u = 1;
	_vertex[1]._v = 0;
	// 右下角
	_vertex[2]._position = D3DXVECTOR3(_width / 2.0f, -_height / 2.0f, 0);
	_vertex[2]._color = 0xffffffff;
	_vertex[2]._u = 1;
	_vertex[2]._v = 1;
	// 左下角
	_vertex[3]._position = D3DXVECTOR3(-_width / 2.0f, -_height / 2.0f, 0);
	_vertex[3]._color = 0xffffffff;
	_vertex[3]._u = 0;
	_vertex[3]._v = 1;

	ResetVertex();

	WORD index[] = {
		0, 1, 2,
		0, 2, 3
	};

	WORD* pIndex = 0;
	mp_indexBuffer->Lock(0, 0, (void**)&pIndex, 0);
	memcpy(pIndex, index, sizeof(index));
	mp_indexBuffer->Unlock();

	return true;
}

void Texture2D::Release()
{
	if (mp_vertexBuffer)
	{
		mp_vertexBuffer->Release();
		mp_vertexBuffer = 0;
	}

	if (mp_indexBuffer)
	{
		mp_indexBuffer->Release();
		mp_indexBuffer = 0;
	}

	mp_texture = 0;

	delete this;
}

void Texture2D::Draw(
	const float& positionX,
	const float& positionY,
	const float& positionZ,
	const float& angleX,
	const float& angleY,
	const float& angleZ,
	const float& anchorX,
	const float& anchorY,
	const float& scaleX,
	const float& scaleY)
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

	if (_bTextureBlend)
	{
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	}

	pDevice->SetStreamSource(0, mp_vertexBuffer, 0, sizeof(TEXTURE2D_CUSTOMVERTEX));
	pDevice->SetFVF(TEXTURE2D_CUSTOMVERTEX::D3DFVF_TEXTURE2D);
	pDevice->SetIndices(mp_indexBuffer);
	pDevice->SetTexture(0, mp_texture);

	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);

	if (_bTextureBlend)
	{
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	}
}

void Texture2D::SetRenderRect(const RECT& destRect)
{
	_vertex[0]._u = destRect.left / static_cast<float>(_textureWidth);
	_vertex[0]._v = destRect.top / static_cast<float>(_textureHeight);
	_vertex[1]._u = destRect.right / static_cast<float>(_textureWidth);
	_vertex[1]._v = destRect.top / static_cast<float>(_textureHeight);
	_vertex[2]._u = destRect.right / static_cast<float>(_textureWidth);
	_vertex[2]._v = destRect.bottom / static_cast<float>(_textureHeight);
	_vertex[3]._u = destRect.left / static_cast<float>(_textureWidth);
	_vertex[3]._v = destRect.bottom / static_cast<float>(_textureHeight);

	for (int i = 0; i < 4; ++i)
	{
		if (_vertex[i]._u < 0)
		{
			_vertex[i]._u = 0;
		}
		if (_vertex[i]._u > 1)
		{
			_vertex[i]._u = 1;
		}
		if (_vertex[i]._v < 0)
		{
			_vertex[i]._v = 0;
		}
		if (_vertex[i]._v > 1)
		{
			_vertex[i]._v = 1;
		}
	}

	_width = (_vertex[1]._u - _vertex[0]._u) * _textureWidth;
	_height = (_vertex[3]._v - _vertex[0]._v) * _textureHeight;

	// 左上角
	_vertex[0]._position = D3DXVECTOR3(-_width / 2.0f, _height / 2.0f, 0);
	// 右上角
	_vertex[1]._position = D3DXVECTOR3(_width / 2.0f, _height / 2.0f, 0);
	// 右下角
	_vertex[2]._position = D3DXVECTOR3(_width / 2.0f, -_height / 2.0f, 0);
	// 左下角
	_vertex[3]._position = D3DXVECTOR3(-_width / 2.0f, -_height / 2.0f, 0);
}

void Texture2D::SetColor(
	const D3DCOLOR& colorLT,
	const D3DCOLOR& colorRT,
	const D3DCOLOR& colorRB,
	const D3DCOLOR& colorLB
	)
{
	_vertex[0]._color = colorLT;
	_vertex[1]._color = colorRT;
	_vertex[2]._color = colorRB;
	_vertex[3]._color = colorLB;
}

void Texture2D::SetColor(const D3DCOLOR& color)
{
	SetColor(color, color, color, color);
}

void Texture2D::SetColor(const BYTE& r, const BYTE& g, const BYTE& b)
{
	SetColor(D3DCOLOR_XRGB(r, g, b));
}

void Texture2D::ResetVertex()
{
	void* pVertex = 0;
	mp_vertexBuffer->Lock(0, sizeof(_vertex), (void**)&pVertex, 0);
	memcpy(pVertex, _vertex, sizeof(_vertex));
	mp_vertexBuffer->Unlock();
}

int Texture2D::GetWidth() const
{
	return _width;
}

int Texture2D::GetHeight() const
{
	return _height;
}

int Texture2D::GetTextureWidth() const
{
	return _textureWidth;
}

int Texture2D::GetTextureHeight() const
{
	return _textureHeight;
}

void Texture2D::SetTextureBlend(bool enable)
{
	_bTextureBlend = enable;
}
