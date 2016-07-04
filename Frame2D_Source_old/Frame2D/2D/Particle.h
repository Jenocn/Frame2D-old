#ifndef _PARTICLE_H_H_
#define _PARTICLE_H_H_

#include "Object.h"

NS_F2D_BEGIN

class Particle : public Object
{
public:
	/*
		函数功能:创建粒子
	*/
	static Particle* Create();
	static Particle* Create(const string& path, const D3DCOLOR& colorKey = 0);

	/*
		函数功能:如果有继承的子类需要释放独立的内存,则
		会在这里释放
	*/
	virtual ~Particle();

	/*
		初始化,主要是创建点精灵
	*/
	bool Init();

	/*
		初始化,主要是创建点精灵
	*/
	bool InitWithFile(const string& path, const D3DCOLOR& colorKey = 0);

	/*
		函数功能:更新数据
		说明:通过继承实现不同的行为
	*/
	virtual void Update(const float& delta);

	/*
		函数功能:渲染
	*/
	void Render();

	/*
		函数功能:释放内存,并delete自身
	*/
	void Release();

	// 设置是否有效
	void SetVisible(bool visible);

	/*
		函数功能:是否可见,即是否有效
	*/
	bool IsVisible();

	// Setter
	void SetPosition(
		const float& positionX,
		const float& positionY);
	void SetPosition(
		const float& positionX,
		const float& positionY,
		const float& positionZ);
	void SetPositionX(const float& positionX);
	void SetPositionY(const float& positionY);
	void SetPositionZ(const float& positionZ);

	void SetColor(byte r, byte g, byte b);
	void SetColor(const D3DCOLOR& color);
	void SetAlpha(byte alpha);
	void SetColorR(byte r);
	void SetColorG(byte g);
	void SetColorB(byte b);

	// 速度,像素/每秒
	void SetVelocity(
		const float& x,
		const float& y);
	void SetVelocity(
		const float& x,
		const float& y,
		const float& z);
	// 速度,像素/每秒
	void SetVelocityX(const float& x);
	// 速度,像素/每秒
	void SetVelocityY(const float& y);
	// 速度,像素/每秒
	void SetVelocityZ(const float& z);

	// 加速度,速度/每秒
	void SetAcceleration(
		const float& x,
		const float& y);
	// 加速度,速度/每秒
	void SetAcceleration(
		const float& x,
		const float& y,
		const float& z);
	// 加速度,速度/每秒
	void SetAccelerationX(const float& x);
	// 加速度,速度/每秒
	void SetAccelerationY(const float& y);
	// 加速度,速度/每秒
	void SetAccelerationZ(const float& z);

	/* 
	设置持续时间,单位:秒
	*/
	void SetDuration(const float& duration);

	void SetScale(const float& scale);

	// Getter
	float GetPositionX() const;
	float GetPositionY() const;
	float GetPositionZ() const;

	DWORD GetColor() const;
	byte GetAlpha() const;
	byte GetColorR() const;
	byte GetColorG() const;
	byte GetColorB() const;

	float GetVelocityX() const;
	float GetVelocityY() const;
	float GetVelocityZ() const;

	float GetAccelerationX() const;
	float GetAccelerationY() const;
	float GetAccelerationZ() const;

	float GetDuration() const;

	float GetScale() const;

	void SetTextureBlend(bool enable);

	bool IsTextureBlend() const;

protected:
	Particle()
	: _pointSprite(0)
	, _alpha(255)
	, _r(255)
	, _g(255)
	, _b(255)
	, _positionX(0)
	, _positionY(0)
	, _positionZ(0)
	, _velocityX(0)
	, _velocityY(0)
	, _velocityZ(0)
	, _accelerationX(0)
	, _accelerationY(0)
	, _accelerationZ(0)
	, _duration(0)
	, _scale(1.0f)
	, _visible(true)
	, _textureBlend(true)
	{}

private:
	Particle(Particle&);
	Particle& operator=(Particle&);

private:
	// 点精灵对象
	DxPoint* _pointSprite;
	// 粒子的颜色
	byte _alpha;
	byte _r, _g, _b;
	// 坐标
	float _positionX;
	float _positionY;
	float _positionZ;
	// 粒子的速度
	float _velocityX;
	float _velocityY;
	float _velocityZ;
	// 粒子的加速度
	float _accelerationX;
	float _accelerationY;
	float _accelerationZ;
	// 粒子存在的时间
	float _duration;
	// 粒子的缩放比例
	float _scale;
	// 粒子是否有效
	bool _visible;
	// 是否颜色融合高亮
	bool _textureBlend;
};

NS_F2D_END

#endif