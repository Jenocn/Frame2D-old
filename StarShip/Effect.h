#ifndef _EFFECT_H_H_
#define _EFFECT_H_H_

#include <Frame2D.h>

// 特效类
class Effect : public Frame2D::Animation
{
public:
	static Effect* Create(const string& name);

	virtual ~Effect();

	bool InitData(const string& name);

	virtual void Update(const float& delta);

	virtual void Render();

	// setter
	void SetOffsetX(const float& x);
	void SetOffsetY(const float& y);
	void SetDurationTime(const float& duration);

	// getter
	float GetOffsetX() const;
	float GetOffsetY() const;
	float GetDurationTime() const;

protected:
	Effect()
	: _offsetX(0)
	, _offsetY(0)
	, _durationTime(0)
	{}

private:
	Effect(Effect&);
	Effect& operator=(Effect&);

private:
	float _offsetX; // x轴偏移量
	float _offsetY; // y轴偏移量
	float _durationTime; // 持续时间
};

#endif