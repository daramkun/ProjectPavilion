#define DLLEXPORT

#include "DaramImage.h"

DaramImage::DaramImage(void)
{
	texture = NULL;
	device = NULL;
	file = NULL;
	data = NULL;
	size = 0;
	width = NULL;
	height = NULL;
}

DaramImage::~DaramImage(void)
{
	if(texture != NULL)
		texture->Release();
}

void DaramImage::Create(IDirect3DDevice9 *device, LPCSTR file, D3DCOLOR abColor)
{
	D3DXIMAGE_INFO info;
	ZeroMemory(&info, sizeof(info));

	Dispose();

	D3DXGetImageInfoFromFile(file, &info);

	imageType = 0;
	this->file = file;
	this->device = device;
	color = abColor;
	this->width = info.Width;
	this->height = info.Height;
	
	InitClip();

	D3DXCreateTextureFromFileEx(device, file, info.Width, info.Height, 
		1, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT,
		abColor, &info, NULL, &texture);
	imageType = 1;
}

void DaramImage::Create(IDirect3DDevice9 *device, void *data, int size, D3DCOLOR abColor)
{
	D3DXIMAGE_INFO info;
	ZeroMemory(&info, sizeof(info));

	Dispose();

	D3DXGetImageInfoFromFileInMemory(data, size, &info);

	imageType = 0;
	this->data = data;
	this->size = size;
	this->device = device;
	color = abColor;
	this->width = info.Width;
	this->height = info.Height;
	
	InitClip();

	D3DXCreateTextureFromFileInMemoryEx(device, data, size, info.Width, info.Height, 
		1, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, 
		abColor, &info, NULL, &texture);
}

void DaramImage::Create(IDirect3DDevice9 *device, D3DCOLOR color, int width, int height)
{
	Dispose();

	this->device = device;
	imageType = 2;
	this->color = color;
	this->width = width;
	this->height = height;

	D3DXCreateTexture(device, width, height, 1, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, &texture);

	D3DLOCKED_RECT rc;
	RECT rect;
	D3DCOLOR *rcData;

	rect.top = rect.left = 0;
	rect.right = width;
	rect.bottom = height;
	
	InitClip();

	texture->LockRect(0, &rc, &rect, D3DLOCK_DISCARD);

	rcData = (DWORD*)rc.pBits;
	for(int i = 0; i < height; i++)
		for(int j = 0; j < width; j++)
			rcData[i + j * height] = color;
	
	texture->UnlockRect(0);
}

IDirect3DTexture9* DaramImage::GetTexture(IDirect3DDevice9 *device)
{
	if(device == NULL && this->device == NULL) return NULL;

	if(this->device != device)
	{
		if(imageType == 0)
		{
			Create(device, data, size, color);
		}
		else if(imageType == 1)
		{
			Create(device, file, color);
		}
		else
		{
			Create(device, color, width, height);
		}
	}

	return texture;
}

void DaramImage::Dispose()
{
	if(texture != NULL)
		texture->Release();

	texture = NULL;
	file = NULL;
	data = NULL;
	imageType = 0;
}

int DaramImage::GetWidth()
{
	D3DXIMAGE_INFO info;
	GetImageInformation(info);
	return info.Width;
}

int DaramImage::GetHeight()
{
	D3DXIMAGE_INFO info;
	GetImageInformation(info);
	return info.Height;
}

void DaramImage::GetImageInformation(D3DXIMAGE_INFO &info)
{
	info.Width = width;
	info.Height = height;
}

void DaramImage::SetClip(int x, int y, int w, int h)
{
	clip.left = x;
	clip.top = y;
	clip.right = w;
	clip.bottom = h;
}

void DaramImage::InitClip()
{
	ZeroMemory(&clip, sizeof(clip));
	clip.top = 0;
	clip.left = 0;
	clip.right = width;
	clip.bottom = height;
}