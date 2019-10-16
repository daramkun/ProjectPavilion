#define DLLEXPORT
#include "DaramLibrary.h"

///////////////////////////////////////////////////////////////////
#include <atlcore.h> // unicode W2A, A2W macro

// ATL::_AtlGetConversionACP() to CP_ACP
#undef USES_CONVERSION
#ifndef _DEBUG
#define USES_CONVERSION int _convert; (_convert); UINT _acp = CP_ACP; (_acp); LPCWSTR _lpw; (_lpw); LPCSTR _lpa; (_lpa)
#else
#define USES_CONVERSION int _convert = 0; (_convert); UINT _acp = CP_ACP; (_acp); LPCWSTR _lpw = NULL; (_lpw); LPCSTR _lpa = NULL; (_lpa)
#endif

// utf8 convertion macro
#ifndef _DEBUG
#define USES_UTF8_CONVERSION int _convert; (_convert); UINT _acp = CP_UTF8; (_acp); LPCWSTR _lpw; (_lpw); LPCSTR _lpa; (_lpa)
#else
#define USES_UTF8_CONVERSION int _convert = 0; (_convert); UINT _acp = CP_UTF8; (_acp); LPCWSTR _lpw = NULL; (_lpw); LPCSTR _lpa = NULL; (_lpa)
#endif

#undef A2W
#define A2W(lpa) (\
	((_lpa = lpa) == NULL) ? NULL : (\
	_convert = (lstrlenA(_lpa)+1),\
	ATLA2WHELPER((LPWSTR) alloca(_convert*2), _lpa, _convert, _acp)))


#undef W2A      // utf8 을 처리하기위해, (lstrlenW(_lpw)+1)*2 -> (lstrlenW(_lpw)+1)*3 으로 변경
#define W2A(lpw) (\
	((_lpw = lpw) == NULL) ? NULL : (\
	_convert = (lstrlenW(_lpw)+1)*3,\
	ATLW2AHELPER((LPSTR) alloca(_convert), _lpw, _convert, _acp)))
///////////////////////////////////////////////////////////////////

char VersionCheck(int version)
{
	if(version == 0x024)
		return 0;
	else if(version < 0x024)
		return 1;
	else
	{
		if(version < 0x2001)
			return 1;
		else
			return -1;
	}
}

D3DCOLOR GetRGB(int r, int g, int b)
{
	return D3DCOLOR_XRGB(r, g, b);
}

D3DCOLOR GetARGB(int a, int r, int g, int b)
{
	return D3DCOLOR_ARGB(a, r, g, b);
}

bool IsCrashed(RECT rect1, RECT rect2)
{
	if((rect1.top <= rect2.top + rect2.bottom && rect2.top <= rect1.top + rect1.bottom) 
		&&
		(rect1.left <= rect2.left + rect2.right && rect2.left <= rect1.left + rect1.right))
		return true;
	else
		return false;
}

bool IsCrashedRect(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2)
{
	/*
	RECT rect1; SetRect(&rect1, x1, y1, w1, h1);
	RECT rect2; SetRect(&rect2, x2, y2, w2, h2);
	return IsCrashed(rect1, rect2);
	*/
	
	if((x1 <= x2 + w2 && x2 <= x1 + w1) 
		&&
		(y1 <= y2 + h2 && y2 <= y1 + h1))
		return true;
	else
		return false;
}

wchar_t* AnsiToUni(char* text)
{
	USES_CONVERSION;
	return A2W(text);
}

char* UniToAnsi(wchar_t* text)
{
	USES_CONVERSION;
	return W2A(text);
}