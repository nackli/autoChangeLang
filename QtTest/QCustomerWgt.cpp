#include "QCustomerWgt.h"
#include <QStyleOption>
#include <QPainter>

QCustomerWgt::QCustomerWgt(QWidget *parent)
	: QWidget(parent)
{
}

QCustomerWgt::~QCustomerWgt()
{
}

void QCustomerWgt::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);
    QStyleOption styleOpt;
    styleOpt.init(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &styleOpt, &painter, this);
}