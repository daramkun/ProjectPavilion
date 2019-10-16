#include <DaramConsole.h>

#include "resource.h"

#include "MainWindow.h"
#include "Extern.h"
#include "Define.h"

#include "GsLogo.h"
#include "GsMenu.h"
#include "GsSelect.h"
#include "GsGame.h"
#include "GsResult.h"

#pragma comment(lib, "DaramLib.lib")

using namespace util;

MainWindow window;
DaramGraphics g;
DaramInput input;

GsLogo g_Logo;
GsMenu g_Menu;
GsSelect g_Select;
GsGame g_Game;
GsResult g_Result;

DaramImage loadingImage;
DaramImage fade;

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR nCmdLine, int nCmdShow)
{
	// 디버그 콘솔 초기화
	DaramConsole::Initialize();
	// 창 초기화
	window.Initialize(MAKEINTRESOURCE(IDI_MAIN), MAKEINTRESOURCE(IDI_MAIN), IDC_ARROW, hInstance);
	// 창 생성 및 스타트 다이얼로그 띄움
	DialogSetted setted = window.Create(SCREEN_WIDTH, SCREEN_HEIGHT, true);
	
	// 만약 스타트 다이얼로그가 종료 버튼이 눌렸을 경우 종료
	if(setted.dialogExit) { DaramConsole::Finalize(); return 0; }
	DaramConsole::PrintLine("창 생성 완료");

	// 그래픽스 클래스 생성
	g.Create(window.GetHandle(), !setted.Fullscreen, SCREEN_WIDTH, SCREEN_HEIGHT, D3DFMT_X8R8G8B8, D3DMULTISAMPLE_NONE, false);
	g.ChangeFontName("맑은 고딕");
	g.ChangeFontQuality(FQ_ANTIALIASED);
	g.SetFontDesc();
	DaramConsole::PrintLine("그래픽스 장치 생성 완료");

	// 로딩 이미지 로드
	loadingImage.Create(g.GetDevice(), "resource/EtcGraphic/nowloading.dds");
	DaramConsole::PrintLine("로딩 이미지 로드 완료");
	// 페이드 이미지 생성
	fade.Create(g.GetDevice(), GetRGB(0, 0, 0), 1, 1);
	DaramConsole::PrintLine("페이드 이미지 생성 완료");

	g.Clear(GetRGB(0, 0, 0));
	g.Present();

	// 창 띄움
	window.Show();
	DaramConsole::PrintLine("창 띄움. 게임 시작.");
	// 본격적으로 게임 시작
	window.Run();

	// 창을 완전히 닫음
	window.Close();
	// 로딩 이미지 제거
	loadingImage.Dispose();
	// 페이드 이미지 제거
	fade.Dispose();

	// 콘솔 해제
	DaramConsole::Finalize();

	return 1;
}