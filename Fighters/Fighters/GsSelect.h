#pragma once

#include "Define.h"

#include <DaramImage.h>
#include <DaramFrame.h>
#include <DaramDelay.h>
#include <DaramSound.h>
using namespace util;

#include "ImageFont.h"

/////////////////////////////////////////////////
// Class  Name : GsSelect
// Description : 캐릭터 선택 화면
// W o r k e r : 진재연, 전영준
//  Work Date  : 2009/01/21
/////////////////////////////////////////////////
class GsSelect : public DaramFrame
{
public:
	bool fadeIn;
	bool fadeOut;
	int alpha;

	GameState nextState;
	PlayMode playMode;

	DaramSound bgSound;

	DaramImage bg;
	DaramImage selImage[2];

	DaramImage selSmImage[6];
	DaramImage selIllust[6];

	ImageFont charName;

	POINT loc[6];

	bool selKeyCheck1[4] ;				// 키가 눌렸는가 0-Up 1-Down 2-Right 3-Left
	DaramDelay selDelay1 ;
	
	bool selKeyCheck2[4] ;				// 키가 눌렸는가 0-Up 1-Down 2-Right 3-Left
	DaramDelay selDelay2 ;

	int selLoc1;
	int selLoc2;

	bool selOk1;
	bool selOk2;

	LPCSTR charAniFile[6];
	LPCSTR charNames[6];

	LPSTR serverIp;
	bool isServer;

public:
	GsSelect() : DaramFrame(GS_SELECT) { }

	void Initial();
	void Update(double);
	void Draw();
	void KeyCheck();
	void UpKeyPress1();
	void DownKeyPress1();
	void RightKeyPress1();
	void LeftKeyPress1();
	void UpKeyPress2();
	void DownKeyPress2();
	void RightKeyPress2();
	void LeftKeyPress2();
	void Dispose();

};
