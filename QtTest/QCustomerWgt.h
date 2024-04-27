#pragma once

#include <QWidget>

class QCustomerWgt : public QWidget
{
	Q_OBJECT

public:
	QCustomerWgt(QWidget *parent);
	~QCustomerWgt();
private:
	void paintEvent(QPaintEvent* event);
};
