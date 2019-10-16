#pragma once

#include <DaramFrame.h>
#include <DaramImage.h>
#include <DaramSound.h>
#include "Define.h"
#include "ImageFont.h"

#include <DaramDelay.h>
using namespace util;

#include "Animation.h"

/////////////////////////////////////////////////
// Class  Name : GsMenu
// Description : 게임 매인 메뉴 화면
// W o r k e r : 전영준, 진재연
//  Work Date  : 2009/01/13
/////////////////////////////////////////////////
class GsMenu : public DaramFrame
{
private:
	DaramImage bead;						// 배경 구슬 이미지
	DaramImage menuSelectImage[4] ;			// 메인 메뉴 선택 이미지(글씨)
	DaramImage subMenuSelectImage[3] ;		// 서브 메뉴 선택 이미지(글씨)
	DaramImage optionImage[3] ;			// 옵션 이미지 ( 칠판은 0 숫자는 1부터 10은 0 )
											// 11은 percent 12는 cursor 
	DaramImage createrImage[3];

	ImageFont numberFont;

	int menuAlpha ;							// 메뉴 선택 이미지 알파값
	int prevMenuState, nextMenuState ;		// 이전/다음 메뉴 선택 이미지

	MenuState menuState ;					// 매인 메뉴 상태
	bool menuAlphaCheck ;					// 매인 메뉴 선택 이미지 알파값 증감 상태 체크
	bool menuSelectCheck ;					// 매인 메뉴를 활성화 했는지 체크

	SubMenuState subMenuState ;				// 서브 메뉴 선택
	bool subMenuAlphaCheck ;				// 서브 메뉴 선택 이미지 알파값 증감 상태 체크

	int createrCount ;						// Creater 어떤 정보를 출력하는가 0 기획 1프밍 2그래픽
	bool createrDirectionCheck ;			// 어느쪽으로 향하고 있는가? false - 0->2
	bool createrFadein ;					// fadein상태인가
	DaramDelay createrDelay ;				// 

	int opState ;							// 옵션 상태
	int opLinePosY ;						// 옵션 라인 Y좌표 
	bool opSelectCheck ;					// 옵션 선택 활성화 했는지 체크
	int opSelectState ;						// 옵션 선택 세부사항 상태
	int opMenu[5] ;							// 옵션 메뉴 값 0-Hp , 1-Timer 2-Volume 3-Round 4-Key
	int opMenuSize[5] ;						// 
	int opPlusCoor[5] ;						// 
	int opComCoor[5] ;						//
	bool nowKeyChange1p ;					// 현재 1피 키를 바꾸는가?? 1피면 T 2피면 F
	char save1PKey[7][2] ;					// 1피 키 상태 저장
	char save2PKey[7][2] ;					// 2피 키 상태 저장
	bool keyChangeCheck ;					// 키를 바꾸는 상태로 들어갔는가??

	bool fadeIn;						// 페이드인을 수행
	bool fadeOut;						// 페이드아웃을 수행
	unsigned char alpha;				// 페이드 알파

	DaramSound menuSelect;				// 화살표를 이용하여 어떤 메뉴를 사용할 지 고를때 재생
	DaramSound menuChoose;				// 스페이스바를 이용하여 메뉴를 사용할 때 재생

	DaramSound menuTitle;				// 타이틀 화면 배경음악

public:
	GsMenu() : DaramFrame(GS_MENU) { }

	void Initial();
	void Update(double);
	void Draw();
	void Dispose();
	void ImageLoad();

};
