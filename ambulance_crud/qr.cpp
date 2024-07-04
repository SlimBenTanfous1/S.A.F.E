#include "qr.h"
#include <QPainter>
#include <QDebug>
#include <qrencode.h>

QRWidget::QRWidget(QWidget *parent) :QWidget(parent), data("Hello QR")//Note: The encoding fails with empty string so I just default to something else. Use the setQRData() call to change this.
{
}

void QRWidget::setQRData(QString data)
{
    this->data=data;
    update();
}

void QRWidget::paintEvent(QPaintEvent *pe)
{

}
