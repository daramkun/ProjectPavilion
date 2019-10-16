#include "GsSelect.h"
#include "Extern.h"
#include "DaramConsole.h"
#include "Options.h"

void GsSelect::Initial()
{
	loc[0].x = 331, loc[0].y = 316;
	loc[1].x = 296, loc[1].y = 375;
	loc[2].x = 331, loc[2].y = 434;
	loc[3].x = 401, loc[3].y = 435;
	loc[4].x = 436, loc[4].y = 375;
	loc[5].x = 401, loc[5].y = 316;

	fadeIn = true;
	fadeOut = false;
	alpha = 255;

	bg.Create(g.GetDevice(), "resource/Select/bg.png");

	selImage[0].Create(g.GetDevice(), "resource/Select/sel_1p.png", D3DCOLOR_XRGB(255, 0, 255));
	selImage[1].Create(g.GetDevice(), "resource/Select/sel_2p.png", D3DCOLOR_XRGB(255, 0, 255));

	selSmImage[0].Create(g.GetDevice(), "resource/Select/s_karmen_sm.png", D3DCOLOR_XRGB(255, 0, 255));
	selSmImage[1].Create(g.GetDevice(), "resource/Select/s_tirwinn_sm.png", D3DCOLOR_XRGB(255, 0, 255));
	selSmImage[2].Create(g.GetDevice(), "resource/Select/s_rev_sm.png", D3DCOLOR_XRGB(255, 0, 255));
	selSmImage[3].Create(g.GetDevice(), "resource/Select/s_rustinL_sm.png", D3DCOLOR_XRGB(255, 0, 255));
	selSmImage[4].Create(g.GetDevice(), "resource/Select/s_rustin_sm.png", D3DCOLOR_XRGB(255, 0, 255));
	selSmImage[5].Create(g.GetDevice(), "resource/Select/s_lily_sm.png", D3DCOLOR_XRGB(255, 0, 255));

	selIllust[0].Create(g.GetDevice(), "resource/Select/s_karmen.png");
	selIllust[1].Create(g.GetDevice(), "resource/Select/s_tirwinn.png");
	selIllust[2].Create(g.GetDevice(), "resource/Select/s_rev.png");
	selIllust[3].Create(g.GetDevice(), "resource/Select/s_rustinL.png");
	selIllust[4].Create(g.GetDevice(), "resource/Select/s_rustin.png");
	selIllust[5].Create(g.GetDevice(), "resource/Select/s_lily.png");

	charAniFile[0] = "resource/Character/karmen.bdani";
	charAniFile[1] = "resource/Character/tirwinn.bdani";
	charAniFile[2] = "resource/Character/rev.bdani";
	charAniFile[3] = "resource/Character/rustin.bdani";
	charAniFile[4] = "resource/Character/rustinL.bdani";
	charAniFile[5] = "resource/Character/lily.bdani";

	charName.ImageLoad(g, NULL);

	charNames[0] = "Karmen Rosa";
	charNames[1] = "Tir Winn";
	charNames[2] = "Prani Rev";
	charNames[3] = "Rustin";
	charNames[4] = "Rustin";
	charNames[5] = "Lily Olga";

	bgSound.Initialize();
	bgSound.CreateStream("resource/Music/Select.mp3");
	bgSound.SetVolume(0.30f);

	selLoc1 = 0;
	selLoc2 = 4;

	selOk1 = false;
	selOk2 = false;

}

void GsSelect::Update(double ElapsedTime)
{
	if(fadeIn)
	{
		alpha -= 15;
		if(alpha == 0)
		{
			alpha = 0;
			fadeIn = false;

			bgSound.Play();
		}
	}
	else if(fadeOut)
	{
		alpha += 15;
		if(alpha == 255)
		{
			window.SetState(nextState, &g, &loadingImage, true);
			fadeOut = false;
		}
	}
	else
	{
		if(!selOk1)
		{
			if( input.KeyDown( p1Cmd.up ) ) 
			{
				selKeyCheck1[0] = true ;
				UpKeyPress1() ;
				selDelay1.SetCheckMilisec(200) ;
			}
			if( !input.KeyPress( p1Cmd.up ) )
			{
				selKeyCheck1[0] = false ;
			}

			if( input.KeyDown(p1Cmd.down) )
			{
				selKeyCheck1[1] = true ;
				DownKeyPress1() ;
				selDelay1.SetCheckMilisec(200) ;
			}
			if( !input.KeyPress(p1Cmd.down) )
			{
				selKeyCheck1[1] = false ;
			}

			if( input.KeyDown( p1Cmd.right ) )
			{
				selKeyCheck1[2] = true ;
				RightKeyPress1() ;
				selDelay1.SetCheckMilisec(200) ;
			}
			if( !input.KeyPress( p1Cmd.right ) )
			{
				selKeyCheck1[2] = false ;
			}

			if( input.KeyDown(p1Cmd.left) )
			{
				selKeyCheck1[3] = true ;
				LeftKeyPress1() ;
				selDelay1.SetCheckMilisec(200) ;
			}
			if( !input.KeyPress(p1Cmd.left) )
			{
				selKeyCheck1[3] = false ;
			}

			if(input.KeyDown(p1Cmd.a))
			{
				selOk1 = true;

				if(playMode == PM_1P)
				{
					selLoc2 = 0 ;
					selOk2 = true;
					switch(selLoc2)
					{
					case 0:
						g_Game.aiFile = "resource/Ai/karmen.lua";
						break;
					}
				}
				else
					g_Game.aiFile = "";
			}
		}

		
		if(playMode == PM_2P && !selOk2)
		{
			if( input.KeyDown( p2Cmd.up ) ) 
			{
				selKeyCheck2[0] = true ;
				UpKeyPress2() ;
				selDelay2.SetCheckMilisec(200) ;
			}
			if( !input.KeyPress( p2Cmd.up ) )
			{
				selKeyCheck2[0] = false ;
			}

			if( input.KeyDown(p2Cmd.down) )
			{
				selKeyCheck2[1] = true ;
				DownKeyPress2() ;
				selDelay2.SetCheckMilisec(200) ;
			}
			if( !input.KeyPress(p2Cmd.down) )
			{
				selKeyCheck2[1] = false ;
			}

			if( input.KeyDown( p2Cmd.right ) )
			{
				selKeyCheck2[2] = true ;
				RightKeyPress2() ;
				selDelay2.SetCheckMilisec(200) ;
			}
			if( !input.KeyPress( p2Cmd.right ) )
			{
				selKeyCheck2[2] = false ;
			}

			if( input.KeyDown(p2Cmd.left) )
			{
				selKeyCheck2[3] = true ;
				LeftKeyPress2() ;
				selDelay2.SetCheckMilisec(200) ;
			}
			if( !input.KeyPress(p2Cmd.left) )
			{
				selKeyCheck2[3] = false ;
			}

			if(input.KeyDown(p2Cmd.a))
			{
				selOk2 = true;
			}
		}

		if(input.KeyDown(p1Cmd.s))
		{
			selOk1 = false;
		}

		if(playMode == PM_2P && input.KeyDown(p2Cmd.s))
		{
			selOk2 = false;
		}

		if(input.KeyDown(KEY_ESC) || input.KeyDown(KEY_BACKSPACE))
		{
			nextState = GS_MENU;
			fadeOut = true;
			return;
		}

		if(selOk1 && selOk2)
		{
			nextState = GS_GAME;
			g_Game.playMode = playMode;
			fadeOut = true;
			return;
		}
	}

	bgSound.Update();
	KeyCheck() ;
}

void GsSelect::Draw()
{
	// TODO: 캐릭터 선택 화면을 그린다.
	g.DrawImage(bg, 0, 0);

	for(int i = 0; i < 6; i++)
	{
		g.DrawImage(selSmImage[i], loc[i].x + 1, loc[i].y + 1);
	}

	g.DrawImage(selImage[0], loc[selLoc1].x, loc[selLoc1].y - 11);
	if(playMode == PM_2P || playMode == PM_NP)
		g.DrawImage(selImage[1], loc[selLoc2].x, loc[selLoc2].y - 11);

	g.DrawImage(selIllust[selLoc1], 43, 201);
	g.DrawImage(selIllust[selLoc2], 533, 201);

	charName.Draw(g, charNames[selLoc1], 42, 528, 20);
	charName.Draw(g, charNames[selLoc2], 534, 528, 20);

	if(fadeIn || fadeOut)
	{
		g.SetColor(GetARGB(alpha, 255, 255, 255));
		g.DrawImage(fade, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	}
}

void GsSelect::KeyCheck()
{
	if( selDelay1.Checknow() )
	{
		// 위
		UpKeyPress1() ;
		// 아래
		DownKeyPress1() ;
		// 오른쪽
		RightKeyPress1() ;
		// 왼쪽
		LeftKeyPress1() ;
	}

	if( selDelay2.Checknow() )
	{
		// 위
		UpKeyPress2() ;
		// 아래
		DownKeyPress2() ;
		// 오른쪽
		RightKeyPress2() ;
		// 왼쪽
		LeftKeyPress2() ;
	}
}

void GsSelect::UpKeyPress1()
{
	if( selKeyCheck1[0] )
	{
		if( selLoc1 < 3 )	selLoc1 -= 1 ;
		else if( selLoc1 < 5 )	selLoc1 += 1 ;
		if( selLoc1 < 0 ) selLoc1 = 0 ;
	}
}

void GsSelect::UpKeyPress2()
{
	if( selKeyCheck2[0] )
	{
		if( selLoc2 < 3 )	selLoc2 -= 1 ;
		else if( selLoc2 < 5 )	selLoc2 += 1 ;
		if( selLoc2 < 0 ) selLoc2 = 0 ;
	}
}

void GsSelect::DownKeyPress1()
{
	if( selKeyCheck1[1] )
	{
		if( selLoc1 < 2 ) selLoc1 += 1 ;
		else if( selLoc1 > 3 ) selLoc1 -= 1 ;
	}
}

void GsSelect::DownKeyPress2()
{
	if( selKeyCheck2[1] )
	{
		if( selLoc2 < 2 ) selLoc2 += 1 ;
		else if( selLoc2 > 3 ) selLoc2 -= 1 ;
	}
}

void GsSelect::RightKeyPress1()
{
	if( selKeyCheck1[2] )
	{
		if( selLoc1 == 0 )	selLoc1 = 5 ;
		else if( selLoc1 == 2 )	selLoc1 = 3 ;
	}
}

void GsSelect::RightKeyPress2()
{
	if( selKeyCheck2[2] )
	{
		if( selLoc2 == 0 )	selLoc2 = 5 ;
		else if( selLoc2 == 2 )	selLoc2 = 3 ;
	}
}

void GsSelect::LeftKeyPress1()
{
	if( selKeyCheck1[3] )
	{
		if( selLoc1 == 5 )	selLoc1 = 0 ;
		else if( selLoc1 == 3 )	selLoc1 = 2 ;
	}
}

void GsSelect::LeftKeyPress2()
{
	if( selKeyCheck2[3] )
	{
		if( selLoc2 == 5 )	selLoc2 = 0 ;
		else if( selLoc2 == 3 )	selLoc2 = 2 ;
	}
}

void GsSelect::Dispose()
{
	charName.Dispose();

	if(serverIp != NULL)
	{
		delete serverIp;
		serverIp = NULL;
	}

	selImage[0].Dispose();
	selImage[1].Dispose();

	bg.Dispose();

	bgSound.Stop();
	bgSound.Dispose();
}