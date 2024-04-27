#pragma once

#include <QPushButton>

class QChangeTipBtn : public QPushButton
{
	Q_OBJECT
	Q_PROPERTY(QString toolTip READ OnGetToolTip WRITE OnSetToolTip)
	Q_PROPERTY(QString changeTip READ OnGetChangeTip WRITE OnSetChangeTip)
public:
	QChangeTipBtn(QWidget *parent);
	~QChangeTipBtn();
	void OnSetChangeStatus(bool bChangeStatus);
private:
	QString OnGetToolTip();
	void OnSetToolTip(QString strToolTip);
	QString OnGetChangeTip();
	void OnSetChangeTip(QString strChangeTip);
	bool event(QEvent* event);
private:
	QString m_strToolTip;
	QString m_strChangeTip;
	bool m_bChangeStatus;
};
