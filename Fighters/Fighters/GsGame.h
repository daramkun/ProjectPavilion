#pragma once

#include "Define.h"

#include <DaramFrame.h>

#include "Map.h"
#include "Player.h"
#include "Ai.h"

/////////////////////////////////////////////////
// Class  Name : GsGame
// Description : 실질적인 게임 부분 화면
// W o r k e r : 진재연
//  Work Date  : 2009/01/21
/////////////////////////////////////////////////
class GsGame : public DaramFrame
{
public:
	Map map;

	PlayMode playMode;

	Player p1;
	Player p2;

	Ai p2Ai;
	char *aiFile;

	DaramImage artipectBar[2];
	DaramImage artipects[3];
	DaramImage beadBar[2];

	DaramImage mapState[8];
public:
	GsGame() : DaramFrame(GS_GAME) { }

	void Initial();
	void Update(double);
	void Draw();
	void Dispose();

	void Player1State(DIRECTION dir, ACTION act);
	void Player2State(DIRECTION dir, ACTION act);

	void CharacterMoveCheck() ;
};
