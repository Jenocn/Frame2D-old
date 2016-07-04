#include "DxFontCache.h"
#include "D3DManager.h"

static DxFontCache* pInstance = 0;

DxFontCache* DxFontCache::getInstance()
{
	if (pInstance == 0)
	{
		pInstance = new DxFontCache();
	}

	return pInstance;
}

void DxFontCache::Release()
{
	ClearDxFontCache();

	delete this;
	pInstance = 0;
}

const DxFontInfo* DxFontCache::LoadDxFontFromFile(
	const string& fontName,
	const int& fontSize,
	bool italic)
{
	vector<DxFontInfo*>::iterator ite = m_dxfont_list.begin();
	while (ite != m_dxfont_list.end())
	{
		if ((*ite)->GetFontName() == fontName &&
			(*ite)->GetFontSize() == fontSize &&
			(*ite)->IsItalic() == italic)
		{
			return (*ite);
		}

		++ite;
	}

	LPD3DXFONT font;

	if (S_OK != D3DXCreateFont(
		D3DManager::getInstance()->getDevice(),
		fontSize, 0, 0, 1, italic,
		DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
		DEFAULT_QUALITY, 0, fontName.c_str(), &font))
	{
		return 0;
	}

	DxFontInfo* info = new DxFontInfo(fontName, font, fontSize, italic);
	m_dxfont_list.push_back(info);

	return info;
}

void DxFontCache::ClearDxFontCache()
{
	vector<DxFontInfo*>::iterator ite = m_dxfont_list.begin();
	while (ite != m_dxfont_list.end())
	{
		(*ite)->GetDxFont()->Release();
		delete (*ite);
		ite = m_dxfont_list.erase(ite);
	}
}
