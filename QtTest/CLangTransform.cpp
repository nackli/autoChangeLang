#include "CLangTransform.h"
#include <iostream>

#include <fstream>
#include <sstream>
using namespace std;


static MAPSTRPAIR g_mapStrPair = MAPSTRPAIR();
CLangTransform::CLangTransform()
{

}

CLangTransform::~CLangTransform()
{

}

bool CLangTransform::InitLangInfo(const char* strLangFile)
{
    bool fRet = false;
	if (!strLangFile)
		return fRet;
    ifstream langStream(strLangFile, std::ios::in);
    string strLine = string();

    if (!langStream.is_open())
    {
        std::cout << "Error: opening file fail" << std::endl;
        std::exit(1);
    }
    if (!g_mapStrPair.empty())
        g_mapStrPair.clear();
    istringstream strStream = istringstream();
    while (getline(langStream, strLine))
    {
        strStream.clear();
        strStream.str(strLine);
        string word = string();
        string strLangInfo[2] = {string()};
        int iIndex = 0;
        while (getline(strStream, word, '='))
        {
            strLangInfo[iIndex] = word;
            iIndex++;
        }
        if(iIndex > 1)
            g_mapStrPair.insert(make_pair(strLangInfo[0], strLangInfo[1]));
    }
    langStream.close();
    if (g_mapStrPair.empty())
        fRet = true;
	return fRet;
}

const char* CLangTransform::GetTransformLang(const char* strLangId)
{
    if (!strLangId || g_mapStrPair.empty())
        return nullptr;
    return g_mapStrPair[strLangId].c_str();
}

MAPSTRPAIR* CLangTransform::GetAllTransformLang()
{
    return &g_mapStrPair;
}