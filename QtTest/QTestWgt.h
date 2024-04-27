#pragma once

#include <QWidget>
#include <QHBoxLayout>
class QTestWgt : public QWidget
{
	Q_OBJECT
public:
	QTestWgt(QWidget *parent = nullptr);
	~QTestWgt();
	void OnCreateGui();
private slots:
	void OnSlotChangeStyleBtn();
private: 
	QHBoxLayout* m_pMainHLayout;
};
