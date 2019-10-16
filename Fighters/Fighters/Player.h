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
	// ĳ���� �ִϸ��̼�
	Animation ani;
	// ĳ���� ����
	DIRECTION dir;
	// ĳ���� ���� �׼�
	ACTION action;

	// ĳ���� ��ġ
	int x;
	int y;

	// �̱� Ƚ��
	int win;
	// ��� Ƚ��
	int draw;

	// ��Ƽ��Ʈ ����
	/*
	int art_head;
	int art_body;
	int art_leg;
	*/
	// �� ������ �Ʒ� �Ѱ��� ��ġ�� �����ȴ�.
	int art_beadPosition[3];
public:
	Player();

	void SetDirection(DIRECTION direction);
	bool SetAction(ACTION action);

	void Update();
	bool CheckCrash(Player &player);
};
