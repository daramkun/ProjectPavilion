#define DLLEXPORT

#include "DaramGraphics.h"

#include <stdio.h>
#include <stdarg.h>

void DaramGraphics::Initialize(HWND hWnd)
{
	winHandle = hWnd;
}

void DaramGraphics::Create(HWND hWnd, bool isWindow, int ScreenWidth, int ScreenHeight, D3DFORMAT backbufFormat, D3DMULTISAMPLE_TYPE multiSample, bool warning)
{
	INT hwvertex = 0;

	if(hWnd != NULL)
		winHandle = hWnd;
	else if(hWnd == NULL && winHandle == NULL)
		return;

	d3d = Direct3DCreate9(D3D_SDK_VERSION);

	color = D3DCOLOR_XRGB(0, 0, 0);

	D3DCAPS9 caps;
	d3d->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &caps);

	if(caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
		hwvertex = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	else
	{
		hwvertex = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
		if(warning)
			MessageBox(NULL, "이 컴퓨터에서는 게임이 느려질 수 있습니다.\n\n하드웨어 정점 프로세싱을 사용할 수 없습니다.", "경고", NULL);

	}

	ZeroMemory(&pp, sizeof(pp));
	if(isWindow)
	{
		pp.BackBufferFormat = D3DFMT_UNKNOWN;
		pp.BackBufferWidth = ScreenWidth;
		pp.BackBufferHeight = ScreenHeight;
		pp.SwapEffect = D3DSWAPEFFECT_DISCARD;
		pp.MultiSampleType = multiSample;
		pp.Windowed = true;
	}
	else
	{
		pp.BackBufferCount = 1;
		pp.BackBufferFormat = backbufFormat;
		pp.BackBufferWidth = ScreenWidth;
		pp.BackBufferHeight = ScreenHeight;
		pp.Flags = NULL;
		pp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
		pp.hDeviceWindow = winHandle;
		pp.MultiSampleQuality = NULL;
		pp.MultiSampleType = multiSample;
		pp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
		pp.SwapEffect = D3DSWAPEFFECT_DISCARD;
		pp.Windowed = false;
	}

	if(device != NULL)
	{
		device->Release();
		device = NULL;
	}

	if(FAILED(d3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL,
		winHandle, hwvertex, &pp, &device))) 
	{
		if(FAILED(d3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF,
		winHandle, hwvertex, &pp, &device)))
		{
			MessageBox(NULL, "장치 초기화 오류", "그래픽스 장치 오류", NULL);
			PostQuitMessage(0);
		}
		else
		{
			if(warning)
				MessageBox(NULL, "이 컴퓨터에서는 게임이 느려질 수 있습니다.\n\n하드웨어 가속을 사용할 수 없습니다.", "경고", NULL);
		}
	}
	
	if(FAILED(D3DXCreateSprite(device, &sprite)))
	{
		MessageBox(NULL, "스프라이트 생성 오류", "그래픽스 오류", NULL);
		PostQuitMessage(0);
	}

	ZeroMemory(&fdesc, sizeof(fdesc));

	fdesc.CharSet = DEFAULT_CHARSET;
	ChangeFontName("Consolas");
	ChangeFontSize(22);
	SetFontDesc();
}

bool DaramGraphics::CheckMultiSample(D3DMULTISAMPLE_TYPE multiSample, bool isWindow, D3DFORMAT fmt)
{
	D3DFORMAT format = (isWindow) ? D3DFMT_UNKNOWN : fmt;
	if(SUCCEEDED(d3d->CheckDeviceMultiSampleType(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, format, isWindow, multiSample, NULL)))
		return true;
	else
		return false;
}

void DaramGraphics::Clear(D3DCOLOR color)
{
	device->Clear(0, NULL, D3DCLEAR_TARGET,
		color, 1.0f, 0);
}

void DaramGraphics::Begin()
{
	device->BeginScene();
	sprite->Begin(D3DXSPRITE_ALPHABLEND);
}

void DaramGraphics::End()
{
	sprite->End();
	device->EndScene();
}

void DaramGraphics::DrawImage(DaramImage &image, int X, int Y)
{
	D3DXVECTOR3 pos((float)X, (float)Y, 1.0f);
	sprite->Draw(image.GetTexture(device), &image.clip, NULL, &pos, color);
}

void DaramGraphics::DrawImage(DaramImage &image, int X, int Y, int Width, int Height)
{
	D3DXVECTOR2 pos((float)X, (float)Y);//, 1.0f);
	D3DXVECTOR2 size(((float)Width / (float)image.GetWidth()), ((float)Height / (float)image.GetHeight()));
	D3DXVECTOR2 scen(0, 0);
	D3DXMATRIX mat;
	D3DXMATRIX old;

	sprite->GetTransform(&old);
	D3DXMatrixTransformation2D(&mat, &scen, 0.0f, &size, NULL, 0.0f, &pos);
	sprite->SetTransform(&mat);
	
	sprite->Draw(image.GetTexture(device), &image.clip, NULL, NULL, color);
	sprite->SetTransform(&old);
}

void DaramGraphics::DrawImage(DaramImage &image, int X, int Y, float angle, int rttCenterX, int rttCenterY)
{
	D3DXVECTOR2 pos((float)X, (float)Y);
	D3DXVECTOR2 rttCenter((float)rttCenterX, (float)rttCenterY);
	D3DXMATRIX mat;
	D3DXMATRIX old;

	sprite->GetTransform(&old);
	D3DXMatrixTransformation2D(&mat, NULL, 0.0f, NULL, &rttCenter, angle, &pos);
	sprite->SetTransform(&mat);

	sprite->Draw(image.GetTexture(device), &image.clip, NULL, NULL, color);
	sprite->SetTransform(&old);	
}

void DaramGraphics::DrawImage(DaramImage &image, int X, int Y, float angle, int rttCenterX, int rttCenterY, int Width, int Height)
{
	D3DXVECTOR2 pos((float)X, (float)Y);
	D3DXVECTOR2 size(((float)Width / (float)image.GetWidth()), ((float)Height / (float)image.GetHeight()));
	D3DXVECTOR2 rttCenter((float)rttCenterX, (float)rttCenterY);
	D3DXMATRIX mat;
	D3DXMATRIX old;

	sprite->GetTransform(&old);
	D3DXMatrixTransformation2D(&mat, NULL, 0.0f, &size, &rttCenter, angle, &pos);
	sprite->SetTransform(&mat);

	sprite->Draw(image.GetTexture(device), &image.clip, NULL, NULL, color);
	sprite->SetTransform(&old);	
}

void DaramGraphics::DrawAnsiText(int X, int Y, const char *format, ...)
{
	va_list data;
	char *text = new char[1024];

	va_start(data, format);
	wvsprintf(text, format, data);
	va_end(data);

	RECT rect = {X, Y, fdesc.Width * strlen(text) * 2, fdesc.Height};
	font->DrawTextA(sprite, text, (int)strlen(text), &rect, DT_NOCLIP, color);
	delete [] text;
}

void DaramGraphics::DrawUniText(int X, int Y, const wchar_t *format, ...)
{
	va_list data;
	wchar_t *text = new wchar_t[1024];

	va_start(data, format);
	wvsprintfW(text, format, data);
	va_end(data);

	RECT rect = {X, Y, fdesc.Width * wcslen(text) * 2, fdesc.Height};
	font->DrawTextW(sprite, text, (int)wcslen(text), &rect, DT_NOCLIP, color);
	delete [] text;
}

void DaramGraphics::Present(int X, int Y, int Width, int Height)
{
	RECT rect = {0, };
	bool rectUse = true;

	if(X != NULL && Y != NULL && Width != NULL && Height != NULL)
		SetRect(&rect, X, Y, Width, Height);
	else
		rectUse = false;

	device->Present(NULL, (rectUse) ? &rect : NULL, NULL, NULL);
}

void DaramGraphics::SetColor(D3DCOLOR color)
{
	this->color = color;
}

D3DCOLOR DaramGraphics::GetColor()
{
	return color;
}

IDirect3DDevice9* DaramGraphics::GetDevice()
{
	return device;
}

ID3DXSprite* DaramGraphics::GetSprite()
{
	return sprite;
}

void DaramGraphics::ChangeFontName(LPCSTR name)
{
	ZeroMemory(&fdesc.FaceName, LF_FACESIZE);
	memcpy(fdesc.FaceName, name, strlen(name) * sizeof(char));
}

void DaramGraphics::ChangeFontSize(int size)
{
	fdesc.Height = size;
}

void DaramGraphics::ChangeFontWeight(UINT weight)
{
	fdesc.Weight = weight;
}

void DaramGraphics::ChangeFontItalic(bool isItalic)
{
	fdesc.Italic = isItalic;
}

void DaramGraphics::ChangeFontQuality(BYTE ql)
{
	fdesc.Quality = ql;
}

void DaramGraphics::SetFontDesc()
{
	if(font != NULL)
		font->Release();

	if(FAILED(D3DXCreateFontIndirect(device, &fdesc, &font)))
	{
		MessageBox(NULL, "폰트 생성 오류", "그래픽스 오류", NULL);
		PostQuitMessage(0);
	}
}

void DaramGraphics::Dispose()
{
	if(font != NULL)
		font->Release();

	if(sprite != NULL)
		sprite->Release();
	if(device != NULL)
		device->Release();

	if(d3d != NULL)
		d3d->Release();
}

int DaramGraphics::GetBackBufferWidth()
{
	return pp.BackBufferWidth;
}

int DaramGraphics::GetBackBufferHeight()
{
	return pp.BackBufferHeight;
}