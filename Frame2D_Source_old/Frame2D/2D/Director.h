#ifndef _DIRECTOR_H_H_
#define _DIRECTOR_H_H_

#include "Object.h"

NS_F2D_BEGIN

class Scene;
class EventDispatcher;

/*
	导演类
*/
class Director : public Object
{
public:
	static Director* getInstance();

	/*
		更新,场景的update和渲染
	*/
	void Update(const float& delta);

	/*
		释放内存并delete自身
	*/
	void Release();

	/*
		函数功能:添加一个场景
		参数1:场景对象
	*/
	void PushScene(Scene* scene);

	/*
		函数功能:删除当前场景并添加新的场景
		参数:新的场景
	*/
	void ReplaceScene(Scene* scene);

	/*
		函数功能:删除当前场景
	*/
	void PopScene();

	/*
		函数功能:清空所有场景
	*/
	void ClearScene();

	// 返回暂停的状态
	bool IsPause();

	/*
		设置是否暂停
		参数1:是否暂停,true暂停,false不暂停
	*/
	void SetPause(bool bPause);

	/*
	函数功能:获得可视区域的大小
	*/
	RECT GetViewRect() const;

	/*
	函数功能:获得事件分发器
	*/
	EventDispatcher* getEventDispatcher();

private:
	Director()
	{}
	Director(Director&);
	Director& operator=(Director&);

private:
	vector<Scene*> m_scene_list;
};

NS_F2D_END

#endif