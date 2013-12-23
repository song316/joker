#ifndef LEFTUSER_H
#define LEFTUSER_H

#include <QThread>
#include <QGraphicsPixmapItem>
#include <QPoint>
#include "carditem.h"
//#include <buttonitem.h>
#include "centrecontrol.h"
#include "cardutil.h"
#include "timeritem.h"
class UserThread : public QThread
{
    Q_OBJECT
public:
    explicit UserThread(QObject *parent = 0);
    ~UserThread();
    void init(QList<CardItem *> cardList,QPoint * cardPos,QGraphicsPixmapItem *head);
private:
    void run();

private:
    QList<CardItem *> myCardList;
    QList<CardItem*> preCardList;
    QGraphicsPixmapItem *errorTip;
    QGraphicsPixmapItem *myHead;
    QGraphicsPixmapItem *time;
    int timeCount;
    QPoint * myCardPos;
public:
    int index;

signals:
    void takeouted();
public slots:
    void someOneTakeout();
};

#endif // LEFTUSER_H
