#include "QStyleSheetManage.h"
#include <QApplication>
#include <QFile>
#include <QMap>
#include <QMetaEnum>
#include "CLangTransform.h"

//template <typename T>
QMap<QString, int> m_qtStyleEnumMap;

static QString replaceQtStyleEnumValue(const QString& str) 
{
	QString result = str;
	QMap<QString, int>::Iterator it = m_qtStyleEnumMap.begin();
	while (it != m_qtStyleEnumMap.end()) 
	{
		result.replace(it.key(), QString::number(it.value()));
		it++;
	}
	return result;
}

template <typename T>
static void insertQtStyleEnumMap() 
{
	QMetaEnum metaEnum = QMetaEnum::fromType<T>();
	for (int i = 0; i < metaEnum.keyCount(); i++) 
		m_qtStyleEnumMap.insert(metaEnum.key(i), metaEnum.value(i));
}

QStyleSheetManage::QStyleSheetManage()
{
}

QStyleSheetManage::~QStyleSheetManage()
{
}

static bool OnLoadLang2Qss(MAPSTRPAIR *pMapLanguage, QString& strQSS)
{
	if (!pMapLanguage || pMapLanguage->empty() || strQSS.isEmpty())
		return false;

	for (MAPSTRPAIR::iterator iter = pMapLanguage->begin(); iter != pMapLanguage->end(); iter++)
		strQSS.replace(QRegExp(QString::fromLocal8Bit(iter->first.c_str()) + ";"), QString::fromLocal8Bit(iter->second.c_str()) + ";");
	return true;
}

static bool OnLoadQss(QString strFileName, QString strLangFileName)
{
	if (strFileName.isEmpty())
		return false;
	QFile qss(strFileName);
	if (qss.open(QFile::ReadOnly))
	{
		QString style = QString::fromLocal8Bit(qss.readAll());
		MAPSTRPAIR mapLanguage;
		CLangTransform LangTrans;
		LangTrans.InitLangInfo(strLangFileName.toStdString().c_str());

		OnLoadLang2Qss(LangTrans.GetAllTransformLang(), style);
		qApp->setStyleSheet(style);
		
		qss.close();
		return true;
	}
	return false;
}

bool QStyleSheetManage::OnLoadStyleSheet(QString strStyleFileName,QString strLangFileName)
{
	return OnLoadQss(strStyleFileName, strLangFileName);
}