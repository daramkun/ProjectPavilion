#define _CRT_SECURE_NO_WARNINGS
#include "MainWindow.h"
#include <string>

#include "Extern.h"

void MainWindow::Initial()
{
	SetTitle("Pavilion - FPS:0");
	input.CreateInput(GetHandle(), true, true);

	AddFrame(GS_LOGO, (DaramFrame*)&g_Logo);
	AddFrame(GS_MENU, (DaramFrame*)&g_Menu);
	AddFrame(GS_SELECT, (DaramFrame*)&g_Select);
	AddFrame(GS_GAME, (DaramFrame*)&g_Game);
	AddFrame(GS_RESULT, (DaramFrame*)&g_Result);

	SetState(GS_LOGO, &g, &loadingImage);
}

void MainWindow::Update(double ElapsedTime)
{
	char temp[50] = "";
	sprintf(temp, "Pavilion - FPS:%d", GetFPS());

	SetTitle(temp);
	input.UpdateData();

	CallFrameUpdate(ElapsedTime);
}

void MainWindow::Draw()
{
	g.Clear(GetRGB(100, 149, 237));
	g.Begin();

	CallFrameDraw();

	g.SetColor( GetRGB( 255, 255, 255) );
	char *versionInfo = "Program Version 0.01 Alpha";
	g.ChangeFontSize(16);
	g.SetFontDesc();
	g.DrawAnsiText( 800 - strlen(versionInfo) * 6, 600 - 16, versionInfo);

	g.End();
	g.Present();
}

void MainWindow::Destroy()
{
	input.Dispose();
	g.Dispose();
}