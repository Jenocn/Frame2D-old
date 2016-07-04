#ifndef _TEXT_SPRITE_H_H_
#define _TEXT_SPRITE_H_H_

#include "Element.h"

NS_F2D_BEGIN

/*
文本精灵,用于渲染文本
*/
class TextSprite : public Element
{
public:
	/*
		函数功能:创建字体精灵并初始化
		返回值:返回已经初始化的字体精灵对象
		参数1:要渲染的文本内容(也可通过SetText设置)
		参数2:字体名称
		参数3:字体的大小
		参数4:指定字体的显示范围,最多能显示的像素宽
		参数5:指定字体的显示范围,最多能显示的像素高
		参数6:是否斜体
		参数7:在指定的范围中将字体显示在哪个区域
	*/
	static TextSprite* Create(
		const string& text,
		const string& fontName,
		const int& fontSize,
		const int& width = F2D_NORMAL,
		const int& height = F2D_NORMAL,
		bool italic = false,
		const ENUM_F2D_DIRECTION& dir = F2D_DIRECTION_UPLEFT);

	/*
	函数功能:初始化字体精灵
	返回值:初始化成功返回真,否则返回假
	参数1:要渲染的文本内容(也可通过SetText设置)
	参数2:字体名称
	参数3:字体的大小
	参数4:指定字体的显示范围,最多能显示的像素宽
	参数5:指定字体的显示范围,最多能显示的像素高
	参数6:是否斜体
	参数7:在指定的范围中将字体显示在哪个区域
	*/
	bool InitWithSystemFont(
		const string& text,
		const string& fontName,
		const int& fontSize,
		const int& width = F2D_NORMAL,
		const int& height = F2D_NORMAL,
		bool italic = false,
		const ENUM_F2D_DIRECTION& dir = F2D_DIRECTION_UPLEFT);

	/*
	函数功能:设置要显示的文本
	参数:文本内容
	*/
	void SetText(const string& text);

	/*
	获得当前的文本内容
	*/
	string GetText();

	/*
	*/
	virtual void Update(const float& delta);

	virtual void Render();

	/*
	函数功能:设置文本在显示范围内的位置
	*/
	void SetTextFormat(const ENUM_F2D_DIRECTION& dir);

	/*
	函数功能:设置文本显示的范围
	*/
	void SetTextShowRect(
		const int& positionX,
		const int& positionY,
		const int& width,
		const int& height);

	/*
	函数功能:设置颜色
	*/
	void SetColor(const DWORD& color);

	/*
	函数功能:获取颜色
	*/
	DWORD GetColor() const;

private:
	TextSprite()
	: _text("")
	, _format(0)
	, _color(0xffffffff)
	{}
	TextSprite(TextSprite&);
	TextSprite& operator=(TextSprite&);

private:
	DxFont* _font;
	string _text;
	DWORD _format;
	DWORD _color;
};

NS_F2D_END

#endif