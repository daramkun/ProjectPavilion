#pragma once

#include <Windows.h>
#include "DaramLibrary.h"

namespace util
{
	class DECLSPEC DaramConsole sealed
	{
	public:
		static void Initialize();
		static void Finalize();

		static void Print(const char *text, ...);
		static void PrintLine(const char *text, ...);
	};
};