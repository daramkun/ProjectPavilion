#pragma once

#include "../DaramLib/DaramLibrary.h"

#include "../DaramLib/DaramGame.h"
#include "../DaramLib/DaramGraphics.h"
#include "../DaramLib/DaramImage.h"
#include "../DaramLib/DaramSound.h"
#include "../DaramLib/DaramInput.h"
#include "../DaramLib/DaramDelay.h"
#include "../DaramLib/DaramConsole.h"
#pragma comment(lib, "../Release/DaramLib.lib")
using namespace util;

#include "GameExtern.h"
#include "GameFrame.h"

class MainWindow : public DaramGame
{
public:
	GameStart start;
	GameAttack game;
	GameEnd end;

	DaramDelay delay;

	int count;

public:
	MainWindow() {}

	void Initial()
	{
		start = GameStart(0);
		game = GameAttack(1);
		end = GameEnd(2);

		input.CreateInput(GetHandle(), true, true);
		DaramConsole::PrintLine("Created Input Class");

		SetTitle("Finger Attack - Daram Library Version");

		SetStyle(GetStyle() | WS_THICKFRAME | WS_MAXIMIZEBOX);
		g.Create(GetHandle(), !set.Fullscreen, 640, 480);
		DaramConsole::PrintLine("Created Graphics Class");

		g.ChangeFontName("³ª´®°íµñ");
		g.ChangeFontSize(18 * 2);
		g.ChangeFontWeight(FW_EXTRABOLD);
		g.ChangeFontItalic(true);
		g.SetFontDesc();
		DaramConsole::PrintLine("Setted Font");
		
		if(!sound.Initialize()) PostQuitMessage(0);

		delay.SetCheckMilisec(200);

		AddFrame(0, &start);
		DaramConsole::PrintLine("Setted Frame - Start");
		AddFrame(1, &game);
		DaramConsole::PrintLine("Setted Frame - Game");
		AddFrame(2, &end);
		DaramConsole::PrintLine("Setted Frame - End");

		SetState(0);

		DaramConsole::Print("Initial()\n");

		count = 0;
	}

	void Update(double ElapsedTime)
	{
		if(!IsFocus()) return;

		input.UpdateData();

		CallFrameUpdate(ElapsedTime);

		sound.Update();
	}

	void Draw()
	{
		g.Clear(GetRGB(255, 255, 255));
		g.Begin();

		CallFrameDraw();

		g.End();
		g.Present(0, 0, 320, 240);
	}

	void Destroy()
	{
		ShowCursor(true);
		input.Dispose();
		g.Dispose();
		DaramConsole::Print("Dispose()");
	}
};

extern MainWindow window;