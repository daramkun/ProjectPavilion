#include "GameExtern.h"

#include "GameFrame.h"
#include "MainWindow.h"

#define _CRT_SECURE_NO_WARNINGS
#include <fstream>
using namespace std;

#include "resource.h"

char name[120] = "";
int highscore = 0;

void GameStart::Update(double ElapsedTime)
{
	if(input.MouseDown(MOUSE_LEFT) ||
		((input.IsJoyConn()) ?
		input.JoystickDown(JOYPAD_4) : 0) ||
		input.KeyDown(KEY_SPACE))
	{
		window.SetState(1);
	}

	DaramConsole::PrintLine("Update(%f)", ElapsedTime);
}

void GameStart::Draw()
{
	g.SetColor(GetRGB(0, 0, 0));
	g.DrawUniText
		(20, 20, L"게임을 플레이 하시려면\n화면을 클릭하세요. ㅇㅅㅇ");
	DaramConsole::PrintLine("Draw()");
}

void GameAttack::Initial()
{
	count = 0;

	mouseX = 160;
	mouseY = 120;
	DaramConsole::PrintLine("마우스 좌표 설정");

	// Images Load
	bang.Create(g.GetDevice(), "./Data/bang.png");
	bg.Create(g.GetDevice(), "./Data/bg.png");
	enermy.Create(g.GetDevice(), "./Data/enermy.png");
	finger1.Create(g.GetDevice(), "./Data/finger1.png");
	finger2.Create(g.GetDevice(), "./Data/finger2.png");
	frame.Create(g.GetDevice(), "./Data/frame.png");
	DaramConsole::PrintLine("이미지 로드 완료");

	sound.Create("./Data/Laser.wav");							// Sound Create From File
	DaramConsole::PrintLine("사운드 로드 완료");

	//ShowCursor(false);
	DaramConsole::PrintLine("Initial()");
}

void GameAttack::Update(double ElapsedTime)
{
	static DWORD gtc = GetTickCount();

	if(window.GetWindowFromCursor() == window.GetHandle())
	{
		mouseX = input.GetMouseXFromWindow();
		mouseY = input.GetMouseYFromWindow();
		//mouseX += input.GetMouseX();
		//mouseY += input.GetMouseY();
	}

	/*if(input.IsJoyConn())
	{
		if(input.GetJoyX() > 32511)
			mouseX += 20;
		else if(input.GetJoyX() < 32511)
			mouseX -= 20;

		if(input.GetJoyY() > 32511)
			mouseY += 20;
		else if(input.GetJoyY() < 32511)
			mouseY -= 20;
	}

	if(input.KeyPress(KEY_UP)) mouseY -= 20;
	if(input.KeyPress(KEY_DOWN)) mouseY += 20;
	if(input.KeyPress(KEY_LEFT)) mouseX -= 20;
	if(input.KeyPress(KEY_RIGHT)) mouseX += 20;*/

	if(mouseX < 0) mouseX = 0;
	if(mouseY < 0) mouseY = 0;
	if(mouseX > 640) mouseX = 640;
	if(mouseY > 480) mouseY = 480;

	ElapsedTime *= 3;

	for(int i = 0; i < 10; i++)
	{
		if(!monvisible[i])
		{
			monvisible[i] = true;
			monmode[i] = (rand() % 2);

			switch(monmode[i])
			{
			case 0:
				monster[i].x = 0;
				monster[i].y = rand() % (240) + 240;
				break;
			case 1:
				monster[i].x = 640;
				monster[i].y = rand() % (240) + 240;
				break;
			}

			isNotAttackMon[i] = ((rand() % 4) == 0) ? true : false;

			DaramConsole::PrintLine("몬스터 생성");

			break;
		}
	}

	for(int i = 0; i < 10; i++)
	{
		if(monvisible[i])
		{
			switch(monmode[i])
			{
			case 0:
				monster[i].x += 
					(long)((rand() % 20) * ElapsedTime);
				monster[i].y += 
					(long)(((rand() % 40) - 20) * ElapsedTime);
				break;
			case 1:
				monster[i].x -= 
					(long)((rand() % 20) * ElapsedTime);
				monster[i].y += 
					(long)(((rand() % 40) - 20) * ElapsedTime);
				break;
			}

			if(monster[i].y <= 240)
				monster[i].y += 20;

			if(monster[i].y > 480)
				monster[i].y -= 20;

			if(monster[i].x > 640 || monster[i].x < 0)
			{
				monvisible[i] = false;
				if(!isNotAttackMon[i])
				{
					--count;
					DaramConsole::PrintLine("몬스터 %d 도망 성공, 1포인트 감소", i);
				}
				else
					count++;

				DaramConsole::PrintLine("Score : %d", count);
			}
		}
	}

	if(input.MouseDown(MOUSE_LEFT) || 
		((input.IsJoyConn()) ? 
		input.JoystickDown(JOYPAD_4) : 0) ||
		input.KeyDown(KEY_SPACE))
	{
		for(int i = 0; i < 10; i++)
		{
			if(monvisible[i])
			{
				if( IsCrashedRect(monster[i].x, monster[i].y, 60, 60, mouseX - 4, mouseY - 4, 5, 5))
				{
					if(isNotAttackMon[i])
						window.SetState(2);

					count += 3;

					mousestate = true;

					monvisible[i] = false;
					bangs.x = monster[i].x -= 30;
					bangs.y = monster[i].y -= 30;
					bangvisible = true;
					window.delay.SetCheckMilisec(200);

					sound.Play();

					DaramConsole::PrintLine("몬스터 %d 팅겨냄, 3포인트 증가", i);
					DaramConsole::PrintLine("Score : %d", count);
				}
			}
		}
	}

	if(bangvisible)
	{
		if(window.delay.Checknow())
		{
			bangvisible = false;
			gtc = GetTickCount();
		}
	}
	DaramConsole::PrintLine("Update(%f)", ElapsedTime);
}

void GameAttack::Draw()
{
	bool joyKeycheck = false;

	g.SetColor(CLR_WHITE);

	g.DrawImage(bg, 0, 0, bg.GetWidth() * 2, bg.GetHeight() * 2);

	for(int i = 0; i < 10; i++)
	{
		if(isNotAttackMon[i])
			g.SetColor(GetRGB(100, 10, 10));
		else
			g.SetColor(CLR_WHITE);
		g.DrawImage(enermy, monster[i].x, monster[i].y, 
		enermy.GetWidth() * 2, enermy.GetHeight() * 2);
	}

	g.SetColor(CLR_WHITE);

	if(bangvisible)
		g.DrawImage(bang, bangs.x, bangs.y, 
		bang.GetWidth() * 2, bang.GetHeight() * 2);

	g.DrawImage(frame, 0, 0, frame.GetWidth() * 2, frame.GetHeight() * 2);

	if(input.IsJoyConn())
	{
		if(!input.JoystickPress(JOYPAD_4))
			joyKeycheck = true;
		else
			joyKeycheck = false;
	}

	if(!input.MousePress(MOUSE_LEFT) || joyKeycheck)
		g.DrawImage(finger1, mouseX - 24, mouseY - 94, finger1.GetWidth() * 2, finger1. GetHeight() * 2);
	else
		g.DrawImage(finger2, mouseX - 24, mouseY - 94, finger2.GetWidth() * 2, finger2.GetHeight() * 2);

	g.SetColor(GetRGB(0, 0, 0));
	g.DrawAnsiText(0, 0, "스코어: %d, FPS : %d", count, window.GetFPS());
	DaramConsole::PrintLine("Draw()");
}

void GameAttack::Dispose()
{
	ShowCursor(true);
	DaramConsole::PrintLine("Dispose()");
}

void GameEnd::Initial()
{
	DaramConsole::PrintLine("Waiting Initial()");
	FILE *fp;
	fp = fopen("highscore.txt", "rt");
	fscanf(fp, "%s", name);
	fscanf(fp, "%d", &highscore);
	fclose(fp);
	DaramConsole::PrintLine("File Loaded");

	if(highscore < count)
	{
		DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_SCORE), window.GetHandle(), DlgProc);
		highscore = count;
	}

	fp = fopen("highscore.txt", "wt");
	fprintf(fp, "%s ", name);
	fprintf(fp, "%d", highscore);
	fclose(fp);
	DaramConsole::PrintLine("File Saved");
	DaramConsole::PrintLine("Initial()");
}

void GameEnd::Update(double ElapsedTime)
{
	if(input.KeyDown(KEY_SPACE))
	{
		PostQuitMessage(0);
		return;
	}
	DaramConsole::PrintLine("Update(%f)", ElapsedTime);
}

void GameEnd::Draw()
{
	g.SetColor(GetRGB(0, 0, 0));

	g.DrawAnsiText(0, 0, "최고 기록자 : %s, 포인트 : %d", name, highscore);

	g.DrawUniText(20, 100,
		L"끝났습니다!\n게임을 종료하시려면,\n스페이스바 키를 눌러주세요. ㅇㅅㅇ");
	DaramConsole::PrintLine("Draw()");
}

BOOL CALLBACK GameEnd::DlgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg)
	{
	case WM_INITDIALOG:
		return TRUE;
	case WM_COMMAND:
		switch(LOWORD(wParam))
		{
		case IDOK:
			GetDlgItemTextA(hWnd, IDC_NAME, name, 120);
			EndDialog(hWnd, 0);
			return TRUE;
		}
		break;
	}

	return FALSE;
}