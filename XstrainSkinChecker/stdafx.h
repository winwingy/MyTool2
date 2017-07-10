// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include <iostream>

#include <atlbase.h>
#include <atlstr.h>
#include <Shlwapi.h>
#include <windows.h>
#include <functional>


#ifdef _UNICODE
#   define std_out std::wcout
typedef std::wostream tos;
typedef std::wstring tstring;
#else
#   define std_out std::cout
typedef std::ostream tos;
typedef std::string tstring;
#endif

// TODO: 在此处引用程序需要的其他头文件
