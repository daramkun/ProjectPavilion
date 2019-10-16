#include "Animation.h"
#include <iostream>
#include <fstream>
using namespace std;
#include "DaramConsole.h"
#include "DaramLibrary.h"
using namespace util;

bool CrashObjects(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2)
{
	if(IsCrashedRect(x1, y1, w1, h1, x2, y2, w2, h2))
		return true;
	else
		return false;
}

Animation::Animation(void)
{
	modes = NULL;
	objs = NULL;
	isPlaying = false;
	playingFrameMode = -1;
}

Animation::~Animation(void)
{
	Dispose();
}

bool Animation::Load(LPCSTR file, DaramGraphics &g)
{
	ifstream is;
	is.open(file, ifstream::binary);
	if(is.fail()) { MessageBox(NULL, "애니메이션 파일 로드 실패", "오류", NULL); PostQuitMessage(0); return false; }

	char buffer = NULL;
	is.read(&buffer, 1);
	/****************///util::DaramConsole::PrintLine("애니메이션 %s 파일 형식 정보 1번 확인 - %c", file, buffer);
	if(buffer != 'A') return false;
	is.read(&buffer, 1);
	/****************///util::DaramConsole::PrintLine("애니메이션 %s 파일 형식 정보 2번 확인 - %c", file, buffer);
	if(buffer != 'N') return false;
	is.read(&buffer, 1);
	/****************///util::DaramConsole::PrintLine("애니메이션 %s 파일 버전 정보 확인 - %d", file, (int)buffer);

	is.read((char*)&speed, 4);
	delay.SetCheckMilisec(speed);
	/****************///util::DaramConsole::PrintLine("스피드 - %d", speed);

	modelength = NULL;
	is.read((char*)&modelength, 4);
	/****************/util::DaramConsole::PrintLine("프레임모드 갯수 - %d", modelength);
	modes = new AnimationFrameMode[modelength];
	for(int i = 0; i < modelength; i++)
	{
		char namelength = NULL;
		is.read(&namelength, 1);
		if(namelength != 0)
		{
			modes[i].name = new char[namelength + 1];
			is.read(modes[i].name, namelength);
			modes[i].name[namelength] = NULL;
			/****************/util::DaramConsole::PrintLine("프레임모드 이름 - %s", modes[i].name);
		}

		is.read((char*)&modes[i].screen_width, 4);
		/****************/util::DaramConsole::PrintLine("프레임모드 화면 가로 - %d", modes[i].screen_width);
		is.read((char*)&modes[i].screen_height, 4);
		/****************/util::DaramConsole::PrintLine("프레임모드 화면 세로 - %d", modes[i].screen_height);

		modes[i].frmlength = NULL;
		is.read((char*)&modes[i].frmlength, 4);
		/****************/util::DaramConsole::PrintLine("프레임 갯수 - %d", modes[i].frmlength);
		modes[i].frms = new AnimationFrame[modes[i].frmlength];
		for(int j = 0; j < modes[i].frmlength; j++)
		{
			is.read((char*)&modes[i].frms[j].anchor_x, 4);
			/****************/util::DaramConsole::PrintLine("앵커 X화면 - %d", modes[i].frms[j].anchor_x);
			is.read((char*)&modes[i].frms[j].anchor_y, 4);
			/****************/util::DaramConsole::PrintLine("앵커 X화면 - %d", modes[i].frms[j].anchor_y);

			modes[i].frms[j].objlength = NULL;
			is.read((char*)&modes[i].frms[j].objlength, 4);
			/****************/util::DaramConsole::PrintLine("사용 객체 갯수 - %d", modes[i].frms[j].objlength);

			modes[i].frms[j].objs = new AnimationUsingObject[modes[i].frms[j].objlength];
			for(int k = 0; k < modes[i].frms[j].objlength; k++)
			{
				is.read((char*)&modes[i].frms[j].objs[k].index, 4);
				/****************/util::DaramConsole::PrintLine("사용 객체 인덱스 - %d", modes[i].frms[j].objs[k].index);
				is.read((char*)&modes[i].frms[j].objs[k].x, 4);
				/****************/util::DaramConsole::PrintLine("사용 객체 X - %d", modes[i].frms[j].objs[k].x);
				is.read((char*)&modes[i].frms[j].objs[k].y, 4);
				/****************/util::DaramConsole::PrintLine("사용 객체 Y - %d", modes[i].frms[j].objs[k].y);
				is.read((char*)&modes[i].frms[j].objs[k].width, 4);
				/****************/util::DaramConsole::PrintLine("사용 객체 가로 - %d", modes[i].frms[j].objs[k].width);
				is.read((char*)&modes[i].frms[j].objs[k].height, 4);
				/****************/util::DaramConsole::PrintLine("사용 객체 세로 - %d", modes[i].frms[j].objs[k].height);
			}
		}
	}

	objlength = NULL;
	is.read((char*)&objlength, 4);
	/****************/util::DaramConsole::PrintLine("객체 갯수 - %d", objlength);
	objs = new AnimationObject[objlength];
	for(int i = 0; i < objlength; i++)
	{
		int namelength = NULL;
		is.read((char*)&namelength, 1);
		if(namelength != 0)
		{
			objs[i].name = new char[namelength + 1];
			is.read(objs[i].name, namelength);
			objs[i].name[namelength] = NULL;
			/****************/util::DaramConsole::PrintLine("객체 이름 - %s", objs[i].name);
		}
		else
		{
			objs[i].name = NULL;
		}

		int pathlength = NULL;
		is.read((char*)&pathlength, 1);
		if(pathlength != 0)
		{
			objs[i].path = new char[pathlength + 1];
			is.read(objs[i].path, pathlength);
			objs[i].path[pathlength] = NULL;
			/****************/util::DaramConsole::PrintLine("객체 경로 - %s", objs[i].path);
		}
		else
		{
			objs[i].path = NULL;
		}

		int type = NULL;
		is.read((char*)&type, 1);
		objs[i].type = (ObjType)type;
		/****************/util::DaramConsole::PrintLine("객체 타입 - %d", (int)objs[i].type);
		is.read((char*)&objs[i].tc_a, 1);
		/****************/util::DaramConsole::PrintLine("객체 투명색 알파 - %d", (int)objs[i].tc_a);
		is.read((char*)&objs[i].tc_r, 1);
		/****************/util::DaramConsole::PrintLine("객체 투명색 R - %d", (int)objs[i].tc_r);
		is.read((char*)&objs[i].tc_g, 1);
		/****************/util::DaramConsole::PrintLine("객체 투명색 G - %d", (int)objs[i].tc_g);
		is.read((char*)&objs[i].tc_b, 1);
		/****************/util::DaramConsole::PrintLine("객체 투명색 B - %d", (int)objs[i].tc_b);

		objs[i].datalength = NULL;
		is.read((char*)&objs[i].datalength, 4);
		/****************/util::DaramConsole::PrintLine("객체 데이터 길이 - %d", objs[i].datalength);
		if(objs[i].datalength != 0)
		{
			objs[i].data = new unsigned char[objs[i].datalength];
			is.read((char*)objs[i].data, objs[i].datalength);
		}
		else
		{
			objs[i].data = NULL;
		}

		switch(objs[i].type)
		{
		case OT_IMAGE:
			objs[i].image.Create(g.GetDevice(), objs[i].data, objs[i].datalength, 
				D3DCOLOR_ARGB(objs[i].tc_a, objs[i].tc_r, objs[i].tc_g, objs[i].tc_b));
			/****************/util::DaramConsole::PrintLine("객체 이미지 생성");
			break;
		case OT_SOUND:
			objs[i].sound.Initialize();
			objs[i].sound.CreateStream(objs[i].data, objs[i].datalength);
			/****************/util::DaramConsole::PrintLine("객체 사운드 생성");
			break;
		}
	}

	is.close();

	return true;
}

void Animation::Play(LPCSTR fmName)
{
	for(int i = 0; i < modelength; i++)
	{
		if(strcmp(fmName, modes[i].name) == 0)
		{
			playingFrameMode = i;
			playFrame = 0;
			isPlaying = true;
			return;
		}
		else
		{
			playingFrameMode = -1;
			playFrame = 0;
			isPlaying = true;
		}
	}
}

void Animation::Play(int fmIndex)
{
	playingFrameMode = fmIndex;
	isPlaying = true;
	delay.SetTickCount();
}

void Animation::Play()
{
	isPlaying = true;
	delay.SetTickCount();
}

void Animation::Stop()
{
	isPlaying = false;
	playFrame = 0;
}

void Animation::Pause()
{
	isPlaying = false;
}

void Animation::AnimationDraw(DaramGraphics &g, int x, int y, int width, int height)
{
	if(!isPlaying) return;
	if(playingFrameMode == -1) return;
	if(playFrame == -1) return;

	if(width == NULL)
		width = modes[playingFrameMode].screen_width;
	if(height == NULL)
		height = modes[playingFrameMode].screen_height;

	double bw = (double)width / (double)modes[playingFrameMode].screen_width;
	double bh = (double)height / (double)modes[playingFrameMode].screen_height;
	
	for(int i = 0; i < modes[playingFrameMode].frms[playFrame].objlength; i++)
	{
		DaramImage *image;
		switch(objs[modes[playingFrameMode].frms[playFrame].objs[i].index].type)
		{
		case (int)OT_IMAGE:
			image = &(objs[modes[playingFrameMode].frms[playFrame].objs[i].index].image);
			g.DrawImage(*image,
				x + modes[playingFrameMode].frms[playFrame].objs[i].x,
				y + modes[playingFrameMode].frms[playFrame].objs[i].y,
				image->GetWidth() * bw,
				image->GetHeight() * bh);
			break;
		case (int)OT_SOUND:
			objs[modes[playingFrameMode].frms[playFrame].objs[i].index].sound.Play();
			break;
		}
	}
}

void Animation::AnimationUpdate()
{
	if(!isPlaying) return;
	if(delay.Checknow())
	{
		playFrame++;
		if(playFrame >= modes[playingFrameMode].frmlength)
			playFrame = 0;
	}
}

int Animation::GetAnimationAnchorX()
{
	if(!isPlaying) return NULL;
	if(playingFrameMode == -1) return NULL;
	if(playFrame == -1) return NULL;
	return modes[playingFrameMode].frms[playFrame].anchor_x;
}

int Animation::GetAnimationAnchorY()
{
	if(!isPlaying) return NULL;
	if(playingFrameMode == -1) return NULL;
	if(playFrame == -1) return NULL;
	return modes[playingFrameMode].frms[playFrame].anchor_y;
}

bool Animation::Crash(Animation &ani, CrashInformation *info, int x, int y, int x2, int y2)
{
	if(playingFrameMode == -1) return false;
	if(ani.playingFrameMode == -1) return false;

	for(int i = 0; i < modes[playingFrameMode].frms[playFrame].objlength; i++)
	{
		for(int j = 0; j < ani.modes[ani.playingFrameMode].frms[ani.playFrame].objlength; j++)
		{
			AnimationUsingObject myObj = modes[playingFrameMode].frms[playFrame].objs[i];
			AnimationUsingObject enObj = ani.modes[ani.playingFrameMode].frms[ani.playFrame].objs[j];
			
			if(objs[myObj.index].type == OT_DAMAGEPOINT) 
			{
				if(ani.objs[enObj.index].type == OT_ASSULTPOINT)
				{
					if(CrashObjects(myObj.x + x, myObj.y + y, myObj.width, myObj.height, 
						enObj.x + x2, enObj.y + y2, enObj.width, enObj.height))
					{
						info->EnAssultPointNumber = j - 1;
						info->MyDamagePointNumber = i - 1;
						if(info->assultHasMe == CRP_ME)
							info->assultHasMe = CRP_BOTH;
						else if(info->assultHasMe == CRP_NONE)
							info->assultHasMe = CRP_ENERMY;
					}
				}
			}
		}
	}

	if(info->assultHasMe == CRP_NONE)
		return false;
	else
		return true;
}

int Animation::GetFrameModeIndex()
{
	return playingFrameMode;
}

int Animation::GetFrameIndex()
{
	return playFrame;
}

void Animation::Dispose()
{
	if(objs != NULL)
	{
		for(int i = 0; i < objlength; i++)
		{
			if(objs[i].name != NULL)
				delete [] objs[i].name;
			if(objs[i].data != NULL)
				delete [] objs[i].path;
			if(objs[i].data != NULL)
				delete [] objs[i].data;
			objs[i].image.Dispose();
			objs[i].sound.Dispose();
		}

		delete [] objs;
		objs = NULL;
	}
	/****************/util::DaramConsole::PrintLine("애니메이션 제거");

	if(modes != NULL)
	{
		for(int i = 0; i < modelength; i++)
		{
			for(int j = 0; j < modes[i].frmlength; j++)
			{
				if(modes[i].frms[j].objs != NULL)
					delete [] modes[i].frms[j].objs;
			}
			if(modes[i].frms != NULL)
				delete [] modes[i].frms;
			if(modes[i].name != NULL)
				delete [] modes[i].name;
		}

		if(modes != NULL)
			delete [] modes;
		modes = NULL;
	}
	/****************/util::DaramConsole::PrintLine("객체 제거");
}

int Animation::GetWidth()
{
	return modes[playingFrameMode].screen_width ;
}