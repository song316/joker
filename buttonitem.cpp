#include "buttonitem.h"
#include <QtWidgets/QMessageBox>
ButtonItem::ButtonItem(QGraphicsItem *parent):QGraphicsObject(parent)
{
    picShowPos = 0;
}

QRectF ButtonItem::boundingRect() const
{
    return QRectF(pos().x(),pos().y(),picWidth/picNum,picHight);
}

void ButtonItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(pos().x(),pos().y(),pic,picWidth/picNum*picShowPos,0,picWidth/picNum,picHight);
}

void ButtonItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(picShowPos != (picNum-1)){
        picShowPos = 1;
        update(boundingRect());
        emit onClick();
    }
}

void ButtonItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if(picShowPos != (picNum-1)){
        picShowPos = 0;
        update(boundingRect());
    }
}
