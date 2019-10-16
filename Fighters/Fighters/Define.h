#pragma once

// 화면 크기
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

// 캐릭터 접촉한계
#define limitTouch 35

// 게임 상태
enum GameState
{
	GS_LOGO = 0,
	GS_MENU,
	GS_SELECT,
	GS_GAME,
	GS_RESULT,
};

// 메뉴 상태
enum MenuState
{
	MS_START = 0,
	MS_OPTION,
	MS_CREATER,
	MS_EXIT,
};

// 서브 메뉴
enum SubMenuState
{
	SMS_START_1P = 0,
	SMS_START_2P = 1,
	SMS_START_NP = 2,

	SMS_OPTION_,
};

enum PlayMode
{
	PM_1P = 0,
	PM_2P = 1,
	PM_NP = 2,
};

