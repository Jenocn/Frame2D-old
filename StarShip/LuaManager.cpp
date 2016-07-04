#include "LuaManager.h"
#include <cassert>

static LuaManager* pInstance = 0;

LuaManager* LuaManager::getInstance()
{
	if (0 == pInstance)
	{
		pInstance = new LuaManager();
	}

	return pInstance;
}

bool LuaManager::open(const char* path)
{
	// 获取一个lua实例
	m_lua = luaL_newstate();
	luaL_openlibs(m_lua);

	// 打开lua脚本文件,并获取返回值信息
	int ret = luaL_loadfile(m_lua, path);
	// 如果返回值不为0,那么打开出错,输出出错信息
	if (ret != 0)
	{
		return false;
	}

	// 调用lua函数,这里无参无返回值所以都为0
	lua_call(m_lua, 0, 0);

	return true;
}

void LuaManager::close()
{
	// 获取lua栈容量
	int size = lua_gettop(m_lua);
	// 清空lua栈
	lua_pop(m_lua, size);
	
	lua_close(m_lua);
}

// 读取int数据,传入变量名
double LuaManager::getNumber(const char* variableName)
{
	// 获得全局变量,传入需要获取的变量名,将该变量压入lua栈顶-1位置
	lua_getglobal(m_lua, variableName);
	// 判断lua栈顶元素是否是数值类型,如果是则获取
	assert(lua_isnumber(m_lua, -1) && "Data is not a number!");

	double num = lua_tonumber(m_lua, -1);

	// 获取lua栈容量
	int size = lua_gettop(m_lua);
	// 清空lua栈
	lua_pop(m_lua, size);

	return num;
}

// 读取字符串数据,传入变量名
string LuaManager::getString(const char* variableName)
{
	// 获得全局变量,传入需要获取的变量名,将该变量压入lua栈顶-1位置
	lua_getglobal(m_lua, variableName);
	// 判断lua栈顶元素是否是字符串类型,如果是则获取
	assert(lua_isstring(m_lua, -1) && "Data is not a string!");

	string str = lua_tostring(m_lua, -1);

	// 获取lua栈容量
	int size = lua_gettop(m_lua);
	// 清空lua栈
	lua_pop(m_lua, size);

	return str;
}

// 读取table中指定下标的数据
string LuaManager::getTableString(const char* tableName, int index)
{
	// 获得全局数组,并将数组压入栈顶
	lua_getglobal(m_lua, tableName);
	// 压入index元素
	lua_rawgeti(m_lua, -1, index);

	assert(lua_isstring(m_lua, -1) && "Data is not a string!");

	string str = lua_tostring(m_lua, -1);

	// 获取lua栈容量
	int size = lua_gettop(m_lua);
	// 清空lua栈
	lua_pop(m_lua, size);

	return str;
}

// 读取table中指定下标的数值数据,下标从1开始
double LuaManager::getTableNumber(const char* tableName, int index)
{
	// 获得全局数组,并将数组压入栈顶
	lua_getglobal(m_lua, tableName);
	// 压入index元素
	lua_rawgeti(m_lua, -1, index);

	assert(lua_isnumber(m_lua, -1) && "Data is not a number!");

	double num = lua_tonumber(m_lua, -1);

	// 获取lua栈容量
	int size = lua_gettop(m_lua);
	// 清空lua栈
	lua_pop(m_lua, size);

	return num;
}
