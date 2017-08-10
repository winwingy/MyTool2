#include "StdAfx.h"
#include "StringWy.h"


StringWy::StringWy(void)
{
}


StringWy::~StringWy(void)
{
}


tString StringWy::IntToString(int val)
{
	TCHAR szBuf[30] = {0};
	_itot(val, szBuf, 10);
	return szBuf;
}

int StringWy::StringToInt(const tString& str)
{
	return _ttoi(str.c_str());
}