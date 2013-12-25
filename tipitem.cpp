#include "tipitem.h"

TipItem::TipItem()
{
    setPixmap(QPixmap(":images/image/error.png"));
    startTimer(1000);
}

TipItem::~TipItem(){

}

void TipItem::timerEvent(QTimerEvent *event)
{
    killTimer(event->timerId());
    CentreControl::getInstance()->removeItem(this);
    this->deleteLater();
}
