#ifndef _DX_FONT_CHACHE_H_H_
#define _DX_FONT_CHACHE_H_H_

#include "DX9.h"

class DxFontInfo
{
public:
	/*
		构造函数:
		参数1:字体名称
		参数2:directx字体对象
		参数3:字体大小
	*/
	explicit DxFontInfo(
		const string& fontName,
		const LPD3DXFONT& dxfont,
		const int& fontSize,
		bool italic)
	{
		this->fontName = fontName;
		this->dxfont = dxfont;
		this->fontSize = fontSize;
		this->italic = italic;
	}

	// 获取字体名称
	const string& GetFontName() const
	{
		return fontName;
	}

	// 获取字体对象
	LPD3DXFONT GetDxFont() const
	{
		return dxfont;
	}

	// 获取字体大小
	int GetFontSize() const
	{
		return fontSize;
	}

	// 是否斜体
	bool IsItalic() const
	{
		return italic;
	}

private:
	string fontName;
	LPD3DXFONT dxfont;
	int fontSize;
	bool italic;
};

class DxFontCache
{
public:
	static DxFontCache* getInstance();

	/*
		函数功能:释放内存,并delete自身
	*/
	void Release();

	/*
		函数功能:通过字体名称和字体大小加载字体
		返回值:如果加载成功,那么返回一个字体信息的结构体对象
		参数1:字体名称
		参数2:字体大小
		参数3:是否斜体
	*/
	const DxFontInfo* LoadDxFontFromFile(
		const string& fontName,
		const int& fontSize,
		bool italic);

	/*
		函数功能:清空缓存列表
	*/
	void ClearDxFontCache();

private:
	DxFontCache() {}
	DxFontCache(DxFontCache&);
	DxFontCache& operator=(DxFontCache&);

private:
	// 缓存列表
	vector<DxFontInfo*> m_dxfont_list;
};

#endif