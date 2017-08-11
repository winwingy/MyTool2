#include "StdAfx.h"
#include "logWj.h"
void _TRACE_W(TCHAR* szpFormatName,...){
#ifdef _DEBUG
	va_list argList;
	TCHAR buffer[1024];
	va_start(argList, szpFormatName);
	_vstprintf_s(buffer, szpFormatName, argList);
	OutputDebugStringW(buffer);
	va_end(argList);
#endif
}