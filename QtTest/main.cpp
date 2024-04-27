//#include <QtCore/QCoreApplication>
#include <QApplication>
#include "QTestWgt.h"
#include "QStyleSheetManage.h"
#include <Windows.h>
#include <QMetaProperty>

typedef struct TEST_STRUCT{
    int iTest;
    QString strName;
}TEST_STRUCT;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QStyleSheetManage::OnLoadStyleSheet("test.qss", "./Language/Lang_zh.txt");
    QTestWgt wgt;
    wchar_t strLocaleName[200] = { 0 };
    GetUserDefaultLocaleName(strLocaleName, 200);
    LCID  lcid = GetUserDefaultLCID();
    QWidgetList  all = QApplication::allWidgets();
    for (QWidgetList::ConstIterator it = all.constBegin(), cend = all.constEnd(); it != cend; ++it) 
    {
        QWidget* w = *it;
        QString str = w->objectName();
        QString strClass = w->metaObject()->className();
        for (int i = 0; i < w->metaObject()->propertyCount(); i++)
        {
            QMetaProperty pta =  w->metaObject()->property(i);
            QString str  = QString(pta.name());
            

        }
    }
    wgt.show();
    return a.exec();
}
