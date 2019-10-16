#pragma once

#include <windows.h>
#include "DaramLibrary.h"

namespace util
{
	class DECLSPEC DaramDelay sealed
	{
	private:
		unsigned int milisec;
		DWORD lastTickCount;

	public:
		DaramDelay(int milisec = 300);

		void SetCheckMilisec(int milisec);
		bool Checknow();

		void SetTickCount();
	};
};