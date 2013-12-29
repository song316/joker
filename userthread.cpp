#pragma warning(disable: 4819)
#include "userthread.h"
#include "cardutil.h"
#include "centrecontrol.h"
UserThread::UserThread(QObject *parent) :
    QThread(parent)
{
    errorTip = NULL;
    myHead = NULL;
    myCardPos = NULL;

}
UserThread::~UserThread()
{
    delete errorTip;
    delete myHead;
    delete myCardPos;

    errorTip = NULL;
    myHead = NULL;
    myCardPos = NULL;
}

void UserThread::init(QList<CardItem *> cardList,QPoint * cardPos,QGraphicsPixmapItem *head){
    myCardList = cardList;
    myCardPos = cardPos;
    this->myHead = head;

    //显示牌
    int x = myCardPos->x();
    int y = myCardPos->y()-(95+myCardList.size()*10)/2;
    for (int var = 0; var < myCardList.size(); ++var) {
        CardItem *item = myCardList.value(var);
        item->setPos(QPoint(x,y+var*10));
        CentreControl::getInstance()->addItem(item);
    }
    CentreControl::getInstance()->addItem(myHead);
    CentreControl::getInstance()->updateScene();
}

void UserThread::run()
{
    while (true) {
        //qDebug()<<CentreControl::getInstance()->handerIndex<<"-------------";
        QThread::msleep(3000);
        if(index == CentreControl::getInstance()->handerIndex){
            QThread::msleep(3000);
            //随便出一张.
            QList<CardItem *> handList;
            CardItem *item = myCardList.takeLast();
            item->isFront = true;
            handList << item;
			CentreControl::getInstance()->removeItem(item);
            CentreControl::getInstance()->showPreCardList(handList);
            CentreControl::getInstance()->updateScene();
            emit takeouted();
            //qDebug()<<CentreControl::getInstance()->handerIndex<<"------out-------";
        }
    }
}