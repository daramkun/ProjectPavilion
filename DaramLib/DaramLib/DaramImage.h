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

	// �̹��� �ؽ��ĸ� ���Ϸκ��� �����ɴϴ�.
	void Create(IDirect3DDevice9 *device, const char *file, DWORD abColor = NULL);
	// �̹��� �ؽ��ĸ� ���۷κ��� �����ɴϴ�.
	void Create(IDirect3DDevice9 *device, void *data, int size, DWORD abColor = NULL);
	// �ܻ� �ؽ��ĸ� ����ϴ�.
	void Create(IDirect3DDevice9 *device, D3DCOLOR color, int width, int height);

	// �ؽ��ĸ� �����ɴϴ�.
	IDirect3DTexture9* GetTexture(IDirect3DDevice9 *device = NULL);

	// �ؽ��� �Ҹ�
	void Dispose();

	// �׸� ���� ũ�⸦ �����ɴϴ�.
	int GetWidth();
	// �׸� ���� ũ�⸦ �����ɴϴ�.
	int GetHeight();
	// �̹��� ������ �����ɴϴ�.
	void GetImageInformation(D3DXIMAGE_INFO &info);

	void SetClip(int x, int y, int w, int h);
	void InitClip();
};
