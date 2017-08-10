#pragma once
#include <string>
#include <vector>
#include <Windows.h>
#include <tchar.h>
#include <QDebug>


#ifndef tString
#ifdef UNICODE
typedef std::wstring tString;
#else
typedef std::string tString;
#endif
#endif