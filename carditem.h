﻿#ifndef CARDITEM_H
#define CARDITEM_H

#include <QtWidgets/QGraphicsObject>
class CardItem :
    public QGraphicsObject
{
    Q_OBJECT
public:
    CardItem(QGraphicsItem *parent = 0);
    ~CardItem(void);
    QRectF  boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    //void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    //void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
	bool move();
public:
    QPixmap fkPic;
    QString bkPic;
    int CardNum;
    QString cardType;
    bool isSelect;
    bool isFront;

signals:
    void onClick(CardItem *item);
};

#endif // CARDITEM_H
