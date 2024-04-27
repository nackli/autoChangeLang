#pragma once
#include <QString>

class QStyleSheetManage 
{
public:
	QStyleSheetManage();
	~QStyleSheetManage();
	static bool OnLoadStyleSheet(QString strFileName, QString strLangFileName);
};
