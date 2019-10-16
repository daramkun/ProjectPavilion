#pragma once

/*-------------------------------------------------------------------
 * AI ���� Ŭ����
 * ���� : AI ��� ��ũ��Ʈ ������ �����Ѵ�.
 *-----------------------------------------------------------------*/

#include "Lua/lua.hpp"
#include <DaramConsole.h>
#include <stdlib.h>
#include "Define.h"

#pragma comment(lib, "Lua/Lua5.1.lib")

class Ai
{
private:
	lua_State *pLuaState;

public:
	void Initialize();
	void RunAI(const char *file);
	void Finalize();
};