#ifndef _SPRITE_GROUP_H_H_
#define _SPRITE_GROUP_H_H_

#include "Element.h"

NS_F2D_BEGIN

class Sprite;

/*
	一组执行相同的动作的精灵
*/
class SpriteGroup : public Element
{
public:
	static SpriteGroup* Create();

	virtual ~SpriteGroup();

	/*
		函数功能:添加精灵
		说明:这里如果添加了精灵,那么请勿再次添加到场景中,
		否则会出现未知错误
	*/
	void Add(Sprite* sprite);

	/*
		函数功能:删除精灵
		参数1:要删除的精灵
	*/
	void Remove(Sprite* sprite);

	/*
		清空所有精灵
	*/
	void Clear();

	virtual void Update(const float& delta);

	virtual void Render();

	vector<Sprite*> GetSpriteList() const;

protected:
	SpriteGroup(){}

private:
	SpriteGroup(SpriteGroup&);
	SpriteGroup& operator=(SpriteGroup&);

private:
	vector<Sprite*> m_sprite_list;
};

NS_F2D_END

#endif