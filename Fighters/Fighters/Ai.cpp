#include "Ai.h"
#include <DaramConsole.h>
#include "Extern.h"

extern "C" int _SetPlayer1State(lua_State *pLuaState)
{
	int dir = luaL_optint(pLuaState, 1, 0);
	int act = luaL_optint(pLuaState, 2, 0);

	g_Game.Player1State((DIRECTION)dir, (ACTION)act);

	return 0;
}

extern "C" int _SetPlayer2State(lua_State *pLuaState)
{
	int dir = luaL_optint(pLuaState, 1, 0);
	int act = luaL_optint(pLuaState, 2, 0);

	g_Game.Player2State((DIRECTION)dir, (ACTION)act);

	return 0;
}

/////////////////////////////////////////////////

extern "C" int _Player1GetX(lua_State *pLuaState)
{
	lua_pushnumber(pLuaState, g_Game.p1.x);
	return 1;
}

extern "C" int _Player1GetY(lua_State *pLuaState)
{
	lua_pushnumber(pLuaState, g_Game.p1.y);
	return 1;
}

extern "C" int _Player1GetWidth( lua_State *pLuaState )
{
	lua_pushnumber( pLuaState, g_Game.p1.ani.GetWidth() ) ;
	return 1 ;
}

/////////////////////////////////////////////////

extern "C" int _Player2GetX(lua_State *pLuaState)
{
	lua_pushnumber(pLuaState, g_Game.p2.x);
	return 1;
}

extern "C" int _Player2GetY(lua_State *pLuaState)
{
	lua_pushnumber(pLuaState, g_Game.p2.x);
	return 1;
}

extern "C" int _Player2GetWidth( lua_State *pLuaState )
{
	lua_pushnumber( pLuaState, g_Game.p2.ani.GetWidth() ) ;
	return 1 ;
}

/////////////////////////////////////////////////

extern "C" int _Player1SetX(lua_State *pLuaState)
{
	int x = luaL_optint(pLuaState, 1, 0);
	g_Game.p1.x = x;
	return 0;
}

extern "C" int _Player1SetY(lua_State *pLuaState)
{
	int y = luaL_optint(pLuaState, 1, 0);
	g_Game.p1.y = y;
	return 0;
}

/////////////////////////////////////////////////

extern "C" int _Player2SetX(lua_State *pLuaState)
{
	int x = luaL_optint(pLuaState, 1, 0);
	g_Game.p2.x = x;
	return 0;
}

extern "C" int _Player2SetY(lua_State *pLuaState)
{
	int y = luaL_optint(pLuaState, 1, 0);
	g_Game.p1.y = y;
	return 0;
}

/////////////////////////////////////////////////

extern "C" int _Player1GetAction(lua_State *pLuaState)
{
	lua_pushnumber(pLuaState, g_Game.p1.action);
	return 1;
}

extern "C" int _Player2GetAction(lua_State *pLuaState)
{
	lua_pushnumber(pLuaState, g_Game.p2.action);
	return 1;
}

extern "C" int _Player1GetDirection(lua_State *pLuaState)
{
	lua_pushnumber(pLuaState, g_Game.p1.dir);
	return 1;
}

extern "C" int _Player2GetDirection(lua_State *pLuaState)
{
	lua_pushnumber(pLuaState, g_Game.p2.dir);
	return 1;
}

extern "C" int _Player1GetArtipect(lua_State *pLuaState)
{
	int artindex = luaL_optint(pLuaState, 1, 0);
	lua_pushnumber(pLuaState, g_Game.p1.art_beadPosition[artindex]);
	return 1;
}

extern "C" int _Player2GetArtipect(lua_State *pLuaState)
{
	int artindex = luaL_optint(pLuaState, 1, 0);
	lua_pushnumber(pLuaState, g_Game.p2.art_beadPosition[artindex]);
	return 1;
}

extern "C" int _Print(lua_State *pLuaState)
{
	const char* pString = luaL_optstring(pLuaState, 1, 0);

	util::DaramConsole::Print(pString);
	return 0;
}

extern "C" int _PrintLine(lua_State *pLuaState)
{
	const char* pString = luaL_optstring(pLuaState, 1, 0);

	util::DaramConsole::PrintLine(pString);
	return 0;
}

extern "C" int _Random(lua_State *pLuaState)
{
	int min, max;
	min = luaL_optint(pLuaState, 1, 0);
	max = luaL_optint(pLuaState, 2,  0);

	srand( GetTickCount() ) ;
	
	lua_pushnumber(pLuaState, (rand() % (max + 1) + min) );

	return 1;
}

extern "C" int _TickCount(lua_State *pLuaState)
{
	lua_pushnumber(pLuaState, GetTickCount());
	return 1;
}

static luaL_reg GlueFunctions[] = {
							{"P1_SetState", _SetPlayer1State},
							{"P2_SetState", _SetPlayer2State},
							
							{"P1_GetX", _Player1GetX},
							{"P1_GetY", _Player1GetY},
							{"P1_GetWidth", _Player1GetWidth},
							
							{"P2_GetX", _Player2GetX},
							{"P2_GetY", _Player2GetY},
							{"P2_GetWidth", _Player2GetWidth},

							{"P1_SetX", _Player1SetX},
							{"P1_SetY", _Player1SetY},
							
							{"P2_SetX", _Player2SetX},
							{"P2_SetY", _Player2SetY},
							
							{"P1_GetArtipect", _Player1GetArtipect},
							{"P2_GetArtipect", _Player2GetArtipect},
							
							{"P1_GetDir", _Player1GetDirection},
							{"P2_GetDir", _Player2GetDirection},
							
							{"P1_GetAction", _Player1GetAction},
							{"P2_GetAction", _Player2GetAction},
							
							{"Print", _Print},
							{"PrintLine", _PrintLine},
							{"Random", _Random},
							{"TickCount", _TickCount},
							
							{NULL,   NULL}
						   };

void Ai::Initialize()
{
	pLuaState = lua_open();
	luaopen_base(pLuaState);
	luaopen_math(pLuaState);

	for(int i = 0; GlueFunctions[i].name; i++)
	{
		lua_register(pLuaState, GlueFunctions[i].name, GlueFunctions[i].func);
	}

	srand(GetTickCount());
}

void Ai::RunAI(const char *file)
{
	luaL_dofile(pLuaState, file);
}

void Ai::Finalize()
{
	lua_close(pLuaState);
}