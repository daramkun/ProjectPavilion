#pragma once

// ȭ�� ũ��
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

// ĳ���� �����Ѱ�
#define limitTouch 35

// ���� ����
enum GameState
{
	GS_LOGO = 0,
	GS_MENU,
	GS_SELECT,
	GS_GAME,
	GS_RESULT,
};

// �޴� ����
enum MenuState
{
	MS_START = 0,
	MS_OPTION,
	MS_CREATER,
	MS_EXIT,
};

// ���� �޴�
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

