#ifndef _PARTICLE_SYSTEM_H_H_
#define _PARTICLE_SYSTEM_H_H_

#include "Object.h"

NS_F2D_BEGIN

class Particle;

class ParticleSystem : public Object
{
public: 
	static ParticleSystem* Create();

	static ParticleSystem* Create(
		const float& positionX,
		const float& positionY,
		const float& positionZ,
		const float& launcherDuration,
		const float& launcherInterval,
		const float& systemDuration,
		const int& maxNums,
		const int& boundBoxPositionX,
		const int& boundBoxPositionY,
		const int& boundBoxWidth,
		const int& boundBoxHeight);

	/*
	函数功能:添加粒子纹理
	说明:会从添加的纹理中随机选取
	参数1:粒子的纹理路径
	*/
	void AddParticleTexture(const string& texturePath);

	/*
	函数功能:设置粒子数据
	参数1:粒子的存活时间
	参数2~4:粒子的平均速度
	参数5~7:粒子的加速度
	参数8:粒子的颜色
	参数9:粒子的缩放比例
	参数11:颜色高亮
	*/
	void SetParticleData(
		const float& duration,
		const float& velocityX,
		const float& velocityY,
		const float& velocityZ,
		const float& accelerationX = 0,
		const float& accelerationY = 0,
		const float& accelerationZ = 0,
		float alpha = 255, float r = 255,
		float g = 255, float b = 255,
		const float& scale = 1.0f,
		bool textureBlendEnable = true);

	/*
	函数功能:通过文件初始化粒子的数据
	参数1:粒子数据文件路径
	*/
	void SetParticleDataFromFile(const string& path);

	/*
	函数功能:设置粒子的偏移数据
	说明:数值的正负范围,颜色只有正范围
	参数1:粒子的存活时间的偏移值
	参数2~4:粒子的坐标偏移值
	参数5~7:粒子的平均速度偏移值
	参数8~10:粒子的加速度偏移值
	参数11:粒子的颜色偏移值
	参数12:粒子的缩放比例偏移值
	*/
	void SetParticleOffsetData(
		const float& durationOffset,
		const float& positionOffsetX,
		const float& positionOffsetY,
		const float& positionOffsetZ,
		const float& velocityOffsetX,
		const float& velocityOffsetY,
		const float& velocityOffsetZ,
		const float& accelerationOffsetX,
		const float& accelerationOffsetY,
		const float& accelerationOffsetZ,
		float alphaOffset, float rOffset,
		float gOffset, float bOffset,
		const float& scaleOffset);

	/*
		函数功能:子类用于释放独立的内存
	*/
	virtual ~ParticleSystem();

	/*
		函数功能:初始化粒子系统
	*/
	virtual bool Init();

	/*
		函数功能:释放内存,并delete自身
	*/
	void Release();

	/*
		函数功能:更新数据
		说明:如果要继承该类,请务必调用父类的该函数
	*/
	virtual void Update(const float& delta);

	/*
		函数功能:渲染
	*/
	void Render();

	/*
		函数功能:清空所有粒子
	*/
	void Clear();

	/*
		函数功能:设置粒子系统生成粒子的位置
	*/
	void SetPosition(
		const float& positionX,
		const float& positionY,
		const float& positionZ);

	/*
	函数功能:设置粒子系统生成粒子的位置
	*/
	void SetPosition(
		const float& positionX,
		const float& positionY);

	/*
		函数功能:设置粒子系统生成粒子的x坐标
	*/
	void SetPositionX(
		const float& positionX);
	/*
	函数功能:设置粒子系统生成粒子的y坐标
	*/
	void SetPositionY(
		const float& positionY);
	/*
		函数功能:设置粒子系统的z坐标
	*/
	void SetPositionZ(
		const float& positionZ);

	/*
		函数功能:返回粒子系统的x坐标
	*/
	float GetPositionX() const;
	/*
		函数功能:返回粒子系统的y坐标
	*/
	float GetPositionY() const;
	/*
	函数功能:返回粒子系统的z坐标
	*/
	float GetPositionZ() const;


	/*
	函数功能:设置粒子数量上限
	*/
	void SetMaxNums(const int& maxNums);

	/*
	函数功能:设置粒子的显示范围
	参数1~2:起始坐标
	参数3~4:宽和高
	*/
	void SetBoundBox(
		const int& positionX,
		const int& positionY,
		const int& width,
		const int& height);

	/*
	函数功能:设置持续时间
	参数1:发射器持续的时间(单位:秒)
	参数2:粒子系统的持续时间(单位:秒)
	*/
	void SetDuration(
		const float& launcherDuration,
		const float& duration);

	/*
	函数功能:设置粒子发射的间隔时间
	参数1:间隔时间(单位:秒)
	*/
	void SetLaunchInterval(const float& interval);

	/*
		返回发射器是否有效,true有效,false无效
	*/
	bool IsLaunch() const;

	/*
		返回粒子系统是否有效,true有效,false无效
	*/
	bool IsVisible() const;

	/*
		设置发射器的状态是否发射,true发射,false不发射
	*/
	void SetLaunch(bool enable);

	/*
		设置粒子系统是否有效,true有效,false无效
	*/
	void SetVisible(bool visible);

protected:
	ParticleSystem()
	: m_particle_list(0)
	, m_texturePath_list(0)
	, _positionX(0)
	, _positionY(0)
	, _positionZ(0)
	, _positionOffsetX(0)
	, _positionOffsetY(0)
	, _positionOffsetZ(0)
	, _alpha(255)
	, _r(255)
	, _g(255)
	, _b(255)
	, _alphaOffset(0)
	, _rOffset(0)
	, _gOffset(0)
	, _bOffset(0)
	, _velocityX(0)
	, _velocityY(0)
	, _velocityZ(0)
	, _velocityOffsetX(0)
	, _velocityOffsetY(0)
	, _velocityOffsetZ(0)
	, _accelerationX(0)
	, _accelerationY(0)
	, _accelerationZ(0)
	, _accelerationOffsetX(0)
	, _accelerationOffsetY(0)
	, _accelerationOffsetZ(0)
	, _particleDuration(0)
	, _particleDurationOffset(0)
	, _scale(1)
	, _scaleOffset(0)
	, _launchInterval(0)
	, _tempInterval(0)
	, _boundBoxPositionX(0)
	, _boundBoxPositionY(0)
	, _boundBoxWidth(0)
	, _boundBoxHeight(0)
	, _maxParticleNums(0)
	, _launchDuration(0)
	, _duration(0)
	, _launchEnable(true)
	, _visible(true)
	, _textureBlend(true)
	{}

private:
	ParticleSystem(ParticleSystem&);
	ParticleSystem& operator=(ParticleSystem&);

	void _AutoPush();

private:
	//vector<Particle*> m_particle_list;
	list<Particle*> m_particle_list;

	// 粒子的纹理路径
	vector<string> m_texturePath_list;

	// 粒子生成的位置
	float _positionX;
	float _positionY;
	float _positionZ;
	// 粒子生成位置的随机偏移值
	float _positionOffsetX;
	float _positionOffsetY;
	float _positionOffsetZ;
	// 粒子的初始属性
	// 颜色
	float _alpha;
	float _r, _g, _b;
	// 颜色随机偏移值
	float _alphaOffset;
	float _rOffset, _gOffset, _bOffset;
	// 速度
	float _velocityX;
	float _velocityY;
	float _velocityZ;
	// 速度随机偏移值
	float _velocityOffsetX;
	float _velocityOffsetY;
	float _velocityOffsetZ;
	// 加速度
	float _accelerationX;
	float _accelerationY;
	float _accelerationZ;
	// 加速度偏移值
	float _accelerationOffsetX;
	float _accelerationOffsetY;
	float _accelerationOffsetZ;
	// 粒子的存在时间
	float _particleDuration;
	// 粒子存在时间的随机偏移值
	float _particleDurationOffset;
	// 粒子的缩放比例
	float _scale;
	// 粒子的缩放比例偏移值
	float _scaleOffset;

	// 粒子的生成间隔
	float _launchInterval;
	// 临时的间隔,用于计算
	float _tempInterval;
	
	// 粒子显示的范围,超出这个范围就无效
	int _boundBoxPositionX;
	int _boundBoxPositionY;
	int _boundBoxWidth;
	int _boundBoxHeight;

	// 最大粒子数
	int _maxParticleNums;

	// 发射器的持续时间
	float _launchDuration;

	// 整个效果的持续时间
	float _duration;

	// 是否发射粒子,为false则停止发射,但仍然有效
	bool _launchEnable;

	// 是否有效
	bool _visible;

	// 粒子高亮
	bool _textureBlend;
};

NS_F2D_END

#endif