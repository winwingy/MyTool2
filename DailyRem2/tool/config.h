#ifndef _CONFIGWY_H_
#define _CONFIGWY_H_
#include <string>
#include <tchar.h>



class ConfigWy
{
public:
    static ConfigWy* GetShared();

	bool Init(const tString& strFileName);

    tString GetConfigPath();

    tString GetValue(const tString& strAppName, const tString& strKeyName, 
        const tString& strDefault = tString());

	int GetValue(const tString& strAppName, const tString& strKeyName,
		int defaultValue = 0);

    void SetValue(const tString& strAppName, const tString& strKeyName,
        const tString& value);

    void SetValue(const tString& strAppName, const tString& strKeyName,
        int value);

    bool GetList(const tString& listBegin, const tString& listEnd, 
                 std::vector<tString>* listText);

private:
    ConfigWy();
    ~ConfigWy(void);
    static ConfigWy* pThis_;
    tString configPath_;
};
#endif