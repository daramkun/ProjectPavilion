#pragma once

#pragma comment (lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

#include "DaramLibrary.h"

class DECLSPEC DaramInput sealed
{
	IDirectInput8 *input;
	IDirectInputDevice8 *keyboard;
	IDirectInputDevice8 *mouse;
	IDirectInputDevice8 *joystick;
	
	HWND win;

	DIMOUSESTATE mstate;
	BYTE diks[256];
	DIJOYSTATE jstate;
	
	bool keylast[256];
	bool mouselast[4];
	bool joylast[32];

	bool keyboardUse;
	bool mouseUse;
	bool joyUse;
public:
	void CreateInput(HWND, bool = false, bool = false, bool = true, bool = true, bool = false);

	bool KeyDown(int);
	bool KeyPress(int);
	bool KeyUp(int);

	BYTE* GetPressedKey();

	bool AnyKeyDown();
	bool AnyKeyPress();
	bool AnyKeyUp();

	bool MouseDown(int);
	bool MousePress(int);
	bool MouseUp(int);

	bool AnyMouseDown();
	bool AnyMousePress();
	bool AnyMouseUp();

	int GetMouseX();
	int GetMouseY();
	int GetMouseZ();

	bool JoystickDown(int);
	bool JoystickPress(int);
	bool JoystickUp(int);

	bool AnyJoystickDown();
	bool AnyJoystickPress();
	bool AnyJoystickUp();

	int GetJoyX();
	int GetJoyY();
	int GetJoyZ();

	bool IsKeyConn();
	bool IsMsConn();
	bool IsJoyConn();

	void UpdateData();

	int GetMouseXFromWindow();
	int GetMouseYFromWindow();

	void SetMouseXToWindow(int x);
	void SetMouseYToWindow(int y);
	void SetMousePositionToWindow(int x, int y);

	void Dispose();
};