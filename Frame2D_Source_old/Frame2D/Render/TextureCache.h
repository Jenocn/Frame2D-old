#ifndef _TEXTURE_CACHE_H_H_
#define _TEXTURE_CACHE_H_H_

#include "DX9.h"

// 纹理信息
class TextureInfo
{
public:
	/*
		构造函数:
		参数1:路径名
		参数2:d3d纹理对象的指针
		参数3:d3d纹理信息
	*/
	explicit TextureInfo(
		const string& path,
		const LPDIRECT3DTEXTURE9& texture,
		const D3DXIMAGE_INFO& info
		)
	{
		this->path = path;
		this->texture = texture;
		this->info = info;
	}

	// 获取路径名
	const string& GetPath() const
	{
		return path;
	}

	// 获取d3d纹理对象指针
	LPDIRECT3DTEXTURE9 GetTexture() const
	{
		return texture;
	}

	// 获取d3d纹理信息
	D3DXIMAGE_INFO GetTextureInfo() const
	{
		return info;
	}

private:
	// 路径名
	string path;
	LPDIRECT3DTEXTURE9 texture;
	D3DXIMAGE_INFO info;
};

// 纹理缓存类
class TextureCache
{
public:
	static TextureCache* getInstance();

	// 释放内存,并delete自身
	void Release();

	/*
	函数功能:通过文件路径加载纹理
	返回值:如果加载成功,那么返回一个纹理信息的结构体对象
	参数1:文件路径名
	参数2:需要透明的颜色
	*/
	const TextureInfo* LoadTextureFromFile(const string& path, const D3DCOLOR& colorKey = 0);

	/*
		函数功能:清空纹理缓存列表
		*/
	void ClearTextureCache();

private:
	TextureCache() {}
	TextureCache(TextureCache&);
	TextureCache& operator=(TextureCache&);

private:
	// 缓存列表
	vector<TextureInfo*> m_texture_list;
};

#endif