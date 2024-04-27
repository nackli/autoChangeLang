#pragma once
#include <map>
#include <string>
typedef std::map<std::string, std::string> MAPSTRPAIR;
class CLangTransform
{
public:
	CLangTransform();
	~CLangTransform();
	bool InitLangInfo(const char* strLangFile);
	const char* GetTransformLang(const char* strLangId);
	MAPSTRPAIR *GetAllTransformLang();
};

