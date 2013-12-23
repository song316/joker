#ifndef MYCONTROL_H
#define MYCONTROL_H

#include <QObject>
#include <QList>
#include <QMap>
#include <QSound>
#include <QTimerEvent>
#include <QGraphicsPixmapItem>
#include <QPoint>
#include "carditem.h"
#include "buttonitem.h"

class MyControl : public QObject
{
    Q_OBJECT
public:
    explicit MyControl(QObject *parent = 0);
    ~MyControl();
    void flashMyCardList();
    void timerEvent(QTimerEvent *event);
protected:
    QList<CardItem *> myCard;
    QMap<QString,CardItem *> myHandCardMap;
    QGraphicsPixmapItem *errorTip;
    QGraphicsPixmapItem *myHead;
    QPoint * myCardPos;
    ButtonItem *passButton;
    ButtonItem *tipButton;
    ButtonItem * takeoutButton;
    int showCardIndex;
signals:
    void takeouted();
public slots:
    void initGame(QList<CardItem*> item);
    void takeout();
    void cardSelect(CardItem *item);
    void someOneTakeout();
};

#endif // MYCONTROL_H
