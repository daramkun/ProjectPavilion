#pragma once

#include <windows.h>
#include <DaramGraphics.h>
#include <DaramImage.h>
#include <DaramSound.h>
#include <DaramConsole.h>
#include <DaramDelay.h>
using namespace util;

#pragma comment(lib, "DaramLib.lib")

enum ObjType
{
	OT_IMAGE = 0,
	OT_SOUND = 1,
	OT_DAMAGEPOINT = 2,
	OT_ASSULTPOINT = 3,
	OT_ETC = 4,
};

struct AnimationUsingObject
{
	int index;
	int x, y;
	int width, height;
	float angle;
};

struct AnimationFrame
{
	AnimationUsingObject *objs;
	int objlength;
	int anchor_x, anchor_y;
};

struct AnimationFrameMode
{
	AnimationFrame *frms;
	int frmlength;
	int screen_width, screen_height;
	LPSTR name;
};

struct AnimationObject
{
	LPSTR name;
	LPSTR path;
	unsigned char *data;
	int datalength;
	unsigned char tc_a, tc_r, tc_g, tc_b;
	ObjType type;
	DaramImage image;
	DaramSound sound;
};

enum CrashPlayer
{
	CRP_NONE = 0,
	CRP_ME = 1,
	CRP_ENERMY = 2,
	CRP_BOTH = 3,
};

struct CrashInformation
{
	CrashPlayer assultHasMe;
	int MyDamagePointNumber;
	int MyAssultPointNumber;
	int EnDamagePointNumber;
	int EnAssultPointNumber;
};

class Animation
{
public:
	AnimationFrameMode *modes;
	int modelength;
	AnimationObject *objs;
	int objlength;

	int speed;

	bool isPlaying;
	int playingFrameMode;
	int playFrame;

	DaramDelay delay;

public:
	Animation(void);
	~Animation(void);

	bool Load(LPCSTR, DaramGraphics &g);

	void Play(LPCSTR fmName);
	void Play(int fmIndex);
	void Play();
	void Stop();
	void Pause();

	void AnimationDraw(DaramGraphics &g, int x, int y, int width = NULL, int height = NULL);
	void AnimationUpdate();

	int GetAnimationAnchorX();
	int GetAnimationAnchorY();

	int GetFrameModeIndex();
	int GetFrameIndex();

	int GetWidth() ;

	bool Crash(Animation&, CrashInformation*, int x, int y, int x2, int y2);

	void Dispose();
};