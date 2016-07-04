#ifndef _ELEMENT_H_H_
#define _ELEMENT_H_H_

#include "Object.h"
#include "EventObj.h"

NS_F2D_BEGIN

class UpdateFunc;
class Action;
class ParticleSystem;
class Scene;

// 元素,组成程序的必要成分
class Element : public Object, public EventObj
{
public:
	/*
	说明:继承自Element的子类将不再提供析Release函数,而是通过
	在析构函数中释放内存,因此继承自该来的子类的释放内存操作应该
	放到析构函数中才会正确,请勿手动delete子类
	*/
	virtual ~Element();

	/*
		函数功能:delete自身
		说明:在此delete自身,因此会调用到析构函数,而析构函数是virtual修饰
		的,所以会调用子类的析构函数
	*/
	void Release();

	/*
		更新数据
	*/
	virtual void Update(const float& delta);

	/*
		渲染
	*/
	virtual void Render();

	void ParticleRender();

	/*
		函数功能:获取排序值
		说明:这里的排序值是元素的z坐标到摄像机的距离
	*/
	int GetOrder() const;

	void SetOrder(const int& order);

	/*
		获取x坐标
	*/
	float GetPositionX() const;

	/*
		获取y坐标
	*/
	float GetPositionY() const;

	/*
		获取z坐标	
	*/
	float GetPositionZ() const;

	/*
		函数功能:设置空间坐标
		参数1~3:空间坐标值
	*/
	void SetPosition(
		const float& positionX,
		const float& positionY,
		const float& positionZ);

	/*
		函数功能:设置平面坐标
		参数1~2:平面坐标xy
	*/
	void SetPosition(
		const float& positionX,
		const float& positionY);

	/*
		设置x坐标
	*/
	void SetPositionX(const float& positionX);

	/*
		设置y坐标
	*/
	void SetPositionY(const float& positionY);

	/*
		设置z坐标
	*/
	void SetPositionZ(const float& positionZ);

	/*
		获得x轴旋转角度
	*/
	float GetAngleX() const;

	/*
		获得y轴旋转角度
	*/
	float GetAngleY() const;

	/*
		获得z轴旋转角度
	*/
	float GetAngleZ() const;

	/*
		函数功能:设置旋转角度
		参数1~3:分别对应(x,y,z)的旋转角度
	*/
	void SetAngle(
		const float& angleX,
		const float& angleY,
		const float& angleZ);

	/*
		设置x轴旋转角度
	*/
	void SetAngleX(const float& angleX);

	/*
		设置y轴旋转角度
	*/
	void SetAngleY(const float& angleY);

	/*
		设置z轴旋转角度
	*/
	void SetAngleZ(const float& angleZ);

	/*
		获得x轴方向上的锚点
	*/
	float GetAnchorX() const;

	/*
		获得y轴方向上的锚点
	*/
	float GetAnchorY() const;

	/*
		设置锚点
		参数1~2:分别对应(x,y)轴上的锚点
	*/
	void SetAnchor(
		const float& anchorX,
		const float& anchorY);

	/*
		设置x轴上的锚点
	*/
	void SetAnchorX(const float& anchorX);

	/*
		设置y轴上的锚点
	*/
	void SetAnchorY(const float& anchorY);

	/*
		获得x轴方向上的缩放比例
	*/
	float GetScaleX() const;

	/*
		获得y轴方向上的缩放比例
	*/
	float GetScaleY() const;

	/*
		设置整体缩放比例
	*/
	void SetScale(const float& scale);

	/*
		分别设置x,y轴方向上的缩放比例
	*/
	void SetScale(
		const float& scaleX,
		const float& scaleY);

	/*
		设置x轴方向上的缩放比例
	*/
	void SetScaleX(const float& scaleX);

	/*
		设置y轴方向上的缩放比例
	*/
	void SetScaleY(const float& scaleY);

	/*
		获得宽度
	*/
	int GetWidth() const;

	/*
		获得高度
	*/
	int GetHeight() const;

	/*
		返回是否可见的状态
	*/
	bool IsVisible();

	/*
		设置是否可见的状态
	*/
	void SetVisible(bool bVisible);

	/*
	函数功能:添加每帧更新的函数
	*/
	void AddUpdateFunc(UpdateFunc* func);

	/*
	函数功能:删除某个自添加更新的函数
	*/
	void RemoveUpdateFunc(UpdateFunc* func);

	/*
	函数功能:清空所有自添加的更新函数
	*/
	void ClearUpdateFunc();

	/*
	函数功能:添加并执行一个动作
	参数:动作
	*/
	void RunAction(Action* action);

	/*
	函数功能:删除一个动作
	*/
	void RemoveAction(Action* action);

	/*
	函数功能:删除所有动作
	*/
	void ClearAction();

	/*
	函数功能:判断当前是否存在action行为
	*/
	bool IsActionPlaying() const;

	/*
	函数功能:添加一个粒子系统
	参数:粒子系统对象
	*/
	void Add(ParticleSystem* system);

	/*
	函数功能:从场景中删除一个粒子系统
	参数:要删除的系统对象
	*/
	void Remove(ParticleSystem* system);

	/*
	函数功能:清空当前场景的所有粒子系统
	*/
	void Clear();

	/*
	绑定场景
	*/
	void BindScene(Scene* scene);

	/*
	获得当前所在场景
	*/
	Scene* GetScene() const;

protected:
	Element()
	: _scene(0)
	, _positionX(0)
	, _positionY(0)
	, _positionZ(0)
	, _angleX(0)
	, _angleY(0)
	, _angleZ(0)
	, _anchorX(0.5f)
	, _anchorY(0.5f)
	, _scaleX(1.0f)
	, _scaleY(1.0f)
	, _width(0)
	, _height(0)
	, _order(0)
	, _visible(true)
	{}

	void SetWidth(const int& width);
	void SetHeight(const int& height);

private:
	Element(Element&);
	Element& operator=(Element&);

private:
	vector<UpdateFunc*> m_updateFunc_list;
	vector<Action*> m_action_list;
	vector<ParticleSystem*> m_particleSys_list;
	Scene* _scene;
	float _positionX;
	float _positionY;
	float _positionZ;
	float _angleX;
	float _angleY;
	float _angleZ;
	float _anchorX;
	float _anchorY;
	float _scaleX;
	float _scaleY;
	int _width;
	int _height;
	int _order;
	bool _visible;
};

NS_F2D_END

#endif