#include "MainWindow.h"

#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>

MainWindow window;
DialogSetted set;

DaramGraphics g;
DaramInput input;
DaramSound sound;

int count;

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevINstance,
				   LPSTR nCmdLine, int nCmdShow)
{
	//DaramConsole::Initialize();
	DaramConsole::PrintLine("Initialize Finger Attack");

	window.Initialize();
	DaramConsole::PrintLine("Intialize Finished");
	
	//FILE *fp = fopen("foption.txt", "rt");
	//bool noShow = false;
	//fscanf(fp, "%d", &noShow);
	//fclose(fp);

	//if(!noShow)
	//{
	//	set = window.Create(640, 480, false);
		//fp = fopen("foption.txt", "wt");
		//fprintf(fp, "%d", set.AfterNoShow);
		//fclose(fp);
	//}
	//else
	//{
		window.Create(640, 480, false);
	//}

	DaramConsole::PrintLine("Created Window");
	
	window.Show();
	DaramConsole::PrintLine("Show the Window. Message Loop Start");
	window.Run();

	DaramConsole::Finalize();

	return 1;
}