#ifndef _F2D_STRUCT_H_H_
#define _F2D_STRUCT_H_H_

#include "F2DMacros.h"
#include "F2DEnum.h"

NS_F2D_BEGIN

struct F2D_MSG_INFO
{
	ENUM_F2D_MESSAGE message;
	ENUM_F2D_KEYCODE keycode;
	int positionX;
	int positionY;
};

NS_F2D_END

#endif