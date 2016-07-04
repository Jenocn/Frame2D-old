#ifndef _C_IO_MANAGER_H_H_
#define _C_IO_MANAGER_H_H_

#include "Lua\include\lua.hpp"
#include "Lua\include\lauxlib.h"

#pragma comment(lib, "lua.lib")

#include <string>

using namespace std;

// IO管理器
class LuaManager
{
public:
	static LuaManager* getInstance();

public:
	// 打开文件
	bool open(const char* path);
	// 关闭文件
	void close();
	// 读取数值数据,传入变量名
	double getNumber(const char* variableName);
	// 读取字符串数据,传入变量名
	string getString(const char* variableName);
	// 读取table中指定下标的字符串数据,下标从1开始
	string getTableString(const char* tableName, int index);
	// 读取table中指定下标的数值数据,下标从1开始
	double getTableNumber(const char* tableName, int index);

protected:
	LuaManager() {}
	LuaManager(LuaManager&) {}
	LuaManager& operator=(LuaManager&) {}

protected:
	// lua对象
	lua_State* m_lua;
};

#endif