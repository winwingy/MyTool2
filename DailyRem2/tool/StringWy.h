#pragma once


class StringWy
{
public:
	StringWy(void);
	~StringWy(void);

	static tString IntToString(int val);
	static int StringToInt(const tString& str);
};

