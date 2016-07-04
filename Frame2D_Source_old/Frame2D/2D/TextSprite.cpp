#include "TextSprite.h"
#include "Director.h"

USING_NS_F2D

TextSprite* TextSprite::Create(
	const string& text,
	const string& fontName,
	const int& fontSize,
	const int& width,
	const int& height,
	bool italic,
	const ENUM_F2D_DIRECTION& dir)
{
	TextSprite* sprite = new TextSprite();
	assert(sprite &&
		sprite->InitWithSystemFont(text,
		fontName, fontSize, width, height, italic, dir) &&
		"TextSprite Create Failed!");

	return sprite;
}

bool TextSprite::InitWithSystemFont(
	const string& text,
	const string& fontName,
	const int& fontSize,
	const int& width,
	const int& height,
	bool italic,
	const ENUM_F2D_DIRECTION& dir)
{
	_font = DxFont::CreateWithSystemFont(fontName, fontSize, italic);
	SetText(text);
	SetWidth(width);
	SetHeight(height);

	if (width == F2D_NORMAL)
	{
		SetWidth(Director::getInstance()->GetViewRect().right);
	}
	if (height == F2D_NORMAL)
	{
		SetHeight(Director::getInstance()->GetViewRect().bottom);
	}

	SetTextFormat(dir);

	return true;
}

void TextSprite::SetText(const string& text)
{
	_text = text;
}

string TextSprite::GetText()
{
	return _text;
}

void TextSprite::Update(const float& delta)
{
	Element::Update(delta);

	if (GetPositionX() + GetWidth() < 0 ||
		GetPositionY() + GetHeight() < 0 ||
		GetPositionX() > Director::getInstance()->GetViewRect().right ||
		GetPositionY() > Director::getInstance()->GetViewRect().bottom)
	{
		SetVisible(false);
	}
}

void TextSprite::Render()
{
	Element::Render();

	RECT rect;
	rect.left = (LONG)GetPositionX();
	rect.top = (LONG)GetPositionY();
	rect.right = rect.left + (LONG)GetWidth();
	rect.bottom = rect.top + (LONG)GetHeight();

	_font->Draw(_text, -1, &rect, GetColor(), _format);
}

void TextSprite::SetTextFormat(const ENUM_F2D_DIRECTION& dir)
{
	switch (dir)
	{
	case F2D_DIRECTION_CENTER:
		_format = DT_CENTER | DT_VCENTER;
		break;
	case F2D_DIRECTION_UP:
		_format = DT_TOP | DT_CENTER;
		break;
	case F2D_DIRECTION_DOWN:
		_format = DT_BOTTOM | DT_CENTER;
		break;
	case F2D_DIRECTION_LEFT:
		_format = DT_LEFT | DT_VCENTER;
		break;
	case F2D_DIRECTION_RIGHT:
		_format = DT_RIGHT | DT_VCENTER;
		break;
	case F2D_DIRECTION_UPLEFT:
		_format = DT_TOP | DT_LEFT;
		break;
	case F2D_DIRECTION_UPRIGHT:
		_format = DT_TOP | DT_RIGHT;
		break;
	case F2D_DIRECTION_DOWNLEFT:
		_format = DT_BOTTOM | DT_LEFT;
		break;
	case F2D_DIRECTION_DOWNRIGHT:
		_format = DT_BOTTOM | DT_RIGHT;
		break;
	}
}

void TextSprite::SetTextShowRect(
	const int& positionX,
	const int& positionY,
	const int& width,
	const int& height)
{
	SetPosition((float)positionX, (float)positionY);
	SetWidth(width);
	SetHeight(height);
}

void TextSprite::SetColor(const DWORD& color)
{
	_color = color;
}

DWORD TextSprite::GetColor() const
{
	return _color;
}
