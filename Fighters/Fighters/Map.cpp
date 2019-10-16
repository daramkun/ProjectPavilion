#include "Map.h"
#include "Extern.h"

void Map::Load(LPCSTR mapData)
{
	bg.Create(g.GetDevice(), mapData);
	printx = 0;
	printy = 600 - bg.GetHeight();
}

void Map::Draw(DaramGraphics &g)
{
	g.DrawImage(bg, printx, printy);
}

void Map::SetX(int x)
{
	printx += x;
}

void Map::SetY(int y)
{
	printy += y;
}

int Map::GetX()
{
	return printx;
}

int Map::GetY()
{
	return printy;
}

void Map::Dispose()
{
	bg.Dispose();
}