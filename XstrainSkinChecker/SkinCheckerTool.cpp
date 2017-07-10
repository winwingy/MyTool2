#include "StdAfx.h"
#include "SkinCheckerTool.h"


typedef std::function<void (LPCSTR lpFileOrPath, void* pUserData)> EnumerateFunc;


bool operator < (const FILETIME &left, const FILETIME& right)
{
	if (left.dwHighDateTime != right.dwHighDateTime)
		return left.dwHighDateTime < right.dwHighDateTime;


	if (left.dwLowDateTime != right.dwLowDateTime)
		return left.dwLowDateTime < right.dwLowDateTime;

	return false;
}

bool operator == (const FILETIME &left, const FILETIME& right)
{
	if (left.dwHighDateTime == right.dwHighDateTime
		&& left.dwHighDateTime == right.dwHighDateTime)
	{
		return true;
	}
	return false;
}

bool operator > (const FILETIME &left, const FILETIME& right)
{
	if (left.dwHighDateTime != right.dwHighDateTime)
		return left.dwHighDateTime > right.dwHighDateTime;


	if (left.dwLowDateTime != right.dwLowDateTime)
		return left.dwLowDateTime > right.dwLowDateTime;

	return false;
}

tstring adJustFindFormat(const tstring& lpPath)
{
	tstring path = lpPath;
	if(path[lpPath.length() - 1] != '//')
		path += _T("//");

	path += _T("*");
	return path;
}


void doFileEnumeration(const tstring& lpPath, BOOL bRecursion,
	BOOL bEnumFiles, FILETIME* lastTime)
{
	int len = lpPath.length();
	if(lpPath.empty()|| len<=0)
		return;

	tstring path = adJustFindFormat(lpPath);
	WIN32_FIND_DATAW fd;
	HANDLE hFindFile = FindFirstFile(path.c_str(), &fd);
	if(hFindFile == INVALID_HANDLE_VALUE)
	{
		::FindClose(hFindFile); 
		return;
	}

	BOOL bFinish = FALSE;
	while(!bFinish)
	{
		tstring tempPath = lpPath;
		if(lpPath[len-1] != '//') 
			tempPath += L"//";

		tempPath += fd.cFileName;
		BOOL bIsDirectory = ((fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0);
		if(bIsDirectory && bRecursion) //是子目录
		{
			if (tstring(fd.cFileName).compare(_T(".")) == 0 || 
				tstring(fd.cFileName).compare(_T("..")) == 0)
			{

			}
			else
			{
				doFileEnumeration(tempPath, bRecursion, bEnumFiles, lastTime);
			}
		}
		else
		{
			if (*lastTime < fd.ftLastWriteTime)
				*lastTime = fd.ftLastWriteTime;
		}
		bFinish = (FindNextFile(hFindFile, &fd) == FALSE);
	}

	::FindClose(hFindFile);
}

SkinCheckerTool::SkinCheckerTool(void)
{
}


SkinCheckerTool::~SkinCheckerTool(void)
{
}

bool SkinCheckerTool::GetFolderLastModifyTime(const tstring& dir, 
	bool bRecursion, FILETIME* lastModifyTime)
{
	doFileEnumeration(dir, TRUE, TRUE, lastModifyTime);
	return true;
}

bool SkinCheckerTool::GetFileLastModifyTime(const tstring& file,
	FILETIME* lastModifyTime)
{
	WIN32_FIND_DATAW fd;
	HANDLE hFindFile = FindFirstFile(file.c_str(), &fd);
	if(hFindFile == INVALID_HANDLE_VALUE)
	{
		::FindClose(hFindFile); 
		return false;
	}
	*lastModifyTime = fd.ftLastWriteTime;
	return true;
}


bool SkinCheckerTool::modifyFileTime(const tstring& filePath)
{
	HANDLE hOpenFile = (HANDLE)CreateFile(filePath.c_str(), 
		GENERIC_READ|GENERIC_WRITE, 0, NULL, OPEN_EXISTING, NULL, NULL);

	const int BUF_SIZE = 10;
	HANDLE hMapFile = CreateFileMapping(  
		hOpenFile,    // 物理文件句柄  
		NULL,                    // 默认安全级别  
		PAGE_READWRITE,          // 可读可写  
		0,                       // 高位文件大小  
		BUF_SIZE,                // 地位文件大小  
		nullptr                   // 共享内存名称  
		);  


	char *pBuf = (char *)MapViewOfFile(  
		hMapFile,            // 共享内存的句柄  
		FILE_MAP_ALL_ACCESS, // 可读写许可  
		0,  
		0,  
		BUF_SIZE  
		);  

	char temp = *pBuf;
	*pBuf = 0;
	FlushViewOfFile(pBuf, BUF_SIZE);
	//*pBuf = temp;
	FlushViewOfFile(pBuf, BUF_SIZE);
	UnmapViewOfFile(pBuf);
	CloseHandle(hMapFile);
	CloseHandle(hOpenFile);
	return true;
}

bool SkinCheckerTool::modifyFileTimeC(const tstring& filePath)
{
	FILE* fp = nullptr;
	_tfopen_s(&fp, filePath.c_str(), _T("rb+"));
	fseek(fp, 1, SEEK_END);
	char lastC;
	fread(&lastC, 1, 1, fp);
	fseek(fp, 1, SEEK_END);
	fwrite(&lastC, 1, 1, fp);
	fclose(fp);
	return true;
}

bool SkinCheckerTool::modifyFileTimeByTimeApi(const tstring& filePath)
{
	HANDLE hOpenFile = INVALID_HANDLE_VALUE;
	BOOL ret = FALSE;
	do 
	{
		hOpenFile = (HANDLE)CreateFile(filePath.c_str(), 
			GENERIC_READ|GENERIC_WRITE, 0, NULL, OPEN_EXISTING, NULL, NULL);
		if (!hOpenFile)
			break;

		FILETIME lastWriteTime;
		ret = ::GetFileTime(hOpenFile, nullptr, nullptr, &lastWriteTime);
		if (!ret)
			break;

		lastWriteTime.dwHighDateTime += 1;
		lastWriteTime.dwLowDateTime += 600 * 10 * 1000;
		ret = SetFileTime(hOpenFile, nullptr, nullptr, &lastWriteTime);
		if (!ret)
			break;
	} while (0);
	if (hOpenFile != INVALID_HANDLE_VALUE)
		CloseHandle(hOpenFile);

	return !!ret;
}



