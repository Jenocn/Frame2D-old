#ifndef _ANIMATION_H_H_
#define _ANIMATION_H_H_

#include "Sprite.h"

NS_F2D_BEGIN

// 动画类
class Animation : public Sprite
{
public:
	/*
	函数功能:创建动画对象
	参数1:动画图片文件路径
	参数2:行数
	参数3:列数
	参数4:动画时间间隔,单位:秒
	参数5:动画播放的次数
	参数6:需要透明的颜色
	*/
	static Animation* Create(const string& path,
		const int& row, const int& col,
		const float& animationInterval = 0,
		const int& count = -1,
		const DWORD& colorKey = 0);

	virtual ~Animation();

	/*
	函数功能:初始化动画行列
	参数1:行
	参数2:列
	参数3:动画时间间隔,单位:秒
	参数4:播放的次数
	*/
	bool InitAnimation(const int& row, const int& col,
		const float& animationInterval = 0,
		const int& count = -1);

	virtual void Update(const float& delta);

	/*
	函数功能:设置动画帧间隔时间
	参数1:间隔时间,单位:秒
	说明:最小为0
	*/
	void SetAnimationInterval(const float& second);

	/*
	函数功能:暂停动画
	*/
	void PauseAnimation();

	/*
	函数功能:播放动画
	说明:只有暂停状态下可用
	*/
	void PlayAnimation();

	/*
	函数功能:返回是否暂停的状态
	*/
	bool IsPause() const;

	/*
	函数功能:重置动画帧为初始状态
	*/
	void ResetAnimation();

	/*
	函数功能:设置动画循环播放次数
	参数1:播放的次数,默认是-1,表示无限循环,如果
	设置为0,则一次都不会播放
	*/
	void SetAnimationCount(const int& count = -1);

	/*
	函数功能:获取当前横向帧
	*/
	int GetFrameX() const;

	/*
	函数功能:获取当前纵向帧
	*/
	int GetFrameY() const;

	/*
	函数功能:获得当前剩余次数
	说明:如果是-1表示无限循环
	*/
	int GetAnimationCount() const;


protected:
	Animation()
	: _framePosX(0)
	, _framePosY(0)
	, _row(1)
	, _col(1)
	, _animationInterval(0)
	, _tempInterval(0)
	, _count(-1)
	, _pause(false)
	{}

private:
	Animation(Animation&);
	Animation& operator=(Animation&);

private:
	// 当前x轴第几帧
	int _framePosX;
	// 当前y轴第几帧
	int _framePosY;
	int _row;
	int _col;

	// 动画时间间隔
	float _animationInterval;
	float _tempInterval;

	// 动画播放的次数
	int _count;

	// 是否暂停
	bool _pause;
};

NS_F2D_END

#endif