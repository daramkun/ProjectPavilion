#define DLLEXPORT
#include "DaramSound.h"

DaramSound::DaramSound()
{
	system = NULL;
	sound = NULL;
	channel = NULL;
}

DaramSound::~DaramSound(void)
{
	Dispose();
}

bool DaramSound::Initialize()
{
	FMOD_RESULT result;
	result = FMOD::System_Create(&system);
	if(result != FMOD_OK) return false;

	result = system->init(32, FMOD_INIT_NORMAL, 0);
	if(result != FMOD_OK) return false;

	return true;
}

void DaramSound::Create(const char *file)
{
	FMOD_RESULT result;
	result = system->createSound(file, FMOD_HARDWARE, 0, &sound);

	if(result != FMOD_OK)
	{
		MessageBox(NULL, "사운드 생성 오류", "사운드 오류", NULL);
		PostQuitMessage(0);
	}
}

void DaramSound::Create(wchar_t *file)
{
	FMOD_RESULT result;
	char *filename = UniToAnsi(file);
	result = system->createSound(filename, FMOD_HARDWARE, 0, &sound);

	if(result != FMOD_OK)
	{
		MessageBox(NULL, "사운드 생성 오류", "사운드 오류", NULL);
		PostQuitMessage(0);
	}
}

void DaramSound::Create(void *data, int size)
{
	FMOD_RESULT result;

	result = system->createSound((const char*)data, FMOD_HARDWARE, 0, &sound);

	if(result != FMOD_OK)
	{
		MessageBox(NULL, "사운드 생성 오류", "사운드 오류", NULL);
		PostQuitMessage(0);
	}
}

void DaramSound::CreateStream(wchar_t *file)
{
	FMOD_RESULT result;
	char *filename = UniToAnsi(file);
	result = system->createStream(filename, FMOD_HARDWARE, 0, &sound);

	if(result != FMOD_OK)
	{
		MessageBox(NULL, "사운드 스트림 생성 오류", "사운드 오류", NULL);
		PostQuitMessage(0);
	}
}

void DaramSound::CreateStream(const char *file)
{
	FMOD_RESULT result;
	result = system->createStream(file, FMOD_HARDWARE, 0, &sound);

	if(result != FMOD_OK)
	{
		MessageBox(NULL, "사운드 스트림 생성 오류", "사운드 오류", NULL);
		PostQuitMessage(0);
	}
}

void DaramSound::CreateStream(void *data, int size)
{
	FMOD_RESULT result;

	result = system->createStream((const char*)data, FMOD_HARDWARE, 0, &sound);

	if(result != FMOD_OK)
	{
		MessageBox(NULL, "사운드 스트림 생성 오류", "사운드 오류", NULL);
		PostQuitMessage(0);
	}
}

void DaramSound::Play()
{
	if(channel != NULL)
	{
		bool ip = false;
		channel->getPaused(&ip);

		if(ip)
		{
			channel->setPaused(false);
			return;
		}
	}

	system->playSound(FMOD_CHANNEL_FREE, sound, false, &channel);
}

void DaramSound::Pause()
{
	channel->setPaused(true);
}

void DaramSound::Stop()
{
	channel->stop();
}

void DaramSound::Close()
{
	if(system != NULL) { system->close(); system->release(); system = NULL; }
}

void DaramSound::Update()
{
	system->update();
}

int DaramSound::GetPosition()
{
	unsigned int ms = 0;
	channel->getPosition(&ms, FMOD_TIMEUNIT_MS);

	return ms;
}

void DaramSound::SetPosition(int position)
{
	channel->setPosition(position, FMOD_TIMEUNIT_MS);
}

float DaramSound::GetVolume()
{
	float v = 0.0f;
	channel->getVolume(&v);
	return v;
}

void DaramSound::SetVolume(float volume)
{
	channel->setVolume(volume);
}

bool DaramSound::IsPlaying()
{
	bool ip = false;
	channel->isPlaying(&ip);

	return ip;
}

int DaramSound::Duration()
{
	unsigned int dr = 0;
	sound->getLength(&dr, FMOD_TIMEUNIT_MS);
	return dr;
}

void DaramSound::Dispose()
{
	if(sound != NULL) { sound->release(); sound = NULL; }
	if(system != NULL) { system->release(); system = NULL; }
	channel = NULL;
}