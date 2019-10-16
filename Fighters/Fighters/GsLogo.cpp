#include "GsLogo.h"
#include "Extern.h"
#include "Define.h"

#include "Ai.h"

void GsLogo::Initial()
{
	// �ʱ� ����
	fadeIn = true;
	fadeOut = false;
	alpha = 255;
	
	// �̹��� �ε�
	logo.Create(g.GetDevice(), "resource/EtcGraphic/Logo.dds");
	levelIcon.Create(g.GetDevice(), "resource/EtcGraphic/TestIcon.dds");
	forceIcon.Create(g.GetDevice(), "resource/EtcGraphic/ForceIcon.dds");

	// ���� �ε�
	logoSound.Initialize();
	logoSound.Create("resource/Sound/Logo.wav");

	logoAni.Load("resource/EtcGraphic/logo.bdani", g);
	logoAni.Play(0);
}

void GsLogo::Update(double ElapsedTime)
{
	static DaramDelay fadeIODelay(1000 / 60);

	// ���̵���
	if(fadeIn)
	{
		if(fadeIODelay.Checknow())
		{
			// ���İ� ����
			alpha -= 15;
			// ���İ��� 0�̶��
			if(alpha == 0)
			{
				// �ΰ� ǥ�� ������ 1�� ����
				delay.SetCheckMilisec(1000);
				// ���� ���
				logoSound.Play();
				// ���̵��� ����
				fadeIn = false;
			}
		}
	}
	// ���̵�ƿ�
	else if(fadeOut)
	{
		if(fadeIODelay.Checknow())
		{
			// ���İ� ����
			alpha += 15;
			// ���İ��� 255���
			if(alpha == 255)
			{
				// ���̵�ƿ� ����
				fadeOut = false;
				// �޴� ȭ������ �Ѿ
				window.SetState( GS_MENU, &g, &loadingImage, true );
			}
		}
	}
	else
	{
		// 1�ʰ� �����ٸ�
		if(delay.Checknow())
		{
			// ���̵�ƿ�
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

	// ���̵� �̹����� �׸���
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