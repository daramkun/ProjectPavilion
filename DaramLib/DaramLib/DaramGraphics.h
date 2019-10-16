#pragma once

#include <d3d9.h>
#include <d3dx9.h>

#include "DaramImage.h"
#include "DaramLibrary.h"

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

class DECLSPEC DaramGraphics
{
private:
	IDirect3D9 *d3d;
	IDirect3DDevice9 *device;
	ID3DXSprite *sprite;
	ID3DXFont *font;

	D3DXFONT_DESC fdesc;
	D3DPRESENT_PARAMETERS pp;

	HWND winHandle;

	D3DCOLOR color;

public:
	void Initialize(HWND hWnd);
	void Create(HWND = NULL, bool = true, int = NULL, int = NULL, D3DFORMAT = D3DFMT_X8R8G8B8, D3DMULTISAMPLE_TYPE = D3DMULTISAMPLE_NONE, bool warning = true);

	bool CheckMultiSample(D3DMULTISAMPLE_TYPE multiSample, bool isWindow = true, D3DFORMAT fmt = D3DFMT_UNKNOWN);
	
	void Clear(D3DCOLOR color);
	
	void Begin();
	void End();

	void DrawImage(DaramImage &image, int X, int Y);
	void DrawImage(DaramImage &image, int X, int Y, int Width, int Height);
	void DrawImage(DaramImage &image, int X, int Y, float angle, int rttCenterX, int rttCenterY);
	void DrawImage(DaramImage &image, int X, int Y, float angle, int rttCenterX, int rttCenterY, int Width, int Height);
	void DrawAnsiText(int X, int Y, const char *format, ...);
	void DrawUniText(int X, int Y, const wchar_t *format, ...);

	void SetColor(D3DCOLOR color);
	D3DCOLOR GetColor();

	IDirect3DDevice9* GetDevice();
	ID3DXSprite* GetSprite();

	void ChangeFontName(LPCSTR name);
	void ChangeFontSize(int size);
	void ChangeFontWeight(UINT weight);
	void ChangeFontItalic(bool isItalic);
	void ChangeFontQuality(BYTE ql);
	void SetFontDesc();

	void Present(int X = NULL, int Y = NULL, int Width = NULL, int Height = NULL);

	int GetBackBufferWidth();
	int GetBackBufferHeight();

	void Dispose();
};