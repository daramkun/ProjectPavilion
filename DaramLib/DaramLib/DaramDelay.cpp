#define DLLEXPORT
#include "DaramDelay.h"

namespace util
{
	DaramDelay::DaramDelay(int milisec)
	{
		this->milisec = milisec;
		lastTickCount = GetTickCount();
	}

	void DaramDelay::SetCheckMilisec(int milisec)
	{
		this->milisec = milisec;
		lastTickCount = GetTickCount();
	}

	bool DaramDelay::Checknow()
	{
		if(GetTickCount() - lastTickCount >= milisec)
		{
			lastTickCount = GetTickCount();
			return true;
		}
		else
		{
			return false;
		}
	}

	void DaramDelay::SetTickCount()
	{
		lastTickCount = GetTickCount();
	}
};