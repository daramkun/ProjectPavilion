#pragma once

/*-------------------------------------------------------------------
 * AI 관련 클래스
 * 설명 : AI 루아 스크립트 파일을 실행한다.
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