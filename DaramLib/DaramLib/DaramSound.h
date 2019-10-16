#pragma once

#include "fmod.hpp"
#include "fmod_errors.h"

#include "DaramLibrary.h"

#pragma comment(lib, "fmodex_vc.lib")

class DECLSPEC DaramSound
{
private:
	FMOD::System *system;
	FMOD::Sound *sound;
	FMOD::Channel *channel;

public:
	DaramSound();
	~DaramSound(void);

	bool Initialize();
	void Create(const char *file);
	void Create(wchar_t *file);
	void Create(void *data, int size);
	void CreateStream(const char *file);
	void CreateStream(wchar_t *file);
	void CreateStream(void *data, int size);

	void Play();
	void Pause();
	void Stop();

	void Close();
	void Dispose();

	void Update();

	int GetPosition();
	void SetPosition(int);

	float GetVolume();
	void SetVolume(float);

	bool IsPlaying();

	int Duration();
};