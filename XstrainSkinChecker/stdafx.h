// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
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

// TODO: �ڴ˴����ó�����Ҫ������ͷ�ļ�
