#ifndef _LOGWJ_H_
#define _LOGWJ_H_
#include<windows.h>
#include<stdio.h>

#ifdef UNICODE
#define FUNCTION __FUNCTIONW__
#else
#define FUNCTION __FUNCTION__
#endif


#define TRACE_printf(CHARPTR, ...)  {_TRACE_W(_T("%s::%d    "), FUNCTION, __LINE__);\
	_TRACE_W(CHARPTR, __VA_ARGS__); _TRACE_W(_T("\n"));}

void _TRACE_W(TCHAR* szpFormatName,...);

#endif
