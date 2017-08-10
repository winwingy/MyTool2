#include "StdAfx.h"
#include "config.h"
#include <assert.h>
#include <windows.h>
#include <WTypes.h>
#include "StringWy.h"

ConfigWy* ConfigWy::pThis_ = nullptr;

namespace
{
    tString GetPrivateProfileValue(
        const tString& strAppName, const tString& strKeyName, const tString& strDefault,
        const tString& strFileName)
    {
        TCHAR valueBuf[1024] = { 0 };
        DWORD ret = ::GetPrivateProfileString(strAppName.c_str(), strKeyName.c_str(),
                                  strDefault.c_str(), valueBuf,
                                  sizeof(valueBuf) - 1, strFileName.c_str());
        return valueBuf;
    }
}

ConfigWy* ConfigWy::GetShared()
{
    if (!pThis_)
    {
        pThis_ = new ConfigWy;
    }
    return pThis_;
}

ConfigWy::ConfigWy()
    : configPath_()
{

}

ConfigWy::~ConfigWy(void)
{

}

tString ConfigWy::GetConfigPath()
{
    return configPath_;
}

bool ConfigWy::Init(const tString& strFileName)
{
	if (!configPath_.empty())
		return true;

	FILE* fp = nullptr;
	_tfopen_s(&fp, strFileName.c_str(), _T("rb"));
	if (nullptr == fp)
		return false;

	fclose(fp);
	configPath_ =  strFileName;
    return true;
}

tString ConfigWy::GetValue(const tString& strAppName,
                        const tString& strKeyName, const tString& strDefault)
{
    return GetPrivateProfileValue(
        strAppName, strKeyName, strDefault, configPath_);
}

int ConfigWy::GetValue(const tString& strAppName,
                     const tString& strKeyName, int defaultValue)
{
    tString value = GetPrivateProfileValue(
        strAppName, strKeyName, StringWy::IntToString(defaultValue),
        configPath_);
    return StringWy::StringToInt(value);
}

void ConfigWy::SetValue(const tString& strAppName,
                      const tString& strKeyName, const tString& value)
{
    assert(0);
}

void ConfigWy::SetValue(const tString& strAppName,
                      const tString& strKeyName, int value)
{
    assert(0);
}

bool ConfigWy::GetList(const tString& listBegin, const tString& listEnd,
                     std::vector<tString>* listText)
{
   
    return false;
}


