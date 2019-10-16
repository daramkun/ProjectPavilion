#include "Player.h"
#include <DaramConsole.h>
using namespace util;
#include "Options.h"
#include "Extern.h"

Player::Player()
{
	for(int i = 0; i < 3; i++)
	{
		art_beadPosition[i] = 100;
	}
}

void Player::SetDirection(DIRECTION direction)
{
	dir = direction;
}

bool Player::SetAction(ACTION action)
{
	if(this->action != ACT_NONE)
	{
		switch(action)
		{
		case ACT_FLYAWAY:
		case ACT_HEARTED:
			this->action = action;
			break;
		default:
			return false;
		}
	}
		this->action = action;

		if(dir == DIR_RIGHT)
		{
			switch(action)
			{
			case ACT_FLYAWAY:
				break;
			case ACT_HEARTED:
				break;
			case ACT_NONE:
				ani.Play("breath_right");
				break;
			case ACT_WALK:
				ani.Play( "walk_right" ) ;
				break;
			case ACT_ATTACK1:
				ani.Play("attack1_right");
				break;
			case ACT_ATTACK2:
				ani.Play("attack2_right");
				break;
			case ACT_ATTACK3:
				ani.Play("attack3_right");
				break;
			}
		}
		else
		{
			switch(action)
			{
			case ACT_FLYAWAY:
				break;
			case ACT_HEARTED:
				break;
			case ACT_NONE:
				ani.Play("breath_left");
				break;
			case ACT_WALK:
				ani.Play( "walk_left" ) ;
				break;
			case ACT_ATTACK1:
				ani.Play("attack1_left");
				break;
			case ACT_ATTACK2:
				ani.Play("attack2_left");
				break;
			case ACT_ATTACK3:
				ani.Play("attack3_left");
				break;
			}
		}

	return false;
}

bool Player::CheckCrash(Player &player)
{
	CrashInformation ci;
	ZeroMemory(&ci, sizeof(ci));
	bool returnValue = ani.Crash(player.ani, &ci, x, y, player.x, player.y); 

	switch(ci.assultHasMe)
	{
	case CRP_ME:
		player.art_beadPosition[ci.EnDamagePointNumber] -= 1;
		break;
	case CRP_ENERMY:
		art_beadPosition[ci.MyDamagePointNumber] -= 1;
		break;
	case CRP_BOTH:
		player.art_beadPosition[ci.EnDamagePointNumber] -= 1;
		art_beadPosition[ci.MyDamagePointNumber] -= 1;
		break;
	}

	for(int i = 0; i < 3; i++)
		if(art_beadPosition[i] < 0)
			art_beadPosition[i] = 0;
	
	for(int i = 0; i < 3; i++)
		if(player.art_beadPosition[i] < 0)
			player.art_beadPosition[i] = 0;

	switch(ci.assultHasMe)
	{
	case CRP_ME:
	case CRP_ENERMY:
	case CRP_BOTH:
		DaramConsole::PrintLine("player.art_beadPosition[%d] : %d", ci.EnDamagePointNumber, player.art_beadPosition[ci.EnDamagePointNumber]);
		DaramConsole::PrintLine("art_beadPosition[%d] : %d", ci.MyDamagePointNumber, art_beadPosition[ci.MyDamagePointNumber]);
		DaramConsole::PrintLine("ci.assutHasMe : %d", ci.assultHasMe);
		break;
	}
	return returnValue;
}

void Player::Update()
{
	if((ani.playFrame == ani.modes[ani.playingFrameMode].frmlength - 1 
		|| ani.playingFrameMode == -1) && action != ACT_NONE )
	{
		action = ACT_NONE;
		if(dir == DIR_RIGHT)
			ani.Play("breath_right");
		else
			ani.Play("breath_left");
	}
}