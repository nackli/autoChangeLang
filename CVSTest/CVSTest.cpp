// CVSTest.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <vector>
#include <istream>
#include <streambuf>
#include <fstream>
#include <sstream>
#include <string>
#include <list>
#include <stdlib.h>
#include<map>
#include<direct.h>
#include <windows.h>
#include <stdio.h>

using namespace std;
#define LANGUAGE_FILE_NAME "Language"
#define LANGUAGE_DIR "./"LANGUAGE_FILE_NAME

bool dirExists(const std::string& dirName_in)
{
    DWORD ftyp = GetFileAttributesA(dirName_in.c_str());
    if (ftyp == INVALID_FILE_ATTRIBUTES)
        return false;  //something is wrong with your path!

    if (ftyp & FILE_ATTRIBUTE_DIRECTORY)
        return true;   // this is a directory!

    return false;    // this is not a directory!
}

static bool OnCreateDir()
{
    bool fRet = false;
    if (!dirExists(LANGUAGE_DIR))
    {
        if (_mkdir(LANGUAGE_DIR) == 0)
            fRet = true;
    }
    return fRet;
}

static void OnOpenLangFile(list<FILE*>& strList, ifstream &hCvsHanle)
{
    string strLine;
    hCvsHanle.seekg(0, hCvsHanle.beg);
    getline(hCvsHanle, strLine);
    std::istringstream sin;         //将整行字符串line读入到字符串istringstream中
    sin.str(strLine);
    string word;
    OnCreateDir();
    while (getline(sin, word, ','))
    {
        if (word.compare("Lang_Id"))
        {    
            string strFileName = LANGUAGE_DIR;
            strFileName += ("/Lang_" + word + ".txt");
            FILE* fr = NULL;
            fopen_s(&fr, strFileName.c_str(), "wb");
            if (fr)
                strList.push_back(fr);           
        }
    }
    std::cout << strLine << std::endl;
}

static bool OnWriteLangFile(list<FILE*> strFileList, ifstream& hCvsHanle)
{
    string line;
    std::istringstream sin;         //将整行字符串line读入到字符串istringstream中
    std::string word;
    list<string> listLangKey;
    while (getline(hCvsHanle, line))
    {
        sin.clear();
        sin.str(line);
        string strKey = string();
        std::list<FILE*>::iterator itFile = strFileList.begin();

        while (getline(sin, word, ',') && itFile != strFileList.end()) //将字符串流sin中的字符读到field字符串中，以逗号为分隔符
        {
            if (strKey.empty())
            {
                if (find(listLangKey.begin(), listLangKey.end(), word) != listLangKey.end())
                {
                    std::cout << "Error: Lang_Id repeat ,please fix" << std::endl;
                    return false;
                }
                strKey = word;
                listLangKey.push_back(strKey);
                continue;
            }   
            FILE* fr = *itFile;
            if (fr)
            {
                string strContent = strKey + "=" + word + "\n";
                fwrite(strContent.c_str(), strContent.length(), 1, fr);
            }
            itFile++;
        }
    }
    return true;
}

static void OnCloseLangFile(list<FILE*>& strList)
{
    if (strList.empty())
        return;
    for (std::list<FILE*>::iterator itFile = strList.begin(); itFile != strList.end(); itFile++)
    {
        FILE* fr = *itFile;
        if (fr)
        {
            fclose(fr);
            fr = NULL;
        }
    }
    strList.clear();
}

static void OnReadCvsData(const char *strCvsFileName)
{
    std::ifstream csv_data(strCvsFileName, std::ios::in);
    std::string line;

    if (!csv_data.is_open())
    {
        std::cout << "Error: opening file fail" << std::endl;
        std::exit(1);
    }
    list<FILE*> strList;
    // 读取标题行
    OnOpenLangFile(strList, csv_data);
    OnWriteLangFile(strList, csv_data);
    OnCloseLangFile(strList);
    //OnCreateLangTxt(strList, mapContent);
    csv_data.close();
}

static void OnClearLangFile()
{
    char szCmd[128] = { 0 };
    sprintf_s(szCmd, "rd/s/q %s", LANGUAGE_FILE_NAME);
    system(szCmd);
}
/*
0x0000   Language   Neutral
0x007f   The   language   for   the   invariant   locale(LOCALE_INVARIANT).See   MAKELCID.
0x0400   Process or User   Default   Language
0x0800   System   Default   Language
0x0436   Afrikaans
0x041c   Albanian
0x0401   Arabic(Saudi   Arabia)
0x0801   Arabic(Iraq)
0x0c01   Arabic(Egypt)
0x1001   Arabic(Libya)
0x1401   Arabic(Algeria)
0x1801   Arabic(Morocco)
0x1c01   Arabic(Tunisia)
0x2001   Arabic(Oman)
0x2401   Arabic(Yemen)
0x2801   Arabic(Syria)
0x2c01   Arabic(Jordan)
0x3001   Arabic(Lebanon)
0x3401   Arabic(Kuwait)
0x3801   Arabic(U.A.E.)
0x3c01   Arabic(Bahrain)
0x4001   Arabic(Qatar)
0x042b   Windows   2000 / XP:   Armenian.This   is   Unicode   only.
0x042c   Azeri(Latin)
0x082c   Azeri(Cyrillic)
0x042d   Basque
0x0423   Belarusian
0x0402   Bulgarian
0x0455   Burmese
0x0403   Catalan
0x0404   Chinese(Taiwan)
0x0804   Chinese(PRC)
0x0c04   Chinese(Hong   Kong   SAR, PRC)
0x1004   Chinese(Singapore)
0x1404   Windows   98 / Me, Windows   2000 / XP:   Chinese(Macao   SAR)
0x041a   Croatian
0x0405   Czech
0x0406   Danish
0x0465   Windows   XP : Divehi.This   is   Unicode   only.
0x0413   Dutch(Netherlands)
0x0813   Dutch(Belgium)
0x0409   English(United   States)
0x0809   English(United   Kingdom)
0x0c09   English(Australian)
0x1009   English(Canadian)
0x1409   English(New   Zealand)
0x1809   English(Ireland)
0x1c09   English(South   Africa)
0x2009   English(Jamaica)
0x2409   English(Caribbean)
0x2809   English(Belize)
0x2c09   English(Trinidad)
0x3009   Windows   98 / Me, Windows   2000 / XP:   English(Zimbabwe)
0x3409   Windows   98 / Me, Windows   2000 / XP : English(Philippines)
0x0425   Estonian
0x0438   Faeroese
0x0429   Farsi
0x040b   Finnish
0x040c   French(Standard)
0x080c   French(Belgian)
0x0c0c   French(Canadian)
0x100c   French(Switzerland)
0x140c   French(Luxembourg)
0x180c   Windows   98 / Me, Windows   2000 / XP:   French(Monaco)
0x0456   Windows   XP : Galician
0x0437   Windows   2000 / XP : Georgian.This   is   Unicode   only.
0x0407   German(Standard)
0x0807   German(Switzerland)
0x0c07   German(Austria)
0x1007   German(Luxembourg)
0x1407   German(Liechtenstein)
0x0408   Greek
0x0447   Windows   XP : Gujarati.This   is   Unicode   only.
0x040d   Hebrew
0x0439   Windows   2000 / XP : Hindi.This   is   Unicode   only.
0x040e   Hungarian
0x040f   Icelandic
0x0421   Indonesian
0x0410   Italian(Standard)
0x0810   Italian(Switzerland)
0x0411   Japanese
0x044b   Windows   XP : Kannada.This   is   Unicode   only.
0x0457   Windows   2000 / XP : Konkani.This   is   Unicode   only.
0x0412   Korean
0x0812   Windows   95, Windows   NT   4.0   only : Korean(Johab)
0x0440   Windows   XP : Kyrgyz.
0x0426   Latvian
0x0427   Lithuanian
0x0827   Windows   98   only : Lithuanian(Classic)
0x042f   FYRO   Macedonian
0x043e   Malay(Malaysian)
0x083e   Malay(Brunei   Darussalam)
0x044e   Windows   2000 / XP : Marathi.This   is   Unicode   only.
0x0450   Windows   XP : Mongolian
0x0414   Norwegian(Bokmal)
0x0814   Norwegian(Nynorsk)
0x0415   Polish
0x0416   Portuguese(Brazil)
0x0816   Portuguese(Portugal)
0x0446   Windows   XP : Punjabi.This   is   Unicode   only.
0x0418   Romanian
0x0419   Russian
0x044f   Windows   2000 / XP : Sanskrit.This   is   Unicode   only.
0x0c1a   Serbian(Cyrillic)
0x081a   Serbian(Latin)
0x041b   Slovak
0x0424   Slovenian
0x040a   Spanish(Spain, Traditional   Sort)
0x080a   Spanish(Mexican)
0x0c0a   Spanish(Spain, Modern   Sort)
0x100a   Spanish(Guatemala)
0x140a   Spanish(Costa   Rica)
0x180a   Spanish(Panama)
0x1c0a   Spanish(Dominican   Republic)
0x200a   Spanish(Venezuela)
0x240a   Spanish(Colombia)
0x280a   Spanish(Peru)
0x2c0a   Spanish(Argentina)
0x300a   Spanish(Ecuador)
0x340a   Spanish(Chile)
0x380a   Spanish(Uruguay)
0x3c0a   Spanish(Paraguay)
0x400a   Spanish(Bolivia)
0x440a   Spanish(El   Salvador)
0x480a   Spanish(Honduras)
0x4c0a   Spanish(Nicaragua)
0x500a   Spanish(Puerto   Rico)
0x0430   Sutu
0x0441   Swahili(Kenya)
0x041d   Swedish
0x081d   Swedish(Finland)
0x045a   Windows   XP : Syriac.This   is   Unicode   only.
0x0449   Windows   2000 / XP : Tamil.This   is   Unicode   only.
0x0444   Tatar(Tatarstan)
0x044a   Windows   XP : Telugu.This   is   Unicode   only.
0x041e   Thai
0x041f   Turkish
0x0422   Ukrainian
0x0420   Windows   98 / Me, Windows   2000 / XP : Urdu(Pakistan)
0x0820   Urdu(India)
0x0443   Uzbek(Latin)
0x0843   Uzbek(Cyrillic)
0x042a   Windows   98 / Me, Windows   NT   4.0 and later : Vietnamese
*/
int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        std::cout << "Error: param error ,file not exist" << std::endl;
        return -1;
    }
    WORD wLangId = GetSystemDefaultLangID();
    OnClearLangFile();
    OnReadCvsData(argv[1]);
}
