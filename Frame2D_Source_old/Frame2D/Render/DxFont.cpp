#include "DxFont.h"
#include "DxFontCache.h"

DxFont* DxFont::CreateWithSystemFont(
	const string& fontName,
	const int& fontSize,
	bool italic)
{
	DxFont* font = new(nothrow) DxFont();
	assert(font &&
		font->InitWithSystemFont(fontName, fontSize, italic) &&
		"DxFont Create Failed!");

	return font;
}

void DxFont::Release()
{
	mp_font = 0;

	delete this;
}


bool DxFont::InitWithSystemFont(
	const string& fontName,
	const int& fontSize,
	bool italic)
{
	if (fontName.compare("") == 0)
	{
		return false;
	}

	if (fontSize <= 0)
	{
		return false;
	}

	const DxFontInfo* info =
		DxFontCache::getInstance()->LoadDxFontFromFile(
		fontName, fontSize, italic);

	if (info == 0)
	{
		return false;
	}

	mp_font = info->GetDxFont();

	return true;
}

void DxFont::Draw(
	const string& text,
	const int& charCount,
	const LPRECT& pRect,
	const D3DCOLOR& color,
	const DWORD& format)
{
	mp_font->DrawText(
		NULL, text.c_str(), charCount, pRect, format, color);
	
}
