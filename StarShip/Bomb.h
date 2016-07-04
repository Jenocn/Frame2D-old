#ifndef _BOMB_H_H_
#define _BOMB_H_H_

class Plane;

//===================
// 炸弹类
//===================
class Bomb
{
public:
	virtual ~Bomb();

	void Release();

	virtual void Use();

protected:
	Bomb()
	: _belongPlane(0)
	{}

private:
	Bomb(Bomb&);
	Bomb& operator=(Bomb&);

private:
	const Plane* _belongPlane;
};

#endif