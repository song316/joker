#ifndef TIPITEM_H
#define TIPITEM_H

#include <QGraphicsPixmapItem>
#include <QTimerEvent>
#include "centrecontrol.h"
class TipItem : public QGraphicsPixmapItem,QObject
{
public:
    TipItem();
    ~TipItem();
    void timerEvent(QTimerEvent *event);
};

#endif // TIPITEM_H
