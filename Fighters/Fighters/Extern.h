#pragma once

#include <DaramGraphics.h>
#include <DaramInput.h>
#include "MainWindow.h"

#include "GsLogo.h"
#include "GsMenu.h"
#include "GsSelect.h"
#include "GsGame.h"
#include "GsResult.h"

// 매인 창
extern MainWindow window;

// 그래픽스 클래스
extern DaramGraphics g;
// 인풋 클래스
extern DaramInput input;

// 게임 구성 요소
extern GsLogo g_Logo;
extern GsMenu g_Menu;
extern GsSelect g_Select;
extern GsGame g_Game;
extern GsResult g_Result;

// 로딩 이미지
extern DaramImage loadingImage;
// 페이드 이미지
extern DaramImage fade;