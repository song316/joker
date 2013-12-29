#ifndef USERTHREAD_H
#define USERTHREAD_H

#include <QtCore/QThread>
#include <QtWidgets/QGraphicsPixmapItem>
#include <QtCore/QPoint>
#include "carditem.h"
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
	QList<CardItem *> handList;
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
    
};

#endif // USERTHREAD_H
