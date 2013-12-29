#ifndef MYCONTROL_H
#define MYCONTROL_H

#include <QtCore/QObject>
#include <QtCore/QList>
#include <QtCore/QMap>
#include <QtMultimedia/QSound>
#include <QtCore/QTimerEvent>
#include <QtWidgets/QGraphicsPixmapItem>
#include <QtCore/QPoint>
#include "carditem.h"
#include "buttonitem.h"
#include "tipitem.h"

class MyControl : public QObject
{
    Q_OBJECT
public:
    explicit MyControl(QObject *parent = 0);
    ~MyControl();
    void flashMyCardList();
    void timerEvent(QTimerEvent *event);

    TipItem *tip;
protected:
    QList<CardItem *> myCardList;
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
