#pragma once

#include "Animation.h"

enum DIRECTION
{
	DIR_LEFT = 0,
	DIR_RIGHT = 1,
};

enum ACTION
{
	ACT_FLYAWAY = -2,
	ACT_HEARTED = -1,
	ACT_NONE = 0,
	ACT_WALK,
	ACT_ATTACK1,
	ACT_ATTACK2,
	ACT_ATTACK3,
};

class Player
{
public:
	// 캐릭터 애니메이션
	Animation ani;
	// 캐릭터 방향
	DIRECTION dir;
	// 캐릭터 현재 액션
	ACTION action;

	// 캐릭터 위치
	int x;
	int y;

	// 이긴 횟수
	int win;
	// 비긴 횟수
	int draw;

	// 아티펙트 구슬
	/*
	int art_head;
	int art_body;
	int art_leg;
	*/
	// 위 세개와 아래 한개의 위치는 대응된다.
	int art_beadPosition[3];
public:
	Player();

	void SetDirection(DIRECTION direction);
	bool SetAction(ACTION action);

	void Update();
	bool CheckCrash(Player &player);
};
