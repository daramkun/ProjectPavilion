#define DLLEXPORT

#include "resource.hpp"
#include "DaramGame.h"

#include "DaramConsole.h"

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdarg.h>

bool fullMode = false;
bool noShow = false;

DaramGame::DaramGame(int frameCount)
{
	nowState = 0;
	frames = new DaramFrame*[frameCount];
	for(int i = 0; i < frameCount; i++)
	{
		frames[i] = NULL;
	}
}

DaramGame::~DaramGame(void)
{
	delete [] frames;
}

void DaramGame::Initialize(LPSTR icon, LPSTR smIcon, LPSTR cursor, HINSTANCE hInstance)
{
	wc.cbClsExtra = NULL;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.cbWndExtra = NULL;
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.hCursor = LoadCursor(hInstance, cursor);
	wc.hIcon = LoadIcon(hInstance, icon);
	wc.hIconSm = LoadIcon(hInstance, smIcon);
	wc.hInstance = GetModuleHandle(NULL);
	wc.lpfnWndProc = WndProc;
	wc.lpszClassName = ClassName;
	wc.lpszMenuName = NULL;
	wc.style = NULL;

	RegisterClassEx(&wc);
}

DialogSetted DaramGame::Create(int width, int height, bool showDialog)
{
	int Width, Height, X, Y;
	RECT rect;

	DialogSetted temp;
	temp.dialogExit = false;

	if(showDialog)
	{
		int result = (int)DialogBox(GetModuleHandle("DaramLib.dll"), MAKEINTRESOURCE(IDD_START), HWND_DESKTOP, DlgProc);
		if(result == 0)
		{
			temp.AfterNoShow = false;
			temp.dialogExit = true;
			temp.Fullscreen = false;
			PostQuitMessage(0);
			return temp;
		}
		else
		{
			temp.Fullscreen = fullMode;
			temp.AfterNoShow = noShow;
		}
	}
	else
	{
		temp.AfterNoShow = false;
		temp.Fullscreen = false;
	}

	rect.top = rect.left = 0;
	rect.right = width;
	rect.bottom = height;

	AdjustWindowRect(&rect, WindowStyle_Game, true);

	Width = rect.right;
	Height = rect.bottom;

	X = (GetSystemMetrics(SM_CXSCREEN) / 2) - (Width / 2);
	Y = (GetSystemMetrics(SM_CYSCREEN) / 2) - (Height / 2);

	hWnd = ::CreateWindowEx(NULL, ClassName, WindowTitle, 
		WindowStyle_Game,
		X, Y, Width, Height, NULL, NULL, GetModuleHandle(NULL), NULL);

	return temp;
}

void DaramGame::Show()
{
	if(hWnd == NULL) return;
	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);
}

void DaramGame::Run()
{
	if(hWnd == NULL) return;

	Initial();

	while(true)
	{
		if(PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE))
		{
			if(!GetMessage(&msg, NULL, 0, 0))
				break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			FrameTime = GetTickCount();
			deltaTime = FrameTime - lastFrameTime;

			double ndt = (FPSTime += deltaTime);

			if(ndt >= 1000){
				FPS = FrameCount;
				FrameCount = 0;
				FPSTime = 0;
			}

			if(ndt >= 1000 / 60)
			{
				Update(deltaTime / 100.0);
				Draw();

				FrameCount++;
			}

			Sleep(1);

			lastFrameTime = FrameTime;
		}
	}

	if(nowState != -1)
		frames[nowState]->Dispose();
	Destroy();
}

void DaramGame::Close()
{
	CloseWindow(hWnd);
	DestroyWindow(hWnd);
	PostQuitMessage(0);
}

HWND DaramGame::GetHandle()
{
	return hWnd;
}

void DaramGame::SetStyle(DWORD style)
{
	SetWindowLong(hWnd, GWL_STYLE, style);
}

DWORD DaramGame::GetStyle()
{
	return GetWindowLong(hWnd, GWL_STYLE);
}

void DaramGame::SetTitle(const char *text)
{
	SetWindowText(hWnd, text);
}

void DaramGame::GetTitle(char *text)
{
	GetWindowText(hWnd, text, 256);
}

int DaramGame::GetFPS()
{
	return FPS;
}

int DaramGame::GetClientWidth()
{
	RECT rect = {0, };
	GetClientRect(hWnd, &rect);
	return rect.right;
}

int DaramGame::GetClientHeight()
{
	RECT rect = {0, };
	GetClientRect(hWnd, &rect);
	return rect.bottom;
}

LRESULT CALLBACK DaramGame::WndProc(HWND hWnd,
									  UINT uMsg, 
									  WPARAM wParam, 
									  LPARAM lParam)
{
	switch(uMsg)
	{
	case WM_CLOSE:
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}

	return 0;
}

BOOL CALLBACK DaramGame::DlgProc(HWND hDlg, 
									UINT uMsg,
									WPARAM wParam, 
									LPARAM lParam)
{

	switch(uMsg)
	{
	case WM_INITDIALOG:
		return TRUE;
	case WM_COMMAND:
		switch(LOWORD(wParam))
		{
		case IDOK:
			EndDialog(hDlg, 1);
			return TRUE;
		case IDCANCEL:
			EndDialog(hDlg, 0);
			return TRUE;
		case IDC_FULLSCREEN_CHECK:
			fullMode = !fullMode;
			break;
		case IDC_NOSHOW_CHECK:
			noShow = !noShow;
			break;
		}
		break;
	}

	return FALSE;
}

bool DaramGame::IsFocus()
{
	if(GetFocus() == hWnd)
		return true;
	else
		return false;
}

HWND DaramGame::GetWindowFromCursor()
{
	POINT pt;
	GetCursorPos(&pt);
	return WindowFromPoint(pt);
}

void DaramGame::AddFrame(int index, DaramFrame *frame)
{
	frames[index] = frame;
}

void DaramGame::SetState(int nextState, DaramGraphics *g, DaramImage *loadingImage, bool loadingFade)
{
	int fade = 255;
	DaramImage fader;
	
	if(g != NULL && loadingImage != NULL)
	{
		fader.Create(g->GetDevice(), GetRGB(0, 0, 0), 1, 1);
	}
	util::DaramDelay delay(1000 / 60);

	if(nextState > 10 || nextState < 0) return;
	if(frames[nowState] != NULL && *frames[nowState] != -1) frames[nowState]->Dispose();

	if(g != NULL && loadingImage != NULL)
	{
		do
		{
			g->Clear(0xffffffff);
			g->Begin();
			D3DCOLOR temp = g->GetColor();
			g->SetColor(GetRGB(255, 255, 255));
			g->DrawImage(*loadingImage, 0, 0);

			if(loadingFade)
			{
				g->SetColor(GetARGB(fade, 0, 0, 0));
				g->DrawImage(fader, 0, 0, g->GetBackBufferWidth(), g->GetBackBufferHeight());

				if(delay.Checknow())
				{
					fade -= 15;
					delay.SetTickCount();
				}
			}
			else
			{
				fade = 0;
			}
			
			g->SetColor(temp);
			g->End();
			g->Present();

		}while(fade > 0);
	}

	nowState = nextState;
	if(frames[nowState] != NULL && *frames[nowState] != -1) frames[nowState]->Initial();

	if(g != NULL && loadingImage != NULL)
	{
		do
		{
			g->Clear(0xffffffff);
			g->Begin();
			D3DCOLOR temp = g->GetColor();
			g->SetColor(GetRGB(255, 255, 255));
			g->DrawImage(*loadingImage, 0, 0);

			if(loadingFade)
			{
				g->SetColor(GetARGB(fade, 0, 0, 0));
				g->DrawImage(fader, 0, 0, g->GetBackBufferWidth(), g->GetBackBufferHeight());

				if(delay.Checknow())
				{
					fade += 15;
					delay.SetTickCount();
				}
			}
			else
			{
				fade = 255;
			}
			
			g->SetColor(temp);
			g->End();
			g->Present();

		}while(fade < 255);
	}
}

int DaramGame::GetState()
{
	return nowState;
}

void DaramGame::CallFrameUpdate(double ElapsedTime)
{
	if(nowState != -1 || *frames[nowState] != -1)
		frames[nowState]->Update(ElapsedTime);
}

void DaramGame::CallFrameDraw()
{
	if(nowState != -1 || *frames[nowState] != -1)
		frames[nowState]->Draw();
}

int DaramGame::MsgBox(char *title, UINT type, char *msgformat, ...)
{
	va_list data;
	char *text = new char[1024];

	va_start(data, msgformat);
	vsprintf_s(text, 1024, msgformat, data);
	va_end(data);

	int rtType = MessageBoxA(GetHandle(), text, title, type);
	delete [] text;

	return rtType;
}

////////////////////////////////////////////////////////////////////////

DaramFrame::DaramFrame()
{
	stateValue = -1;
}

DaramFrame::DaramFrame(int statevalue)
{
	stateValue = statevalue;
}

bool DaramFrame::operator==(DaramFrame frames)
{
	if(stateValue == frames.stateValue)
		return true;
	else
		return false;
}

bool DaramFrame::operator!=(DaramFrame frames)
{
	if(stateValue != frames.stateValue)
		return true;
	else
		return false;
}

bool DaramFrame::operator==(int statevalue)
{
	if(stateValue == statevalue)
		return true;
	else
		return false;
}

bool DaramFrame::operator!=(int statevalue)
{
	if(stateValue != statevalue)
		return true;
	else
		return false;
}