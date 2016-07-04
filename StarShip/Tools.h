#ifndef _TOOLS_H_H_
#define _TOOLS_H_H_

#include <Frame2D.h>

USING_NS_F2D

class Tools
{
public:
	// 目标是圆形
	static bool CheckHit_Circle(Element* bullet, Element* plane);
	// 目标是矩形
	static bool CheckHit_Rectangle(Element* bullet, Element* plane);	
	// 目标是点
	static bool CheckHit_Point(Element* bullet, Element* plane);
	// 出了范围
	static bool CheckHit_UnInclude(Element* e,
		const int& left, const int& top,
		const int& right, const int& bottom);
};

#endif