#pragma once

#include <DaramGraphics.h>
#include <DaramInput.h>
#include "MainWindow.h"

#include "GsLogo.h"
#include "GsMenu.h"
#include "GsSelect.h"
#include "GsGame.h"
#include "GsResult.h"

// ���� â
extern MainWindow window;

// �׷��Ƚ� Ŭ����
extern DaramGraphics g;
// ��ǲ Ŭ����
extern DaramInput input;

// ���� ���� ���
extern GsLogo g_Logo;
extern GsMenu g_Menu;
extern GsSelect g_Select;
extern GsGame g_Game;
extern GsResult g_Result;

// �ε� �̹���
extern DaramImage loadingImage;
// ���̵� �̹���
extern DaramImage fade;