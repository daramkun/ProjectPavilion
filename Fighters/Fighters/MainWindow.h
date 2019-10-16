#pragma once

#include <DaramGame.h>
#include <DaramLibrary.h>

#include "Define.h"

/////////////////////////////////////////////////
// Class  Name : MainWindow
// Description : ���� â ���� �� ���� ����
// W o r k e r : ���翬
//  Work Date  : 08-01-08
/////////////////////////////////////////////////
class MainWindow : public DaramGame
{
private:
	GameState gameState;

public:
	MainWindow(void) : gameState(GS_LOGO) {  }
	~MainWindow(void) { }

	void Initial();
	void Update(double);
	void Draw();
	void Destroy();
};
