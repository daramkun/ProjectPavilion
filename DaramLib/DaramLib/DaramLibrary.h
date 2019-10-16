#pragma once

#include <windows.h>

#include <d3d9.h>
#include <d3dx9.h>
#include <dinput.h>

#ifdef DLLEXPORT 
#define DECLSPEC __declspec(dllexport)
#else 
#define DECLSPEC __declspec(dllimport)
#endif

#define DARAM_VERSION 0x024

DECLSPEC char VersionCheck(int version);

DECLSPEC D3DCOLOR GetRGB(int r, int g, int b);
DECLSPEC D3DCOLOR GetARGB(int a, int r, int g, int b);

DECLSPEC bool IsCrashed(RECT rect1, RECT rect2);
DECLSPEC bool IsCrashedRect(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2);

DECLSPEC wchar_t* AnsiToUni(char* text);
DECLSPEC char* UniToAnsi(wchar_t* text);

// 키보드 키
enum InputKeys
{
//키보드 화살표 키
	KEY_UP					= 0xC8,
	KEY_DOWN				= 0xD0,
	KEY_LEFT				= 0xCB,
	KEY_RIGHT				= 0xCD,
	KEY_SPACE				= 0x39,
//키보드 문자 키
	KEY_A					= 0x1E,
	KEY_B					= 0x30,
	KEY_C					= 0x2E,
	KEY_D					= 0x20,
	KEY_E					= 0x12,
	KEY_F					= 0x21,
	KEY_G					= 0x22,
	KEY_H					= 0x23,
	KEY_I					= 0x17,
	KEY_J					= 0x24,
	KEY_K					= 0x25,
	KEY_L					= 0x26,
	KEY_M					= 0x32,
	KEY_N					= 0x31,
	KEY_O					= 0x18,
	KEY_P					= 0x19,
	KEY_Q					= 0x10,
	KEY_R					= 0x13,
	KEY_S					= 0x1F,
	KEY_T					= 0x14,
	KEY_U					= 0x16,
	KEY_V					= 0x2F,
	KEY_W					= 0x11,
	KEY_X					= 0x2D,
	KEY_Y					= 0x15,
	KEY_Z					= 0x2C,
//키보드 숫자 키
	KEY_0					= 0x0B,
	KEY_1					= 0x02,
	KEY_2					= 0x03,
	KEY_3					= 0x04,
	KEY_4					= 0x05,
	KEY_5					= 0x06,
	KEY_6					= 0x07,
	KEY_7					= 0x08,
	KEY_8					= 0x09,
	KEY_9					= 0x0A,
//키보드 기호 키
	KEY_MINUS				= 0x0c,
	KEY_EQUAL				= 0x0d,
	KEY_BACKSPACE			= 0x0e,
	KEY_TAB					= 0x0f,
	KEY_ENTER				= 0x1c,
	KEY_SEMICOLON			= 0x27,
	KEY_COLON				= 0x92,
	KEY_LEFTSHIFT			= 0x2A,
	KEY_RIGHTSHIFT			= 0x36,
	KEY_COMMA				= 0x33,
	KEY_PLUS				= 0x4E,
	KEY_ESC					= 0x01,
	KEY_DOT					= 0x34,
	KEY_SLASH				= 0x35,
	KEY_BACKSLASH			= 0x2B,
	KEY_LCTRL				= 0x1D,
	KEY_RCTRL				= 0x9D,
	KEY_LALT				= 0x38,
	KEY_RALT				= 0xB8,
	KEY_BSPACE				= 0x0E,
//키보드 함수 키
	KEY_F01					= 0x3B,
	KEY_F02					= 0x3C,
	KEY_F03					= 0x3D,
	KEY_F04					= 0x3E,
	KEY_F05					= 0x3F,
	KEY_F06					= 0x40,
	KEY_F07					= 0x41,
	KEY_F08					= 0x42,
	KEY_F09					= 0x43,
	KEY_F10					= 0x44,
	KEY_F11					= 0x57,
	KEY_F12					= 0x58,
//키보드 넘버 패드
	KEY_NUMLOCK				= 0x45,
	KEY_NUM0				= 0x52,
	KEY_NUM1				= 0x4F,
	KEY_NUM2				= 0x50,
	KEY_NUM3				= 0x51,
	KEY_NUM4				= 0x4B,
	KEY_NUM5				= 0x4C,
	KEY_NUM6				= 0x4D,
	KEY_NUM7				= 0x47,
	KEY_NUM8				= 0x48,
	KEY_NUM9				= 0x49,
//키보드 기타 키
	KEY_INSERT				= 0xD2,
	KEY_DELETE				= 0xD3,
	KEY_VOLUP				= 0xB0,
	KEY_VOLDOWN				= 0xAE,
};

// 마우스 키
enum InputMouseKeys
{
	MOUSE_LEFT				= 0,
	MOUSE_RIGHT				= 1,
	MOUSE_MID				= 2,
};

// 조이패드 키
enum InputJoypadKeys
{
	JOYPAD_1				= 0,
	JOYPAD_2				= 1,
	JOYPAD_3				= 2,
	JOYPAD_4				= 3,
	JOYPAD_L1				= 4,
	JOYPAD_L2				= 5,
	JOYPAD_R1				= 6,
	JOYPAD_R2				= 7,
	JOYPAD_SELECT			= 8,
	JOYPAD_START			= 9,
};

// 색상
#define CLR_WHITE			D3DCOLOR_XRGB(255, 255, 255)
#define CLR_BLACK			D3DCOLOR_XRGB(0, 0, 0)
#define CLR_BLUE			D3DCOLOR_XRGB(0, 0, 255)
#define CLR_RED				D3DCOLOR_XRGB(255, 0, 0)
#define CLR_GREEN			D3DCOLOR_XRGB(0, 255, 0)
#define CLR_PINK			D3DCOLOR_XRGB(255, 0, 255)
#define CLR_YELLOW			D3DCOLOR_XRGB(255, 255, 0)
#define CLR_CORNFLOWERBLUE	D3DCOLOR_XRGB(100, 149, 237)

enum FontQuality
{
	FQ_DEFAULT		       = 0,
	FQ_DRAFT	           = 1,
	FQ_PROOF	           = 2,
	FQ_NONANTIALIASED	   = 3,
	FQ_ANTIALIASED		   = 4,
	FQ_CLEARTYPE		   = 5,
	FQ_CLEARTYPE_NATURAL   = 6,
};