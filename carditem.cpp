#include "carditem.h"
#include <QtGui/QPainter>
#include <QtGui/QColor>
#include <QtWidgets/QGraphicsSceneMouseEvent>
#include <QtCore/QDebug>
CardItem::CardItem(QGraphicsItem *parent): QGraphicsObject(parent)
{
    setFlag(QGraphicsItem::ItemIsSelectable,true);
    bkPic = ":images/image/cardbk.png";
    isSelect = false;
    isFront = false;
}

CardItem::~CardItem(void)
{
    
}

QRectF CardItem::boundingRect() const
{
    if(isFront){
        return QRectF(pos().x(),pos().y(),95,128);
    }else{
        return QRectF(pos().x(),pos().y(),128,95);
    }
}

void CardItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    int x = pos().x();
    int y = pos().y();
    if(isFront){
        painter->drawPixmap(x,y,95,128,fkPic);
    }else{
        painter->translate(x+95/2,y+128/2);
        painter->rotate(90);
        painter->translate(-(x+95/2),-(y+128/2));
        painter->drawPixmap(x,y,95,128,QPixmap(bkPic));
    }
//    painter->setPen(Qt::red);
//    painter->drawRect(x,y,95,128);
}

void CardItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (isFront && (event->button() == Qt::LeftButton) && isSelected())
    {
        if(isSelect){
            moveBy(0,10);
            isSelect = false;
        }else{
            isSelect = true;
            moveBy(0,-10);
        }
        update(boundingRect());
        emit onClick(this);
    }
}

void CardItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << event->pos().x() << "," << event->pos().y();
}

void CardItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{

}
