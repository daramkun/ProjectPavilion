#define DLLEXPORT
#include "DaramInput.h"

void DaramInput::CreateInput(HWND Handle, bool ExclusiveMode, bool BackgroundMode, bool keyboardUse, bool mouseUse, bool joyUse)
{
	HRESULT result;
	DWORD exMode, bgMode;

	win = Handle;

	result = DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION, 
		IID_IDirectInput8, (VOID**)&input, NULL);
	if(FAILED(result))
	{
		MessageBox(NULL, "Direct Input 생성 오류", "인풋 장치 오류", NULL);
		PostQuitMessage(0);
		return;
	}

	this->keyboardUse = keyboardUse;
	this->mouseUse = mouseUse;
	this->joyUse = joyUse;

	if(keyboardUse)
		input->CreateDevice(GUID_SysKeyboard, &keyboard, NULL);
	if(mouseUse)
		input->CreateDevice(GUID_SysMouse, &mouse, NULL);
	if(joyUse)
		input->CreateDevice(GUID_Joystick, &joystick, NULL);

	if(ExclusiveMode)
		exMode = DISCL_EXCLUSIVE;
	else
		exMode = DISCL_NONEXCLUSIVE;

	if(BackgroundMode)
		bgMode = DISCL_BACKGROUND;
	else
		bgMode = DISCL_FOREGROUND;

	
	if(keyboard != NULL && keyboardUse)
		result = keyboard->SetCooperativeLevel(Handle, exMode | bgMode);
	if(mouse != NULL && mouseUse)
		result = mouse->SetCooperativeLevel(Handle, exMode | bgMode);
	if(joystick != NULL && joyUse)
		result = joystick->SetCooperativeLevel(Handle, exMode | bgMode);
	
	if(keyboard != NULL && keyboardUse)
		result = keyboard->SetDataFormat(&c_dfDIKeyboard);
	if(mouse != NULL && mouseUse)
		result = mouse->SetDataFormat(&c_dfDIMouse);
	if(joystick != NULL && joyUse)
		result = joystick->SetDataFormat(&c_dfDIJoystick);

	if(keyboard != NULL && keyboardUse)
		keyboard->Acquire();
	if(mouse != NULL && mouseUse)
		mouse->Acquire();
	if(joystick != NULL && joyUse)
		joystick->Acquire();
}

bool DaramInput::KeyDown(int key)
{
	if(!keyboardUse) return false;

	if(diks[key] & 0x80)
	{
		if(keylast[key])
			return false;
		else
		{
			keylast[key] = true;
			return true;
		}
	}
	else
	{
		keylast[key] = false;
		return false;
	}
}

bool DaramInput::KeyPress(int key)
{
	if(!keyboardUse) return false;

	return (diks[key] & 0x80) ? true : false;
}

bool DaramInput::KeyUp(int key)
{
	if(!keyboardUse) return false;

	if(!(diks[key] & 0x80))
	{
		if(!keylast[key])
			return false;
		else
		{
			keylast[key] = false;
			return true;
		}
	}
	else
		return false;
}

BYTE* DaramInput::GetPressedKey()
{
	return diks;
}

bool DaramInput::AnyKeyDown()
{
	for(int i = 0; i < 256; i++)
	{
		if(KeyDown(i))
			return true;
	}

	return false;
}

bool DaramInput::AnyKeyPress()
{
	for(int i = 0; i < 256; i++)
	{
		if(KeyPress(i))
			return true;
	}

	return false;
}

bool DaramInput::AnyKeyUp()
{
	for(int i = 0; i < 256; i++)
	{
		if(KeyUp(i))
			return true;
	}

	return false;
}

bool DaramInput::MouseDown(int mouseKey)
{
	if(!mouseUse) return false;

	if(mstate.rgbButtons[mouseKey] & 0x80)
	{
		if(mouselast[mouseKey])
			return false;
		else
		{
			mouselast[mouseKey] = true;
			return true;
		}
	}
	else
	{
		mouselast[mouseKey] = false;
		return false;
	}
}

bool DaramInput::MousePress(int mouseKey)
{
	if(!mouseUse) return false;

	return (mstate.rgbButtons[mouseKey] & 0x80) ? true : false;
}

bool DaramInput::MouseUp(int mouseKey)
{
	if(!mouseUse) return false;

	if(!(mstate.rgbButtons[mouseKey] & 0x80))
	{
		if(!mouselast[mouseKey])
			return false;
		else
		{
			mouselast[mouseKey] = false;
			return true;
		}
	}
	else
		return false;
}

bool DaramInput::AnyMouseDown()
{
	for(int i = 0; i < 4; i++)
	{
		if(MouseDown(i))
			return true;
	}

	return false;
}

bool DaramInput::AnyMousePress()
{
	for(int i = 0; i < 4; i++)
	{
		if(MousePress(i))
			return true;
	}

	return false;
}

bool DaramInput::AnyMouseUp()
{
	for(int i = 0; i < 4; i++)
	{
		if(MouseUp(i))
			return true;
	}

	return false;
}

int DaramInput::GetMouseX()
{
	if(!mouseUse) return 0;
	return mstate.lX;
}

int DaramInput::GetMouseY()
{
	if(!mouseUse) return 0;
	return mstate.lY;
}

int DaramInput::GetMouseZ()
{
	if(!mouseUse) return 0;
	return mstate.lZ;
}

bool DaramInput::JoystickDown(int joykey)
{
	if(!joyUse) return false;

	if(jstate.rgbButtons[joykey] & 0x80)
	{
		if(joylast[joykey])
			return false;
		else
		{
			joylast[joykey] = true;
			return true;
		}
	}
	else
	{
		joylast[joykey] = false;
		return false;
	}
}

bool DaramInput::JoystickPress(int joykey)
{
	if(!joyUse) return false;
	return (jstate.rgbButtons[joykey] & 0x80) ? true : false;
}

bool DaramInput::JoystickUp(int joykey)
{
	if(!joyUse) return false;

	if(!(jstate.rgbButtons[joykey] & 0x80))
	{
		if(!joylast[joykey])
			return false;
		else
		{
			joylast[joykey] = false;
			return true;
		}
	}
	else
		return false;
}

bool DaramInput::AnyJoystickDown()
{
	for(int i = 0; i < 32; i++)
	{
		if(JoystickDown(i))
			return true;
	}

	return false;
}

bool DaramInput::AnyJoystickPress()
{
	for(int i = 0; i < 32; i++)
	{
		if(JoystickPress(i))
			return true;
	}

	return false;
}

bool DaramInput::AnyJoystickUp()
{
	for(int i = 0; i < 32; i++)
	{
		if(JoystickUp(i))
			return true;
	}

	return false;
}

int DaramInput::GetJoyX()
{
	if(!joyUse) return 0;
	return jstate.lX;
}

int DaramInput::GetJoyY()
{
	if(!joyUse) return 0;
	return jstate.lY;
}

int DaramInput::GetJoyZ()
{
	if(!joyUse) return 0;
	return jstate.lZ;
}

void DaramInput::UpdateData()
{
	if(keyboard != NULL && keyboardUse)
	{
		ZeroMemory(diks, sizeof(diks));
		keyboard->GetDeviceState(sizeof(diks), diks);
	}

	if(mouse != NULL && mouseUse)
	{
		ZeroMemory(&mstate, sizeof(mstate));
		mouse->GetDeviceState(sizeof(mstate), &mstate);
	}
	
	if(joystick != NULL && joyUse)
	{
		ZeroMemory(&jstate, sizeof(jstate));
		joystick->GetDeviceState(sizeof(jstate), &jstate);
	}
}

bool DaramInput::IsKeyConn()
{
	if(!keyboardUse || keyboard == NULL)
		return false;
	else
		return true;
}

bool DaramInput::IsMsConn()
{
	if(!mouseUse || mouse == NULL)
		return false;
	else
		return true;
}

bool DaramInput::IsJoyConn()
{
	if(!joyUse || joystick == NULL)
		return false;
	else
		return true;
}

int DaramInput::GetMouseXFromWindow()
{
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(win, &pt);
	return pt.x;
}

int DaramInput::GetMouseYFromWindow()
{
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(win, &pt);
	return pt.y;
}

void DaramInput::SetMouseXToWindow(int x)
{
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(win, &pt);
	pt.x = x;
	ClientToScreen(win, &pt);
	SetCursorPos(pt.x, pt.y);
}

void DaramInput::SetMouseYToWindow(int y)
{
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(win, &pt);
	pt.y = y;
	ClientToScreen(win, &pt);
	SetCursorPos(pt.x, pt.y);
}

void DaramInput::SetMousePositionToWindow(int x, int y)
{
	POINT pt;
	pt.x = x;
	pt.y = y;
	ClientToScreen(win, &pt);
	SetCursorPos(pt.x, pt.y);
}

void DaramInput::Dispose()
{
	if(joyUse || joystick != NULL)
		joystick->Release();
	if(mouseUse || mouse != NULL)
		mouse->Release();
	if(keyboardUse || keyboard != NULL)
		keyboard->Release();
	
	if(input != NULL)
		input->Release();
}