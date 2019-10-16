#pragma once

#include <DaramGraphics.h>
#include <DaramImage.h>
#include <DaramConsole.h>
using namespace util;

/*--------------------------------------------------
 * Image Font Class for Pavilion Project
 * Made by Jin Jae-yeon
 * 0 ~ 9 : Number Font, 10 : Percent Font,
 * 11 ~ 37 : Alphabet Font
 * Font folder : resource/Font
 * Worked date : 2009/01/20
 -------------------------------------------------*/

int KeyToAscii(InputKeys key);
InputKeys AsciiToKey(char wd);

class ImageFont
{
private:
	DaramImage image[37];
public:
	void ImageLoad(DaramGraphics g, D3DCOLOR color);
	void Draw(DaramGraphics &g, int drawing, bool drawPercent, int x, int y, int height = NULL);
	void Draw(DaramGraphics &g, const char *drawing, int x, int y, int height = NULL);
	void Dispose();
};
