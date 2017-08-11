#pragma once
#include <string>
#include <vector>
#include <Windows.h>
#include <tchar.h>
#include <QDebug>
#include <QLabel>
#include "qboxlayout"
#include <QPainter>
#include "./tool/logWj.h"


#ifndef tString
#ifdef UNICODE
typedef std::wstring tString;
#else
typedef std::string tString;
#endif
#endif