#include "GsLogo.h"
#include "Extern.h"
#include "Define.h"

#include "Ai.h"

void GsLogo::Initial()
{
	// 초기 설정
	fadeIn = true;
	fadeOut = false;
	alpha = 255;
	
	// 이미지 로드
	logo.Create(g.GetDevice(), "resource/EtcGraphic/Logo.dds");
	levelIcon.Create(g.GetDevice(), "resource/EtcGraphic/TestIcon.dds");
	forceIcon.Create(g.GetDevice(), "resource/EtcGraphic/ForceIcon.dds");

	// 사운드 로드
	logoSound.Initialize();
	logoSound.Create("resource/Sound/Logo.wav");

	logoAni.Load("resource/EtcGraphic/logo.bdani", g);
	logoAni.Play(0);
}

void GsLogo::Update(double ElapsedTime)
{
	static DaramDelay fadeIODelay(1000 / 60);

	// 페이드인
	if(fadeIn)
	{
		if(fadeIODelay.Checknow())
		{
			// 알파값 조절
			alpha -= 15;
			// 알파값이 0이라면
			if(alpha == 0)
			{
				// 로고 표시 딜레이 1초 적용
				delay.SetCheckMilisec(1000);
				// 사운드 재생
				logoSound.Play();
				// 페이드인 해제
				fadeIn = false;
			}
		}
	}
	// 페이드아웃
	else if(fadeOut)
	{
		if(fadeIODelay.Checknow())
		{
			// 알파값 조절
			alpha += 15;
			// 알파값이 255라면
			if(alpha == 255)
			{
				// 페이드아웃 해제
				fadeOut = false;
				// 메뉴 화면으로 넘어감
				window.SetState( GS_MENU, &g, &loadingImage, true );
			}
		}
	}
	else
	{
		// 1초가 지났다면
		if(delay.Checknow())
		{
			// 페이드아웃
			fadeOut = true;
		}
	}

	logoAni.AnimationUpdate();
	logoSound.Update();
}

void GsLogo::Draw()
{
	g.Clear(GetRGB(0xff, 0xff, 0xff));
	g.SetColor(GetRGB(255, 255, 255));
	g.DrawImage(logo, SCREEN_WIDTH/2 - logo.GetWidth() / 2, SCREEN_HEIGHT/2 - logo.GetHeight() / 2);
	g.DrawImage(forceIcon, 1080 + levelIcon.GetWidth() + forceIcon.GetWidth(), 10, forceIcon.GetWidth() / 2, forceIcon.GetHeight() / 2);
	g.DrawImage(levelIcon, SCREEN_WIDTH - levelIcon.GetWidth() - 5, 5);

	logoAni.AnimationDraw(g, SCREEN_WIDTH/2 - logo.GetWidth() / 2 - 20, SCREEN_HEIGHT/2 - logo.GetHeight() / 2 + 20, 20, 20);

	// 페이드 이미지를 그린다
	if(fadeIn || fadeOut)
	{
		g.SetColor(GetARGB(alpha, 255, 255, 255));
		g.DrawImage(fade, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	}
}

void GsLogo::Dispose()
{
	forceIcon.Dispose();
	levelIcon.Dispose();
	logo.Dispose();
}