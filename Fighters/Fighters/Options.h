#pragma once

#include <DaramLibrary.h>

enum HEALTHYPOINT
{
	HP_50 = 0,
	HP_60 = 1,
	HP_70 = 2,
	HP_80 = 3,
	HP_90 = 4,
	HP_100 = 5,
};

enum TIMER
{
	TMR_30 = 0,
	TMR_45,
	TMR_60,
};

enum VOLUME
{
	VOL_0 = 0,
	VOL_1,
	VOL_2,
	VOL_3,
	VOL_4,
	VOL_5,
};

enum ROUND
{
	RND_1 = 0,
	RND_2,
	RND_3,
	RND_4,
	RND_5,
};

struct CommandKey
{
	InputKeys up;
	InputKeys down;
	InputKeys left;
	InputKeys right;

	InputKeys a;
	InputKeys s;
	InputKeys d;
};

extern HEALTHYPOINT hp;
extern TIMER timer;
extern VOLUME volume;
extern ROUND round;
extern CommandKey p1Cmd;
extern CommandKey p2Cmd;