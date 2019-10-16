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
	// ����� �ܼ� �ʱ�ȭ
	DaramConsole::Initialize();
	// â �ʱ�ȭ
	window.Initialize(MAKEINTRESOURCE(IDI_MAIN), MAKEINTRESOURCE(IDI_MAIN), IDC_ARROW, hInstance);
	// â ���� �� ��ŸƮ ���̾�α� ���
	DialogSetted setted = window.Create(SCREEN_WIDTH, SCREEN_HEIGHT, true);
	
	// ���� ��ŸƮ ���̾�αװ� ���� ��ư�� ������ ��� ����
	if(setted.dialogExit) { DaramConsole::Finalize(); return 0; }
	DaramConsole::PrintLine("â ���� �Ϸ�");

	// �׷��Ƚ� Ŭ���� ����
	g.Create(window.GetHandle(), !setted.Fullscreen, SCREEN_WIDTH, SCREEN_HEIGHT, D3DFMT_X8R8G8B8, D3DMULTISAMPLE_NONE, false);
	g.ChangeFontName("���� ���");
	g.ChangeFontQuality(FQ_ANTIALIASED);
	g.SetFontDesc();
	DaramConsole::PrintLine("�׷��Ƚ� ��ġ ���� �Ϸ�");

	// �ε� �̹��� �ε�
	loadingImage.Create(g.GetDevice(), "resource/EtcGraphic/nowloading.dds");
	DaramConsole::PrintLine("�ε� �̹��� �ε� �Ϸ�");
	// ���̵� �̹��� ����
	fade.Create(g.GetDevice(), GetRGB(0, 0, 0), 1, 1);
	DaramConsole::PrintLine("���̵� �̹��� ���� �Ϸ�");

	g.Clear(GetRGB(0, 0, 0));
	g.Present();

	// â ���
	window.Show();
	DaramConsole::PrintLine("â ���. ���� ����.");
	// ���������� ���� ����
	window.Run();

	// â�� ������ ����
	window.Close();
	// �ε� �̹��� ����
	loadingImage.Dispose();
	// ���̵� �̹��� ����
	fade.Dispose();

	// �ܼ� ����
	DaramConsole::Finalize();

	return 1;
}