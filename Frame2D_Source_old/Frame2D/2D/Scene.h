#ifndef _SCENE_H_H_
#define _SCENE_H_H_

#include "Object.h"
#include "EventObj.h"

NS_F2D_BEGIN

class Element;
class ParticleSystem;
class UpdateFunc;

/*
场景,用于添加各种元素
说明:一个应用程序至少有一个场景
*/
class Scene : public Object, public EventObj
{
public:
	/*
	函数功能:创建一个场景并初始,返回这个场景
	*/
	static Scene* Create();

	/*
	函数功能:场景初始化
	返回值:初始成功返回真,否则返回假
	*/
	virtual bool Init() { return true; }

	virtual ~Scene() {}

	/*
	函数功能:添加一个元素到场景中
	参数:元素对象
	*/
	void Add(Element* element);

	void Add(Element* element, const int& order);

	/*
	函数功能:从场景中删除一个元素
	参数:要删除的元素对象
	*/
	void Remove(Element* element);

	/*
	函数功能:获取元素数组
	*/
	vector<Element*> GetElementList() const;

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
	函数功能:更新数据
	*/
	virtual void Update(const float& delta);

	/*
	函数功能:渲染所有元素
	*/
	virtual void Render();

	/*
	函数功能:释放空间,并delete自身
	*/
	void Release();

	/*
	函数功能:清空当前场景的所有元素和粒子系统
	*/
	void Clear();

	/*
	函数功能:清空临时列表
	*/
	void ClearTempList();

	/*
	函数功能:order值,排序用
	*/
	int GetOrder() const;

	/*
	函数功能:设置order排序值
	*/
	void SetOrder(const int& order);

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
	函数功能:判断是否有效,无效的会被删除
	*/
	bool IsVisible() const;

	void SetVisible(bool visible);

protected:
	Scene()
		: _sceneOrder(0)
		, _visible(true)
	{}

private:
	Scene(Scene&);
	Scene& operator=(Scene&);
private:
	vector<Element*> m_temp_list;
	vector<Element*> m_element_list;
	vector<ParticleSystem*> m_particleSys_list;
	vector <UpdateFunc*> m_updateFunc_list;
	int _sceneOrder;

	bool _visible;
};

NS_F2D_END

#endif