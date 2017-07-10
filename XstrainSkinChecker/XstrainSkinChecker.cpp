// XstrainSkinChecker.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "SkinCheckerTool.h"

int _tmain(int argc, _TCHAR* argv[])
{
	std::wcout.imbue(std::locale("chs"));
	tstring strSkinFolder; 
	tstring strPackageFile; 
	tstring strCmd; 
	bool checkLastModifiedTime = false;
	// 分析命令行参数
	for (int i = 1; i < argc; )
	{
		if (i < argc - 1 && _tcsicmp(argv[i], _T("-Dir")) == 0)
		{
			strSkinFolder = argv[++i];
		}
		else if (i <= argc - 1 && _tcsicmp(argv[i], _T("-IsCheck")) == 0)
		{
			checkLastModifiedTime = true;
		}
		else if (i <= argc - 1 && _tcsicmp(argv[i], _T("-Skin")) == 0)
		{
			strPackageFile = argv[++i];
		}
		else if (i <= argc - 1 && _tcsicmp(argv[i], _T("-Cmd")) == 0)
		{
			strCmd = argv[++i];
		}		
		else
		{
			std_out << "format error" << std::endl;
			return 1;
		}
		++i;
	}

	if (strSkinFolder.empty())
	{
		std_out << _T("strSkinFolder.IsEmpty()") << std::endl;
		return -1;
	}

	// 检查参数
	if (strSkinFolder.length() > 0 && 
		(!::PathFileExists(strSkinFolder.c_str()) || 
		!::PathIsDirectory(strSkinFolder.c_str())))
	{
		std_out << _T("Skin Folder not exists or is file.") << std::endl;
		return 2;
	}

	if (checkLastModifiedTime && PathFileExists(strPackageFile.c_str()))
	{
		FILETIME skinFolderLastModified = {0};
		SkinCheckerTool::GetFolderLastModifyTime(strSkinFolder.c_str(), true,
			&skinFolderLastModified);

		FILETIME packageFileInfo = {0};
		SkinCheckerTool::GetFileLastModifyTime(strPackageFile.c_str(),
			&packageFileInfo);
		if (packageFileInfo > skinFolderLastModified)
		{
			std_out << _T(" The pack is already up-to-date~~~") << std::endl;
			return 0;
		}
	}

	if (strCmd.empty())
	{
		std_out << _T(" strCmd empty. ") << std::endl;
		return -3;
	}

	USES_CONVERSION;	
	system(W2A(strCmd.c_str()));
	//bool ret = SkinCheckerTool::modifyFileTimeByTimeApi(strPackageFile);

	std_out << _T("run resource package finished, OK!!!") << std::endl;
	return 0;
}
