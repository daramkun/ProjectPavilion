#include "GsMenu.h"
#include "Extern.h"
#include "Define.h"
#include "DaramConsole.h"
#include "Options.h"

#include <windows.h>
#include "resource.h"

using namespace util ;

BOOL CALLBACK DlgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

void GsMenu::Initial()
{
	ImageLoad() ;

	// 사운드 로드
	menuSelect.Initialize();
	menuSelect.Create("resource/Sound/MenuSelect.wav");
	menuChoose.Initialize();
	menuChoose.Create("resource/Sound/MenuChoose.wav");
	menuTitle.Initialize();
	menuTitle.CreateStream("resource/Music/Title.mp3");
	
	// 값 설정
	menuSelectCheck = false ;
	menuAlphaCheck = menuAlphaCheck = true ;

	// 페이드인 수행
	fadeIn = true;
	fadeOut = false;
	alpha = 255;

	// 배경음 재생(볼륨 30)
	menuTitle.Play();
	menuTitle.SetVolume(0.30f);
	DaramConsole::PrintLine("menu bgm");

	numberFont.ImageLoad(g, NULL);
	DaramConsole::PrintLine("numFont");

	opLinePosY = 240 ;
	opSelectState = 460 ;
	opMenu[0] = 5 ; opMenu[1] = 2 ; opMenu[2] = 5 ; opMenu[3] = 2 ; opMenu[4] = 0 ;

	createrCount = 0;

	opMenuSize[0] = 5 ; opMenuSize[1] = 2 ; opMenuSize[2] = 5 ; 
	opMenuSize[3] = 4 ; opMenuSize[4] = 6 ;

	opPlusCoor[0] = 60 ; opPlusCoor[1] = 140 ; opPlusCoor[2] = 60 ; 
	opPlusCoor[3] = 90 ; opPlusCoor[4] = 110 ;

	opComCoor[0] = 80 ; opComCoor[1] = 160 ; opComCoor[2] = 80 ; 
	opComCoor[3] = 80 ; opComCoor[4] = 60 ;

	nowKeyChange1p = true ;

	p1Cmd.up = KEY_Y ; p1Cmd.down = KEY_H ; 
	p1Cmd.right = KEY_J ; p1Cmd.left = KEY_G ; 
	p1Cmd.a = KEY_A ; p1Cmd.s = KEY_S ; p1Cmd.d = KEY_D ;

	p2Cmd.up = KEY_UP ; p2Cmd.down = KEY_DOWN ;
	p2Cmd.right = KEY_RIGHT ; p2Cmd.left = KEY_LEFT ;
	p2Cmd.a = KEY_COMMA ; p2Cmd.s = KEY_DOT ; p2Cmd.d = KEY_SLASH ;

	for(int i = 0; i < 7; i++)
		save1PKey[i][1] = NULL;
	save1PKey[0][0] = KeyToAscii( p1Cmd.a ) ;
	save1PKey[1][0] = KeyToAscii( p1Cmd.s ) ;
	save1PKey[2][0] = KeyToAscii( p1Cmd.d ) ;
	save1PKey[3][0] = KeyToAscii( p1Cmd.up ) ;
	save1PKey[4][0] = KeyToAscii( p1Cmd.down ) ;
	save1PKey[5][0] = KeyToAscii( p1Cmd.left ) ;
	save1PKey[6][0] = KeyToAscii( p1Cmd.right ) ;

}

void GsMenu::ImageLoad()
{
	// 구슬 이미지 로드
	bead.Create(g.GetDevice(), "resource/Menu/bead.dds");
	DaramConsole::PrintLine("bead");
	// 매인 메뉴 이미지 로드
	menuSelectImage[0].Create( g.GetDevice(), "resource/Menu/start.png" ) ;
	menuSelectImage[1].Create( g.GetDevice(), "resource/Menu/option.png" ) ;
	menuSelectImage[2].Create( g.GetDevice(), "resource/Menu/creators.png" ) ;
	menuSelectImage[3].Create( g.GetDevice(), "resource/Menu/exit.png" ) ;
	DaramConsole::PrintLine("mainmenu");

	// 서브 메뉴 이미지 로드
	subMenuSelectImage[0].Create( g.GetDevice(), "resource/Menu/start_com.png" ) ;
	subMenuSelectImage[1].Create( g.GetDevice(), "resource/Menu/start_player.png" ) ;
	subMenuSelectImage[2].Create( g.GetDevice(), "resource/Menu/start_np.png" ) ;
	DaramConsole::PrintLine("start submenu");

	// 옵션 이미지 로드
	optionImage[0].Create( g.GetDevice(), "resource/Menu/optionscreen.png" ) ;
	optionImage[1].Create( g.GetDevice(), "resource/Menu/ocursor.png" ) ;
	optionImage[2].Create( g.GetDevice(), "resource/Menu/downLine.png" ) ;
	DaramConsole::PrintLine("option submenu");

	// 크레딧 이미지 로드
	createrImage[0].Create(g.GetDevice(), "resource/Menu/credit1.png");
	createrImage[1].Create(g.GetDevice(), "resource/Menu/credit2.png");
	createrImage[2].Create(g.GetDevice(), "resource/Menu/credit3.png");
	DaramConsole::PrintLine("credit submenu");
}

void GsMenu::Update(double ElapsedTime)
{
	static DaramDelay fadeIODelay(1000 / 60);

	// 페이드인
	if(fadeIn)
	{
		if(fadeIODelay.Checknow())
		{
			alpha -= 15;
			if(alpha == 0)
			{
				alpha = 0;
				fadeIn = false;
			}
		}
	}
	//페이드아웃
	else if(fadeOut)
	{
		if(fadeIODelay.Checknow())
		{
			alpha += 15;
			if(alpha == 255)
			{
				fadeOut = false;
				
				switch(menuState)
				{
				case MS_START:
					g_Select.playMode = (PlayMode)subMenuState;
					if(g_Select.playMode == PM_NP)
					{
						g_Select.serverIp = NULL;
						int result = DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_NETWORK), 
							window.GetHandle(), DlgProc);
						switch(result)
						{
						case 0:
							fadeIn = true;
							return;
						case 1:
							g_Select.isServer = false;
							break;
						case 2:
							g_Select.isServer = true;
							break;
						}
					}
					window.SetState( GS_SELECT, &g, &loadingImage, true ) ;
					return;
				case MS_EXIT:
					PostQuitMessage(0);
					return;
				}
				//window.SetState( GS_MENU, &g, &loadingImage );
			}
		}
	}
	// 원래 메뉴 처리
	else
	{
		// 메뉴가 선택되지 않고 선택하는 화면인 경우
		if( !menuSelectCheck )
		{
			// 아래쪽 화살표 키를 눌렀을 때
			if( input.KeyDown( KEY_DOWN ) )
			{
				( menuState < 3 ) ? menuState  = 
					(MenuState)((int)menuState + 1) : menuState = MS_START;
				menuAlpha = 0 ;
				menuAlphaCheck = true ;
				fadeIODelay.SetTickCount();
				menuSelect.Play();
				menuSelect.Update();
			}
			// 위쪽 화살표 키를 눌렀을 때
			if( input.KeyDown( KEY_UP ) )
			{
				( menuState > 0 ) ? menuState  = 
					(MenuState)((int)menuState - 1) : menuState = MS_EXIT;
				menuAlpha = 0 ;
				menuAlphaCheck = true ;
				fadeIODelay.SetTickCount();
				menuSelect.Play();
				menuSelect.Update();
			}
			// 매인 메뉴 화면에서 ESC키를 눌렀을 때
			if(input.KeyDown(KEY_ESC))
			{
				menuState = MS_EXIT;
				menuAlpha = 0 ;
				menuAlphaCheck = true ;
				fadeIODelay.SetTickCount();
				menuSelect.Play();
				menuSelect.Update();
			}
			// 스페이스바 키를 누르거나 엔터 키를 눌렀을 때
			if( input.KeyDown( KEY_SPACE ) || input.KeyDown( KEY_ENTER ))
			{
				if(menuState == MS_EXIT)
				{
					fadeOut = true;
				}
				else
				{
					menuSelectCheck = true;
					menuAlphaCheck = true ;
					menuAlpha = 0 ;
				}
				menuChoose.Play();
				menuChoose.Update();

				//createrDelay.SetCheckMilisec(1500);
			}
		}
		else
		{
			switch( menuState )
			{
				case MS_START:
					{
						if( input.KeyDown( KEY_UP ) )
						{
							( subMenuState > 0 ) ? subMenuState  = 
								(SubMenuState)((int)subMenuState - 1) : subMenuState = SMS_START_NP;
							menuAlpha = 0 ;
							menuAlphaCheck = true ;
							fadeIODelay.SetTickCount();
							menuSelect.Play();
							menuSelect.Update();
						}

						if( input.KeyDown( KEY_DOWN ) )
						{
							( subMenuState < 2 ) ? subMenuState  = 
								(SubMenuState)((int)subMenuState + 1) : subMenuState = SMS_START_1P;
							menuAlpha = 0 ;
							menuAlphaCheck = true ;
							fadeIODelay.SetTickCount();
							menuSelect.Play();
							menuSelect.Update();
						}

						// 스페이스바 키를 누르거나 엔터 키를 눌렀을 때
						if( input.KeyDown( KEY_SPACE ) || input.KeyDown( KEY_ENTER ))
						{
							//g_Select.playMode = (PlayMode)subMenuState;
							//window.SetState( GS_SELECT, &g, &loadingImage, true ) ;

							fadeOut = true;
						}

						if( input.KeyDown( KEY_ESC ) || input.KeyDown( KEY_BACKSPACE )  )
						{
							if( menuSelectCheck )
								menuSelectCheck = false ;
							menuAlphaCheck = true ;
							menuAlpha = 0 ;
							menuChoose.Play();
							menuChoose.Update();
						}
					}
					break ;
				case MS_OPTION:
					{
						if( input.KeyDown( KEY_DOWN ) )
						{
							if( !opSelectCheck )
								opState = ( opState < 4 ) ? opState += 1 : 0 ;
							else
							{
								if( keyChangeCheck )
									break ;
								opMenu[opState] = ( opMenu[opState] < opMenuSize[opState] ) ? 
									opMenu[opState] += 1 : 0 ;

								if( opState == 4 && opMenu[opState] == 0 )
									nowKeyChange1p = ( nowKeyChange1p ) ? false : true ;

								opSelectState = 
									opMenu[opState]*opComCoor[opState] + opPlusCoor[opState] ;
							}
						}

						if( input.KeyDown( KEY_UP ) )
						{
							if( !opSelectCheck )
								opState = ( opState > 0 ) ? opState -= 1 : 4 ;
							else
							{
								if( keyChangeCheck )
									break ;
								opMenu[opState] = ( opMenu[opState] > 0 ) ? 
									opMenu[opState] -= 1 : opMenuSize[opState] ;

								if( opState == 4 &&  opMenu[opState] == opMenuSize[opState] )
									nowKeyChange1p = ( nowKeyChange1p ) ? false : true ;

								opSelectState = 
									opMenu[opState]*opComCoor[opState] + opPlusCoor[opState] ;
							}
						}

						if( input.KeyDown( KEY_ENTER ) || input.KeyDown( KEY_SPACE ) )
						{
							if( !opSelectCheck )
							{
								opSelectCheck = true ;
								nowKeyChange1p = true ;
								opSelectState = 
									opMenu[opState]*opComCoor[opState] + opPlusCoor[opState] ;
							}
							else
							{
								if( opState == 4 )
								{
									keyChangeCheck = true ;
								}
							}
						}

						if( keyChangeCheck )
						{
							BYTE *getKeys = input.GetPressedKey();

							for( int i=0; i<255; i++ )
							{
								if(i == 28) continue;
								if(getKeys[i] & 0x80)
								{
									if( nowKeyChange1p )
										save1PKey[opMenu[opState]][0] = KeyToAscii((InputKeys)i);
									else
										save2PKey[opMenu[opState]][0] = KeyToAscii((InputKeys)i);
									keyChangeCheck = false;
									break;
								}
							}
						}

						if( input.KeyDown( KEY_ESC ) || input.KeyDown( KEY_BACKSPACE )  )
						{
							if( opSelectCheck )
							{
								if( keyChangeCheck )
								{
									keyChangeCheck = false ;
									break ;
								}
								opSelectCheck = false ;
								break ;
							}
							if( menuSelectCheck )
								menuSelectCheck = false ;
							menuAlphaCheck = true ;
							menuAlpha = 0 ;
							menuChoose.Play();
							menuChoose.Update();
						}

						opLinePosY = 240 + opState*57 ;

					}
					break;
				case MS_CREATER:
					{
						if( menuAlphaCheck )
						{
							if( !createrFadein )
								menuAlphaCheck = ( menuAlpha + 5 >= 160 ) ? 
									false : ((menuAlpha += 5) ? true : true) ;
							else
								menuAlphaCheck = ( menuAlpha - 5 <= 0 ) ? 
									false : ((menuAlpha -= 5 ) ? true : true ) ;
							if( menuAlphaCheck == false )
							{
								if ( createrDelay.Checknow() )
								{
									menuAlphaCheck = true ;
									createrFadein = ( createrFadein == true ) ? false : true ;
									if( !createrDirectionCheck  && createrFadein == false )
										createrCount = ( createrCount < 2 ) ? 
											createrCount += 1 : createrCount = 0 ;
									else if( createrDirectionCheck && createrFadein == false )
										createrCount = ( createrCount > 0 ) ?
											createrCount -= 1 : createrCount = 2 ;
								}
							}
						}

						if( input.KeyDown( KEY_ESC ) || input.KeyDown( KEY_BACKSPACE )  )
						{
							if( menuSelectCheck )
								menuSelectCheck = false ;
							menuAlphaCheck = true ;
							menuAlpha = 0 ;
							menuChoose.Play();
							menuChoose.Update();
							createrCount = 0;
						}
					}
					break;
			} 

		}

		if(fadeIODelay.Checknow() && menuState != MS_CREATER || menuSelectCheck == false )
			menuAlphaCheck = ( menuAlpha + 15 >= 255 ) ? false : ((menuAlpha += 15) ? true : true) ;	
	}

	menuTitle.Update();
}

void GsMenu::Draw()
{
	int a = (int)menuState ;

	g.Clear(CLR_BLACK);
	g.SetColor( GetRGB( 255, 255, 255 ) ) ;
	if( !menuSelectCheck )
	{
		prevMenuState = ( menuState > 0 ) ? (int)menuState-1 : 3 ;
		nextMenuState = ( menuState < 3 ) ? (int)menuState+1 : 0 ;

		g.DrawImage(bead, SCREEN_WIDTH/2 - bead.GetWidth() / 2, SCREEN_HEIGHT/2 - bead.GetHeight() / 2);
		
		g.SetColor( GetARGB( menuAlpha, 255, 255, 255 ) ) ;
		g.DrawImage( menuSelectImage[a], 
			SCREEN_WIDTH / 2 - menuSelectImage[a].GetWidth() / 2,
			SCREEN_HEIGHT / 2 - menuSelectImage[a].GetHeight() / 2 ) ;

		g.SetColor( GetARGB( ((menuAlpha - 120 >= 0) ? menuAlpha - 120 : 0), 255, 255, 255 ) ) ;
		g.DrawImage( menuSelectImage[prevMenuState], 
			SCREEN_WIDTH / 2 - menuSelectImage[a].GetWidth() / 2,
			SCREEN_HEIGHT / 2 - menuSelectImage[a].GetHeight() / 2 - 150) ;
		g.DrawImage( menuSelectImage[nextMenuState], 
			SCREEN_WIDTH / 2 - menuSelectImage[a].GetWidth() / 2,
			SCREEN_HEIGHT / 2 - menuSelectImage[a].GetHeight() / 2 + 150 ) ;
	}
	else
	{
		switch( menuState )
		{
		case MS_START:
			{
				int a = (int)subMenuState ;
				prevMenuState = ( subMenuState > 0 ) ? (int)subMenuState-1 : 2 ;
				nextMenuState = ( subMenuState < 2 ) ? (int)subMenuState+1 : 0 ;

				g.DrawImage(bead, SCREEN_WIDTH/2 - bead.GetWidth() / 2, SCREEN_HEIGHT/2 - bead.GetHeight() / 2);

				g.SetColor( GetARGB( menuAlpha, 255, 255, 255 ) ) ;
				g.DrawImage( subMenuSelectImage[a], 
					SCREEN_WIDTH / 2 - subMenuSelectImage[a].GetWidth() / 2,
					SCREEN_HEIGHT / 2 - subMenuSelectImage[a].GetHeight() / 2 ) ;

				g.SetColor( GetARGB( ((menuAlpha - 120 >= 0) ? menuAlpha - 120 : 0), 255, 255, 255 ) ) ;
				g.DrawImage( subMenuSelectImage[prevMenuState], 
					SCREEN_WIDTH / 2 - subMenuSelectImage[a].GetWidth() / 2,
					SCREEN_HEIGHT / 2 - subMenuSelectImage[a].GetHeight() / 2 - 150) ;
				g.DrawImage( subMenuSelectImage[nextMenuState], 
					SCREEN_WIDTH / 2 - subMenuSelectImage[a].GetWidth() / 2,
					SCREEN_HEIGHT / 2 - subMenuSelectImage[a].GetHeight() / 2 + 150 ) ;
			}
			break;
		case MS_OPTION :
			{
				g.DrawImage( optionImage[0], 0, 0 ) ;
				g.DrawImage( optionImage[2], 45, opLinePosY ) ;

				switch( opState )
				{
					case 0 :
						for( int i=50; i<=100; i+=10 ) 
							numberFont.Draw( g, i, true, 450, 
								(i/10-5)*opComCoor[opState] + opPlusCoor[opState] ) ;
						break ;
					case 1 :
						for( int i=30; i<=60; i+=15 )
							numberFont.Draw( g, i, false, 450, 
								(i/15-2)*opComCoor[opState] + opPlusCoor[opState] ) ;
						break ;
					case 2 :
						for( int i=0; i<=5; i++ ) 
							numberFont.Draw( g, i, false, 450, 
								i*opComCoor[opState] + opPlusCoor[opState] ) ;
						break ;
					case 3 :
						for( int i=1; i<=5; i++ ) 
							numberFont.Draw( g, i, false, 450, 
								(i-1)*opComCoor[opState] + opPlusCoor[opState] ) ;
						break ;
					case 4 :
						char asdf[2] = {(p1Cmd.a + 35), NULL};
						numberFont.Draw( g, "attack1  ", 380, 110 ) ;
						numberFont.Draw( g, "attack2  ", 380, 170 ) ;
						numberFont.Draw( g, "attack3  ", 380, 230 ) ;
						numberFont.Draw( g, "UP  " , 380, 290 ) ;
						numberFont.Draw( g, "DOWN  " , 380, 350 ) ;
						numberFont.Draw( g, "LEFT  " , 380, 410 ) ;
						numberFont.Draw( g, "RIGHT  " , 380, 470 ) ;
						if( nowKeyChange1p )
						{
							numberFont.Draw( g, "1P KEY" , 380, 30 ) ;
							for( int i=0; i<7; i++ )
							{
								numberFont.Draw( g, save1PKey[i], 730, i*60 + 110 ) ;
							}
						}
						else
						{
							numberFont.Draw( g, "2P KEY" , 380, 30 ) ;
							for( int i=0; i<7; i++ )
							{
								numberFont.Draw( g, save2PKey[i], 730, i*60 + 110 ) ;
							}
						}
						break ;
				}
				if( opSelectCheck )
				{
					int a ;
					a = ( opState < 4 ) ? 420 : 350 ;
					g.DrawImage( optionImage[1], a, opSelectState ) ;
				}
			}
			break ;
		case MS_CREATER :
			{
				g.SetColor(D3DCOLOR_XRGB(255, 255, 255));
				g.DrawImage(createrImage[createrCount], 0, 0);
				
				g.SetColor(D3DCOLOR_ARGB(menuAlpha, 255, 255, 255));
				g.DrawImage(fade, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
			}
			break ;
		case MS_EXIT :
			{

			}
			break ;
		}
	}

	if(fadeIn || fadeOut)
	{
		g.SetColor(GetARGB(alpha, 255, 255, 255));
		g.DrawImage(fade, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	}
}

void GsMenu::Dispose()
{
	p1Cmd.a = AsciiToKey(save1PKey[0][0]) ;
	p1Cmd.s = AsciiToKey(save1PKey[1][0]) ;
	p1Cmd.d = AsciiToKey(save1PKey[2][0]) ;
	p1Cmd.up = AsciiToKey(save1PKey[3][0]) ;
	p1Cmd.down = AsciiToKey(save1PKey[4][0]) ;
	p1Cmd.left = AsciiToKey(save1PKey[5][0]) ;
	p1Cmd.right = AsciiToKey(save1PKey[6][0]) ;

	numberFont.Dispose();

	menuTitle.Stop();
	menuTitle.Dispose();
	menuSelect.Dispose();
	menuChoose.Dispose();

	for( int i=0; i<4; i++ )
		menuSelectImage[i].Dispose() ;
	for( int i=0; i<3; i++ )
	{
		subMenuSelectImage[i].Dispose() ;		
		optionImage[i].Dispose() ;
		createrImage[i].Dispose() ;
	}

	bead.Dispose();
}

BOOL CALLBACK DlgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg)
	{
	case WM_INITDIALOG:
		return true;
	case WM_COMMAND:
		switch(wParam)
		{
		case IDOK:
			g_Select.serverIp = new char[30];
			GetDlgItemText(hWnd, IDC_IPADR, g_Select.serverIp, 30);
			DaramConsole::PrintLine(g_Select.serverIp);
			EndDialog(hWnd, 1);
			break;
		case IDCANCEL:
			EndDialog(hWnd, 0);
			break;
		case IDSERVER:
			EndDialog(hWnd, 2);
			break;
		}
		break;
	}

	return false;
}