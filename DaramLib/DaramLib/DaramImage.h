#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include "DaramLibrary.h"

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

class DECLSPEC DaramImage
{
	friend class DaramGraphics;
private:
	IDirect3DDevice9 *device;
	IDirect3DTexture9 *texture;

	int imageType;

	const char *file;
	void *data;
	int size;
	D3DCOLOR color;

	int width, height;

	RECT clip;

public:
	DaramImage(void);
	~DaramImage(void);

	// 이미지 텍스쳐를 파일로부터 가져옵니다.
	void Create(IDirect3DDevice9 *device, const char *file, DWORD abColor = NULL);
	// 이미지 텍스쳐를 버퍼로부터 가져옵니다.
	void Create(IDirect3DDevice9 *device, void *data, int size, DWORD abColor = NULL);
	// 단색 텍스쳐를 만듭니다.
	void Create(IDirect3DDevice9 *device, D3DCOLOR color, int width, int height);

	// 텍스쳐를 가져옵니다.
	IDirect3DTexture9* GetTexture(IDirect3DDevice9 *device = NULL);

	// 텍스쳐 소멸
	void Dispose();

	// 그림 가로 크기를 가져옵니다.
	int GetWidth();
	// 그림 세로 크기를 가져옵니다.
	int GetHeight();
	// 이미지 정보를 가져옵니다.
	void GetImageInformation(D3DXIMAGE_INFO &info);

	void SetClip(int x, int y, int w, int h);
	void InitClip();
};
