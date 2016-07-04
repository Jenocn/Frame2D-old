#ifndef _F2D_ENUM_H_H_
#define _F2D_ENUM_H_H_

#include "F2DMacros.h"

NS_F2D_BEGIN

enum ENUM_F2D
{
	F2D_NORMAL = -1,
	F2D_NULL = 0,
};

enum ENUM_F2D_DIRECTION
{
	F2D_DIRECTION_CENTER = 0,
	F2D_DIRECTION_UP,
	F2D_DIRECTION_DOWN,
	F2D_DIRECTION_LEFT,
	F2D_DIRECTION_RIGHT,
	F2D_DIRECTION_UPLEFT,
	F2D_DIRECTION_UPRIGHT,
	F2D_DIRECTION_DOWNLEFT,
	F2D_DIRECTION_DOWNRIGHT,
};

// 系统消息
enum ENUM_F2D_MESSAGE
{
	F2D_MESSAGE_NULL = 0,
	F2D_MESSAGE_KEYDOWN,
	F2D_MESSAGE_KEYUP,
	F2D_MESSAGE_LBUTTONDOWN,
	F2D_MESSAGE_LBUTTONUP,
	F2D_MESSAGE_RBUTTONDOWN,
	F2D_MESSAGE_RBUTTONUP,
	F2D_MESSAGE_ROLL,
};

// 按键枚举
enum ENUM_F2D_KEYCODE
{
	F2D_KEYCODE_NULL = 0,
	// 键盘A~Z
	F2D_KEYCODE_A,
	F2D_KEYCODE_B,
	F2D_KEYCODE_C,
	F2D_KEYCODE_D,
	F2D_KEYCODE_E,
	F2D_KEYCODE_F,
	F2D_KEYCODE_G,
	F2D_KEYCODE_H,
	F2D_KEYCODE_I,
	F2D_KEYCODE_J,
	F2D_KEYCODE_K,
	F2D_KEYCODE_L,
	F2D_KEYCODE_M,
	F2D_KEYCODE_N,
	F2D_KEYCODE_O,
	F2D_KEYCODE_P,
	F2D_KEYCODE_Q,
	F2D_KEYCODE_R,
	F2D_KEYCODE_S,
	F2D_KEYCODE_T,
	F2D_KEYCODE_U,
	F2D_KEYCODE_V,
	F2D_KEYCODE_W,
	F2D_KEYCODE_X,
	F2D_KEYCODE_Y,
	F2D_KEYCODE_Z,
	// 键盘区0~9
	F2D_KEYCODE_0,
	F2D_KEYCODE_1,
	F2D_KEYCODE_2,
	F2D_KEYCODE_3,
	F2D_KEYCODE_4,
	F2D_KEYCODE_5,
	F2D_KEYCODE_6,
	F2D_KEYCODE_7,
	F2D_KEYCODE_8,
	F2D_KEYCODE_9,
	// 
	F2D_KEYCODE_MINUS, // (-)键盘区减号
	F2D_KEYCODE_EQUAL, // (=)键盘区等号
	F2D_KEYCODE_BACKSLANT, // (\)反斜杠
	F2D_KEYCODE_BACKSPACE, // 退格
	F2D_KEYCODE_WAVELINE, // (~)键盘区波浪线
	F2D_KEYCODE_BRACE_L, // ({),([)左括号
	F2D_KEYCODE_BRACE_R, // (}),(])右括号
	F2D_KEYCODE_SEMICOLON, // (;)分号
	F2D_KEYCODE_QUOTING, // ('),(")引号
	F2D_KEYCODE_COMMA, // (,)逗号
	F2D_KEYCODE_POINT, // (.)点
	F2D_KEYCODE_SPRIT, // (/)斜杠
	// 
	F2D_KEYCODE_TAB, // TAB
	F2D_KEYCODE_CAPSLOCK, // 大小写锁定
	F2D_KEYCODE_SHIFTL, // 左shift
	F2D_KEYCODE_SHIFTR, // 右shift
	F2D_KEYCODE_CTRLL, // 左ctrl
	F2D_KEYCODE_CTRLR, // 右ctrl
	F2D_KEYCODE_ALTL, // 左alt
	F2D_KEYCODE_ALTR, // 右alt
	F2D_KEYCODE_SPACE, // 空格键
	F2D_KEYCODE_ENTER,
	F2D_KEYCODE_ESC, // ESC
	//
	F2D_KEYCODE_F1,
	F2D_KEYCODE_F2,
	F2D_KEYCODE_F3,
	F2D_KEYCODE_F4,
	F2D_KEYCODE_F5,
	F2D_KEYCODE_F6,
	F2D_KEYCODE_F7,
	F2D_KEYCODE_F8,
	F2D_KEYCODE_F9,
	F2D_KEYCODE_F10,
	F2D_KEYCODE_F11,
	F2D_KEYCODE_F12,
	//
	F2D_KEYCODE_INSERT, // 插入键
	F2D_KEYCODE_DELETE, // 删除键
	F2D_KEYCODE_HOME, // (HOME)页面按键
	F2D_KEYCODE_END, // (END)页面按键
	F2D_KEYCODE_PAGEUP, // (PAGE UP)页面按键
	F2D_KEYCODE_PAGEDOWN, // (PAGE DOWN)页面按键
	//
	F2D_KEYCODE_UP, // 方向键上
	F2D_KEYCODE_DOWN, // 下
	F2D_KEYCODE_LEFT, // 左
	F2D_KEYCODE_RIGHT, // 右
	// 小键盘区域
	F2D_KEYCODE_NUM0,
	F2D_KEYCODE_NUM1,
	F2D_KEYCODE_NUM2,
	F2D_KEYCODE_NUM3,
	F2D_KEYCODE_NUM4,
	F2D_KEYCODE_NUM5,
	F2D_KEYCODE_NUM6,
	F2D_KEYCODE_NUM7,
	F2D_KEYCODE_NUM8,
	F2D_KEYCODE_NUM9,
	F2D_KEYCODE_NUM_POINT,
	F2D_KEYCODE_NUM_ADD,
	F2D_KEYCODE_NUM_MINUS,
	F2D_KEYCODE_NUM_MULTIPLY,
	F2D_KEYCODE_NUM_DIVIDE,
};

NS_F2D_END

#endif