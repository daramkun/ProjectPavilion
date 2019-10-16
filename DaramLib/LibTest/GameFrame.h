#pragma once

#include "../DaramLib/DaramImage.h"
#include "../DaramLib/DaramFrame.h"

class GameStart : public DaramFrame
{
public:
	GameStart() {  }
	GameStart(int state) : DaramFrame(state) {  }

	void Update(double ElapsedTime);
	void Draw();
};

class GameAttack : public DaramFrame
{
private:
	DaramImage bang, bg, enermy, finger1, finger2, frame;
	int mouseX, mouseY;

	POINT monster[10];
	bool monvisible[10];
	int monmode[10];
	bool isNotAttackMon[10];

	POINT bangs;
	bool bangvisible;

	bool mousestate;
public:
	GameAttack() {  }
	GameAttack(int state) : DaramFrame(state) {  }

	void Initial();
	void Update(double ElapsedTime);
	void Draw();
	void Dispose();
};

class GameEnd : public DaramFrame
{
public:
	GameEnd() {  }
	GameEnd(int state) : DaramFrame(state) {  }

	void Initial();
	void Update(double ElapsedTime);
	void Draw();
private:
	static BOOL CALLBACK DlgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
};
