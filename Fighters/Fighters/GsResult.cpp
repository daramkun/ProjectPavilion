#include "GsResult.h"
#include "Extern.h"

void GsResult::Initial()
{
	End[0].Create( g.GetDevice(), "resource\End\1pwin.png" ) ;
	End[1].Create( g.GetDevice(), "resource\End\2pwin.png" ) ;

}

void GsResult::Update(double ElapsedTime)
{

}

void GsResult::Draw()
{
	g.Clear(D3DCOLOR_XRGB(0, 0, 0));
	g.SetColor( D3DCOLOR_XRGB( 255, 255, 255 ) ) ;
	g.ChangeFontSize( 100 );
	g.SetFontDesc();
	if( Check1pWin )
		g.DrawAnsiText( 0, 0, "1PWIN" ) ;
	else
		g.DrawAnsiText( 0, 0, "2PWIN" ) ;
}

void GsResult::Dispose()
{

}