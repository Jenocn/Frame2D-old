#ifndef _SPRITE_H_H_
#define _SPRITE_H_H_

#include "Element.h"

NS_F2D_BEGIN

/*
	精灵
*/
class Sprite : public Element
{
public:
	/*
		函数功能:创建一个精灵,并且通过文件路径加载纹理
		说明:会自动调用初始化函数,因此无需再初始化
		参数1:文件路径
		参数2:需要将之透明的颜色
	*/
	static Sprite* Create(const string& path, const D3DCOLOR& colorKey = 0);

	virtual ~Sprite();

	/*
	函数功能:通过路径初始化精灵
	返回值:如果初始化成功则返回真,否则返回假
	参数1:文件路径
	参数2:需要将之透明的颜色
	*/
	bool InitWithFile(const string& path, const D3DCOLOR& colorKey = 0);

	/*
	函数功能:切换纹理
	参数1:纹理路径
	参数2:需要将之透明的颜色
	*/
	void SetTexture(const string& path, const D3DCOLOR& colorKey = 0);

	/*
	函数功能:切换纹理
	参数1:纹理对象指针
	*/
	void SetTexture(Texture2D* texture);

	virtual void Update(const float& delta);

	virtual void Render();

	/*
		函数功能:重置顶点状态
		说明:当使用过设置颜色,设置目标矩形的操作之后,
		请务必调用该函数确保最终效果能够修改到纹理
		上,否则修改无效
	*/
	virtual void ResetVertex();

	/*
	获得左上角的颜色
	*/
	D3DCOLOR GetColorLT() const;

	/*
	获得右上角的颜色
	*/
	D3DCOLOR GetColorRT() const;

	/*
	获得右下角的颜色
	*/
	D3DCOLOR GetColorRB() const;

	/*
	获得左下角的颜色
	*/
	D3DCOLOR GetColorLB() const;

	/*
	设置整体颜色
	*/
	void SetColor(const D3DCOLOR& color);

	/*
	函数功能:设置四个方向的颜色值
	参数1:左上角
	参数2:右上角
	参数3:右下角
	参数4:左下角
	*/
	void SetColor(
		const D3DCOLOR& colorLT,
		const D3DCOLOR& colorRT,
		const D3DCOLOR& colorRB,
		const D3DCOLOR& colorLB);

	/*
	设置整体透明度
	*/
	void SetAlpha(byte alpha);

	/*
	设置整体颜色(rgb)
	*/
	void SetColorRGB(byte r, byte g, byte b);

	/*
	设置左上角颜色
	*/
	void SetColor_LT(const D3DCOLOR& color);

	/*
	设置左上角颜色
	*/
	void SetColorRGB_LT(byte r, byte g, byte b);

	/*
	设置左上角透明度
	*/
	void SetColorAlpha_LT(byte alpha);

	/*
	设置右上角颜色
	*/
	void SetColor_RT(const D3DCOLOR& color);

	/*
	设置右上角颜色
	*/
	void SetColorRGB_RT(byte r, byte g, byte b);

	/*
	设置右上角透明度
	*/
	void SetColorAlpha_RT(byte alpha);

	/*
	设置右下角颜色
	*/
	void SetColor_RB(const D3DCOLOR& color);

	/*
	设置右下角颜色
	*/
	void SetColorRGB_RB(byte r, byte g, byte b);

	/*
	设置右下角透明度
	*/
	void SetColorAlpha_RB(byte alpha);

	/*
	设置左下角颜色
	*/
	void SetColor_LB(const D3DCOLOR& color);

	/*
	设置左下角颜色
	*/
	void SetColorRGB_LB(byte r, byte g, byte b);

	/*
	设置左下角透明度
	*/
	void SetColorAlpha_LB(byte alpha);

	/*
	获得渲染的目标矩形区域
	*/
	RECT GetRenderRect() const;

	/*
	设置渲染的目标矩形区域
	*/
	void SetRenderRect(const RECT& rect);

	/*
	设置渲染的目标矩形区域
	参数1~2:left, top
	参数3~4:right, bottom
	*/
	void SetRenderRect(
		const int& left,
		const int& top,
		const int& right,
		const int& bottom);

	/*
	获得纹理的宽
	*/
	int GetTextureWidth() const;

	/*
	获得纹理的高
	*/
	int GetTextureHeight() const;

	// 开启纹理融合
	void SetTextureBlend(bool enable);



protected:
	Sprite()
	: _texture2d(0)
	, _aLT(255), _rLT(255), _gLT(255), _bLT(255)
	, _aRT(255), _rRT(255), _gRT(255), _bRT(255)
	, _aLB(255), _rLB(255), _gLB(255), _bLB(255)
	, _aRB(255), _rRB(255), _gRB(255), _bRB(255)
	{}

private:
	Sprite(Sprite&);
	Sprite& operator=(Sprite&);

private:
	Texture2D* _texture2d;
	float _aLT, _rLT, _gLT, _bLT;
	float _aRT, _rRT, _gRT, _bRT;
	float _aLB, _rLB, _gLB, _bLB;
	float _aRB, _rRB, _gRB, _bRB;
	RECT _renderRect;
};

NS_F2D_END

#endif