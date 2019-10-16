#define DLLEXPORT
#include "DaramConsole.h"

#include <stdio.h>
#include <stdarg.h>
#include <conio.h>

namespace util
{
	void DaramConsole::Initialize()
	{
		AllocConsole();
		SetConsoleTitle("Debug Console System For Game about Daram Library");

		PrintLine("D-Console System For Game about Daram Library");
		PrintLine("D-Console System Version 0.0.1");
		PrintLine("\t\t\tMade by Jin Jae-yeon");
		PrintLine("---------------------------------------------");
	}

	void DaramConsole::Finalize()
	{
		PrintLine("---------------------------------------------");
		PrintLine("D-Console System Disposed...");
		FreeConsole();
	}

	void DaramConsole::Print(const char *format, ...)
	{
		va_list data;
		char *text = new char[1024];

		va_start(data, format);
		vsprintf_s(text, 1024, format, data);
		va_end(data);

		DWORD dwResult;
		WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), text, strlen(text), &dwResult, NULL);
		delete [] text;
	}

	void DaramConsole::PrintLine(const char *format, ...)
	{
		va_list data;
		char *text = new char[1024];

		va_start(data, format);
		vsprintf_s(text, 1024, format, data);
		va_end(data);

		DWORD dwResult;
		WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), text, strlen(text), &dwResult, NULL);
		WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), "\n", strlen("\n"), &dwResult, NULL);
		delete [] text;
	}
};