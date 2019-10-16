#include "GsGame.h"
#include "Extern.h"
#include "Options.h"
#include <DaramConsole.h>
using namespace util;

void GsGame::Initial()
{
	p1.ani.Load(g_Select.charAniFile[g_Select.selLoc1], g);
	p2.ani.Load(g_Select.charAniFile[g_Select.selLoc2], g);

	p1.x = 20 ;
	p1.y = 220 ;
	p2.x = 500 ;
	p2.y = 220 ;
	p1.ani.Play("breath_right") ;
	p1.dir = DIR_RIGHT ;
	p2.ani.Play( "breath_left" ) ;
	p2.dir = DIR_LEFT ;
	map.Load("resource/Map/AssemblyHall.png") ;

	p2Ai.Initialize();

	artipectBar[0].Create(g.GetDevice(), "resource/Interface/artbar.png", D3DCOLOR_XRGB(255, 0, 255));
	artipectBar[1].Create(g.GetDevice(), "resource/Interface/artbar_gage.png", D3DCOLOR_XRGB(255, 0, 255));
	
	artipects[0].Create(g.GetDevice(), "resource/Interface/art1.png", D3DCOLOR_XRGB(255, 0, 255));
	artipects[1].Create(g.GetDevice(), "resource/Interface/art2.png", D3DCOLOR_XRGB(255, 0, 255));
	artipects[2].Create(g.GetDevice(), "resource/Interface/art3.png", D3DCOLOR_XRGB(255, 0, 255));
	
	beadBar[0].Create(g.GetDevice(), "resource/Interface/beadbar.png", D3DCOLOR_XRGB(255, 0, 255));
	beadBar[1].Create(g.GetDevice(), "resource/Interface/bead_gage.png", D3DCOLOR_XRGB(255, 0, 255));

	mapState[0].Create(g.GetDevice(), "resource/Map/sun.png", D3DCOLOR_XRGB(255, 0, 255));
	mapState[1].Create(g.GetDevice(), "resource/Map/cloud.png", D3DCOLOR_XRGB(255, 0, 255));
	mapState[2].Create(g.GetDevice(), "resource/Map/moon.png", D3DCOLOR_XRGB(255, 0, 255));
	mapState[3].Create(g.GetDevice(), "resource/Map/rain.png", D3DCOLOR_XRGB(255, 0, 255));
	mapState[4].Create(g.GetDevice(), "resource/Map/seal.png", D3DCOLOR_XRGB(255, 0, 255));
	mapState[5].Create(g.GetDevice(), "resource/Map/snow.png", D3DCOLOR_XRGB(255, 0, 255));
	mapState[6].Create(g.GetDevice(), "resource/Map/wind.png", D3DCOLOR_XRGB(255, 0, 255));
	mapState[7].Create(g.GetDevice(), "resource/Map/mist.png", D3DCOLOR_XRGB(255, 0, 255));

	
}

void GsGame::Update(double ElapsedTime)
{
	if(input.KeyDown(p1Cmd.a))
		Player1State(p1.dir, ACT_ATTACK1) ;
	if(input.KeyDown(p1Cmd.s))
		Player1State(p1.dir, ACT_ATTACK2) ;
	if(input.KeyDown(p1Cmd.d))
		Player1State(p1.dir, ACT_ATTACK3) ;
	if( input.KeyPress( p1Cmd.right ) )
	{
		if(p1.action == ACT_NONE || p1.action == ACT_WALK)
		{
			p1.x += 10 ;
			Player1State(p1.dir, ACT_WALK ) ;
		}
	}
	if( input.KeyPress( p1Cmd.left ) )
	{
		if(p1.action == ACT_NONE || p1.action == ACT_WALK)
		{
			p1.x -= 10 ;
			Player1State( p1.dir, ACT_WALK ) ;
		}
	}

	if(playMode == PM_2P)
	{	
		if(input.KeyDown(p2Cmd.a))
			Player2State(p2.dir, ACT_ATTACK1) ;
		if(input.KeyDown(p2Cmd.s))
			Player2State(p2.dir, ACT_ATTACK2) ;
		if(input.KeyDown(p2Cmd.d))
			Player2State(p2.dir, ACT_ATTACK3) ;

		if( input.KeyPress( p2Cmd.right ) )
		{
			if(p2.action == ACT_NONE || p2.action == ACT_WALK)
			{
				p2.x += 10 ;
				Player2State(p2.dir, ACT_WALK ) ;
			}
		}
		if( input.KeyPress( p2Cmd.left ) )
		{
			if(p2.action == ACT_NONE || p2.action == ACT_WALK)
			{
				p2.x -= 10 ;
				Player2State( p2.dir, ACT_WALK ) ;
			}
		}
	}

	if(aiFile != "")
	{
		p2Ai.RunAI(aiFile);
		DaramConsole::PrintLine("AI 파일 실행 - %s", aiFile);
	}

	p1.Update() ;
	p2.Update() ;
	p1.ani.AnimationUpdate() ;
	p2.ani.AnimationUpdate() ;
	p1.CheckCrash(p2);
	p2.CheckCrash(p1);
	
	CharacterMoveCheck();

	if( input.KeyPress( KEY_F11 ) )
	{
		g_Result.Check1pWin = true ;
		window.SetState( GS_RESULT, &g, &loadingImage, true ) ;
	}
	if( input.KeyPress( KEY_F12 ) )
	{
		g_Result.Check1pWin = false ;
		window.SetState( GS_RESULT, &g, &loadingImage, true ) ;
	}
}

void GsGame::Draw()
{
	map.Draw(g) ;

	if( p1.action != ACT_NONE && p2.action == ACT_NONE )
	{
		p2.ani.AnimationDraw( g, p2.x, p2.y ) ;
		p1.ani.AnimationDraw( g, p1.x, p1.y ) ;

	}
	else
	{
		p1.ani.AnimationDraw( g, p1.x, p1.y ) ;
		p2.ani.AnimationDraw( g, p2.x, p2.y ) ;
	}

	for( int i=0; i<3; i++ )
	{
		// P1 Gagebar
		g.DrawImage( artipects[i], 10, 40*i + 10 ) ;
		g.DrawImage( artipectBar[0], 50, 40*i + 10 ) ;
		artipectBar[1].SetClip( 0, 0, 
			( p1.art_beadPosition[i] > 0 ) ? ( ( p1.art_beadPosition[i] /10 ) * artipectBar[1].GetWidth() /10 ) 
			: 0 , artipectBar[1].GetHeight() ) ;
		g.DrawImage( artipectBar[1], 53, 40*i + 13 ) ;

		// P2 Gagebar
		g.DrawImage( artipects[i], 750, i*40 + 10 ) ;
		g.DrawImage( artipectBar[0], 450, i*40 + 10 ) ;
		artipectBar[1].SetClip( 0, 0, 
			( p2.art_beadPosition[i] > 0 ) ? ( ( p2.art_beadPosition[i] /10 ) * artipectBar[1].GetWidth() /10 ) 
			: 0 , artipectBar[1].GetHeight() ) ;
		g.DrawImage( artipectBar[1], 453, 40*i + 13 ) ;

	}

	g.DrawImage(mapState[map.mapState], 400 - mapState[map.mapState].GetWidth() / 2, 520);
	
	g.DrawImage(beadBar[0], 10, 530);
	g.DrawImage(beadBar[0], 450 + beadBar[0].GetWidth(), 530, -beadBar[0].GetWidth(), beadBar[0].GetHeight());
}

void GsGame::Dispose()
{
	p2Ai.Finalize();

	for(int i = 0; i < 2; i++)
		beadBar[i].Dispose();
	for(int i = 0; i < 2; i++)
		artipectBar[i].Dispose();
	for(int i = 0; i < 3; i++)
		artipects[i].Dispose();

	p2.ani.Dispose();
	p1.ani.Dispose();
	map.Dispose();
}

void GsGame::Player1State(DIRECTION dir, ACTION act)
{
	if(dir != p1.dir)
		p1.SetDirection(dir);
	p1.SetAction(act);
}

void GsGame::Player2State(DIRECTION dir, ACTION act)
{
	if(dir != p2.dir)
		p2.SetDirection(dir);
	p2.SetAction(act);
}

void GsGame::CharacterMoveCheck()
{
	if( p1.dir == DIR_RIGHT )
	{
		
	}
	else
	{

	}
	//캐릭터가 화면밖으로 나가지 않게 하기 위한 것
	p2.x = ( p2.x < 0 ) ? 0 : ( ( p2.x > SCREEN_WIDTH - p2.ani.GetWidth() ) ? 
		SCREEN_WIDTH - p2.ani.GetWidth() : p2.x ) ;
	if( ( ( p1.x + p1.ani.GetWidth() - limitTouch ) > p2.x ) && p1.dir == DIR_RIGHT )
	{
		if( p1.x > ( SCREEN_WIDTH - p2.ani.GetWidth() - p1.ani.GetWidth() + limitTouch ) )	
			p1.x = ( SCREEN_WIDTH - p2.ani.GetWidth() - p1.ani.GetWidth() + limitTouch ) ;
		p2.x = ( p1.x + p1.ani.GetWidth() - limitTouch ) ;
	}
	else if( ( p1.x + p1.ani.GetWidth() - limitTouch ) < p2.x && p1.dir == DIR_LEFT )
	{
		if( p1.x < 0 ) p1.x = 0 ;
		p2.x = ( p1.x + p1.ani.GetWidth() - limitTouch ) ;
	}
}