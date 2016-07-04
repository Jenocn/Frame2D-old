#include "TextureCache.h"
#include "D3DManager.h"

static TextureCache* pInstance = 0;

TextureCache* TextureCache::getInstance()
{
	if (pInstance == 0)
	{
		pInstance = new TextureCache();
	}

	return pInstance;
}

void TextureCache::Release()
{
	ClearTextureCache();

	delete this;
	pInstance = 0;
}

const TextureInfo* TextureCache::LoadTextureFromFile(const string& path, const D3DCOLOR& colorKey)
{
	vector<TextureInfo*>::iterator ite = m_texture_list.begin();
	while (ite != m_texture_list.end())
	{
		if ((*ite)->GetPath().compare(path) == 0)
		{
			return (*ite);
		}

		++ite;
	}

	LPDIRECT3DDEVICE9 pDevice = D3DManager::getInstance()->getDevice();

	LPDIRECT3DTEXTURE9 texture;
	D3DXIMAGE_INFO info;

	if (S_OK != D3DXCreateTextureFromFileEx(
		pDevice,
		path.c_str(),
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT_NONPOW2,
		1,
		D3DPOOL_DEFAULT,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		colorKey,
		&info,
		NULL,
		&texture))
	{
		return 0;
	}

	LPDIRECT3DVERTEXBUFFER9 vertexBuffer = 0;
	LPDIRECT3DINDEXBUFFER9 indexBuffer = 0;
	int width = info.Width;
	int height = info.Height;

	TextureInfo* textureInfo = new TextureInfo(
		path,
		texture,
		info);
	m_texture_list.push_back(textureInfo);

	return textureInfo;
}

void TextureCache::ClearTextureCache()
{
	vector<TextureInfo*>::iterator ite = m_texture_list.begin();

	while (ite != m_texture_list.end())
	{
		(*ite)->GetTexture()->Release();
		delete *ite;
		ite = m_texture_list.erase(ite);
	}
}
