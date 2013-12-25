#include "timeritem.h"
#include "centrecontrol.h"
TimerItem::TimerItem()
{
    timeCount = 9;
    pic = ":images/image/score_minus.png";
    imageWidth = 450;
    imageHight = 63;
    imageNum = 10;
    startTimer(1000);
}

TimerItem::~TimerItem()
{

}

void TimerItem::timerEvent(QTimerEvent *event)
{
    if(timeCount == 0){
        killTimer(event->timerId());
        CentreControl::getInstance()->removeItem(this);
        this->deleteLater();
    }else{
        timeCount--;
        CentreControl::getInstance()->updateScene();
    }
}
QRectF  TimerItem::boundingRect() const
{
    return QRectF(pos().x(),pos().y(),imageWidth/imageNum,imageHight);
}

void TimerItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(pos().x(),pos().y(),QPixmap(pic),imageWidth/imageNum*timeCount,0,imageWidth/imageNum,imageHight);
}
