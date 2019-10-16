#include "ImageFont.h"

void ImageFont::ImageLoad(DaramGraphics g, D3DCOLOR color)
{
	for(int i = 0; i < 10; i++)
	{
		char filename[30] = "";
		wsprintf(filename, "resource/Font/o%d.png", i);
		image[i].Create(g.GetDevice(), filename);
	}

	image[10].Create(g.GetDevice(), "resource/Font/percent.png");
	

	for(int i = 'A'; i <= 'Z'; i++)
	{
		char filename[30] = "";
		wsprintf(filename, "resource/Font/%c.png", i);
		image[10 + i-'A'+1].Create(g.GetDevice(), filename);
		DaramConsole::PrintLine(filename);
	}
}

void ImageFont::Draw(DaramGraphics &g, int drawing, bool drawPercent, int x, int y, int height)
{
	char temp[20] = "";
	wsprintf(temp, "%d", drawing);

	int count = x;

	for(int i = 0; i < strlen(temp); i++)
	{
		int index = 0;

		if(temp[i] >= 48 && temp[i] <= 57)
			index = temp[i] - 48;

		if(height == NULL)
		{
			height = image[index].GetWidth();
		}

		g.DrawImage(image[index], count, y, height, height);
		count += height;
	}

	if(drawPercent)
	{
		if(height == NULL)
			height = image[10].GetWidth();
		g.DrawImage(image[10], count, y, height, height);
	}
}

void ImageFont::Draw(DaramGraphics &g, const char *drawing, int x, int y, int height)
{
	int count = x;
	int length = strlen(drawing);

	for(int i = 0; i < length; i++)
	{
		int index = 0;

		// drawing[i]값이 숫자라면(0 ~ 9 - 10개)
		if(drawing[i] >= 48 && drawing[i] <= 57)
			index = drawing[i] - 48;
		// drawing[i]값이 대문자라면(A ~ Z - 26개)
		else if(drawing[i] >= 65 && drawing[i] <= 90)
			index = drawing[i] - 54;
		// drawing[i]값이 소문자라면(a ~ z - 26개)
		else if(drawing[i] >= 91 && drawing[i] <= 122)
			index = drawing[i] - 54 - 32;
		// drawing[i]값이 %라면
		else if(drawing[i] == 37)
			index = 10;
		else
		{
			count += 10;
			continue;
		}

		if(height == NULL)
		{
			height = image[index].GetWidth();
		}

		g.DrawImage(image[index], count, y, height, height);
		count += height;
	}
}

void ImageFont::Dispose()
{
	for(int i = 0; i < 11; i++)
	{
		image[i].Dispose();
	}
}

int KeyToAscii(InputKeys key)
{
	switch(key)
	{
	case KEY_A:
		return 'A';
	case KEY_B:
		return 'B';
	case KEY_C:
		return 'C';
	case KEY_D:
		return 'D';
	case KEY_E:
		return 'E';
	case KEY_F:
		return 'F';
	case KEY_G:
		return 'G';
	case KEY_H:
		return 'H';
	case KEY_I:
		return 'I';
	case KEY_J:
		return 'J';
	case KEY_K:
		return 'K';
	case KEY_L:
		return 'L';
	case KEY_M:
		return 'M';
	case KEY_N:
		return 'N';
	case KEY_O:
		return 'O';
	case KEY_P:
		return 'P';
	case KEY_Q:
		return 'Q';
	case KEY_R:
		return 'R';
	case KEY_S:
		return 'S';
	case KEY_T:
		return 'T';
	case KEY_U:
		return 'U';
	case KEY_V:
		return 'V';
	case KEY_W:
		return 'W';
	case KEY_X:
		return 'X';
	case KEY_Y:
		return 'Y';
	case KEY_Z:
		return 'Z';
	default:
		return 0;
	}
}

InputKeys AsciiToKey(char wd)
{
	switch(wd)
	{
	case 'A':
		return KEY_A;
	case 'B':
		return KEY_B;
	case 'C':
		return KEY_C;
	case 'D':
		return KEY_D;
	case 'E':
		return KEY_E;
	case 'F':
		return KEY_F;
	case 'G':
		return KEY_G;
	case 'H':
		return KEY_H;
	case 'I':
		return KEY_I;
	case 'J':
		return KEY_J;
	case 'K':
		return KEY_K;
	case 'L':
		return KEY_L;
	case 'M':
		return KEY_M;
	case 'N':
		return KEY_N;
	case 'O':
		return KEY_O;
	case 'P':
		return KEY_P;
	case 'Q':
		return KEY_Q;
	case 'R':
		return KEY_R;
	case 'S':
		return KEY_S;
	case 'T':
		return KEY_T;
	case 'U':
		return KEY_U;
	case 'V':
		return KEY_V;
	case 'W':
		return KEY_W;
	case 'X':
		return KEY_X;
	case 'Y':
		return KEY_Y;
	case 'Z':
		return KEY_Z;
	default:
		return (InputKeys)NULL;
	}
}