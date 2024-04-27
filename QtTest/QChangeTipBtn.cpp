#include "QChangeTipBtn.h"
#include <QHelpEvent>
#include <QToolTip>

QChangeTipBtn::QChangeTipBtn(QWidget *parent)
	: QPushButton(parent)
{
}

QChangeTipBtn::~QChangeTipBtn()
{
}

void QChangeTipBtn::OnSetToolTip(QString strToolTip)
{ 
	m_strToolTip = strToolTip;
}

QString QChangeTipBtn::OnGetToolTip()
{
	return m_strToolTip;
}

QString QChangeTipBtn::OnGetChangeTip() 
{ 
	return m_strChangeTip;
}

void QChangeTipBtn::OnSetChangeTip(QString strChangeTip)
{ 
	m_strChangeTip = strChangeTip;
}

bool QChangeTipBtn::event(QEvent* event)
{
    if (event->type() == QEvent::ToolTip) {

        QHelpEvent* helpEvent = static_cast<QHelpEvent*>(event);
        QString strToolTip = OnGetToolTip();
        if (m_bChangeStatus)
            strToolTip = OnGetChangeTip();
        this->setToolTip(strToolTip);
        QToolTip::showText(helpEvent->globalPos(), toolTip());
    }
    return QWidget::event(event);
}

void QChangeTipBtn::OnSetChangeStatus(bool bChangeStatus)
{
    m_bChangeStatus = bChangeStatus;
}