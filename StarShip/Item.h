#ifndef _ITEM_H_H_
#define _ITEM_H_H_

#include <Frame2D.h>

class Item : public Frame2D::Sprite
{
public:
	static Item* Create(const int& itemID);

	virtual ~Item();

	bool InitData(const int& itemID);

	virtual void Update(const float& delta);

	virtual void Render();

protected:
	Item()
	: _changeTime(0)
	, _bChange(false)
	{}

private:
	Item(Item&);
	Item& operator=(Item&);

private:
	// temp
	float _changeTime;
	bool _bChange;
};

#endif