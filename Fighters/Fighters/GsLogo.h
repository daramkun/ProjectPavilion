#pragma once

#include "Define.h"

#include <DaramImage.h>
#include <DaramFrame.h>
#include <DaramDelay.h>
#include <DaramSound.h>

#include "Animation.h"

/////////////////////////////////////////////////
// Class  Name : GsLogo
// Description : 로고 화면 및 데이터 로드 화면
// W o r k e r : 전영준, 진재연
//  Work Date  : 2009/01/07
/////////////////////////////////////////////////
class GsLogo : public DaramFrame
{
private:
	// 페이드인 모드 체크
	bool fadeIn;
	// 페이드아웃 모드 체크
	bool fadeOut;
	// 알파값(BYTE 자료)
	unsigned char alpha;
	// 딜레이 검사 클래스
	util::DaramDelay delay;

	// 로고 이미지
	DaramImage logo;
	// 등급 이미지
	DaramImage levelIcon;
	// 폭력성 이미지
	DaramImage forceIcon;
	// 별사탕 로고 애니메이션
	Animation logoAni;

	// 로고 사운드
	DaramSound logoSound;

public:
	GsLogo() : DaramFrame(GS_LOGO) { }

	void Initial();
	void Update(double);
	void Draw();
	void Dispose();

};
