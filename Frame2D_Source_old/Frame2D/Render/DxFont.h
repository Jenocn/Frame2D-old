#ifndef _DX_FONT_H_H_
#define _DX_FONT_H_H_

#include "DX9.h"

class DxFont
{
public:
	/*
		函数功能:创建一个系统字体
		返回值:返回创建并初始化过的字体对象
		参数1:字体名称
		参数2:字体大小
		参数3:是否斜体
	*/
	static DxFont* CreateWithSystemFont(
		const string& fontName,
		const int& fontSize,
		bool italic = false);

	/*
		函数功能:释放内存空间并delete自身
		说明:缓存的字体不会在这里释放
	*/
	void Release();

	/*
		函数功能:初始化系统字体
		返回值:如果初始化成功返回真,否则返回假
		参数1:字体名称
		参数2:字体大小
		参数3:是否斜体
	*/
	bool InitWithSystemFont(
		const string& fontName,
		const int& fontSize,
		bool italic = false);


	void Draw(
		const string& text,
		const int& charCount,
		const LPRECT& pRect,
		const D3DCOLOR& color = D3DCOLOR_XRGB(0, 0, 0),
		const DWORD& format = DT_TOP | DT_LEFT);



private:
	LPD3DXFONT mp_font;
};

#endif