#pragma once

#include <DaramImage.h>

class Map
{
public:
	DaramImage bg;
	int printx, printy;

	int mapState;
public:
	void Load(LPCSTR mapData);
	void Draw(DaramGraphics &g);
	
	void SetX(int x);
	void SetY(int y);
	int GetX();
	int GetY();

	void Dispose();
};
