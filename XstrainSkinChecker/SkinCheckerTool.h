#pragma once
bool operator < (const FILETIME &left, const FILETIME& right);
bool operator == (const FILETIME &left, const FILETIME& right);
bool operator > (const FILETIME &left, const FILETIME& right);
class SkinCheckerTool
{
public:
	SkinCheckerTool(void);
	~SkinCheckerTool(void);

	static bool GetFolderLastModifyTime(const tstring& dir, 
		bool bRecursion, FILETIME* lastModifyTime);

	static bool GetFileLastModifyTime(const tstring& file, 
		 FILETIME* lastModifyTime);

	static bool modifyFileTime(const tstring& filePath);
	//���ײ�����ʽ����
	static bool modifyFileTimeC(const tstring& filePath);

	static bool modifyFileTimeByTimeApi(const tstring& filePath);
};

