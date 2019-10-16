#pragma once

#include <windows.h>

#define ClassName "DARAMLIBRARY"
#define WindowTitle "Game about Daram Library"

#include "DaramLibrary.h"
#include "DaramFrame.h"
#include "DaramGraphics.h"
#include "DaramDelay.h"

#define WindowStyle_Game (WS_BORDER | WS_SYSMENU | WS_MINIMIZEBOX)
#define WindowStyle_None (WS_POPUP | WS_SYSMENU)

struct DialogSetted
{
	bool dialogExit;
	bool AfterNoShow;
	bool Fullscreen;
};

class DECLSPEC DaramGame
{
private:
	HWND hWnd;
	MSG msg;
	WNDCLASSEX wc;

	DWORD FrameTime;
	DWORD lastFrameTime;
	double deltaTime;
	double FPSTime;
	int FrameCount;
	int FPS;

	DaramFrame **frames;
	int nowState;

public:
	DaramGame(int frameCount = 10);
	~DaramGame(void);

	void Initialize(LPSTR icon = IDI_APPLICATION, LPSTR smIcon = IDI_APPLICATION, LPSTR cursor = IDC_ARROW, HINSTANCE hInstance = NULL);
	DialogSetted Create(int width = 640, int height = 480, bool showDialog = false);
	void Show();
	void Run();
	void Close();
	
	HWND GetHandle();

	virtual void Initial() = 0;
	virtual void Update(double ElapsedTime) = 0;
	virtual void Draw() = 0;
	virtual void Destroy() = 0;

	void SetStyle(DWORD style);
	DWORD GetStyle();

	int GetClientWidth();
	int GetClientHeight();

	int GetFPS();

	void SetTitle(const char *text);
	void GetTitle(char *text);

	bool IsFocus();

	HWND GetWindowFromCursor();

	void AddFrame(int index, DaramFrame *frame);
	void SetState(int nextState, DaramGraphics *g = NULL, DaramImage *loadingImage = NULL, bool loadingFade = false);
	int GetState();

	void CallFrameUpdate(double ElapsedTime);
	void CallFrameDraw();

	int MsgBox(char *title, UINT type, char *msgformat, ...);

private:
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, 
		WPARAM wParam, LPARAM lParam);
	static BOOL CALLBACK DlgProc(HWND hDlg, UINT uMsg,
		WPARAM wParam, LPARAM lParam);
};