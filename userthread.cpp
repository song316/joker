#pragma warning(disable: 4819)
#include "userthread.h"
#include "cardutil.h"
#include "timeritem.h"
#include "centrecontrol.h"
UserThread::UserThread(QObject *parent) :
    QThread(parent)
{
    errorTip = NULL;
    myHead = NULL;
    time = NULL;
    myCardPos = NULL;

}
UserThread::~UserThread()
{
    delete errorTip;
    delete myHead;
    delete time;
    delete myCardPos;

    errorTip = NULL;
    myHead = NULL;
    time = NULL;
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
        qDebug()<<CentreControl::getInstance()->handerIndex<<"-------------";
        QThread::msleep(3000);
        if(index == CentreControl::getInstance()->handerIndex){
//            TimerItem timerItem;
//            timerItem.setPos(myCardPos->x()-30,myCardPos->y()-40);
//            CentreControl::getInstance()->addItem(&timerItem);
            QThread::msleep(3000);
            //随便出一张.
            QList<CardItem *> list;
            CardItem *item = myCardList.takeLast();
            item->isFront = true;
            list << item;
            CentreControl::getInstance()->showPreCardList(list);
            CentreControl::getInstance()->updateScene();
            emit takeouted();
            qDebug()<<CentreControl::getInstance()->handerIndex<<"------out-------";
        }
    }
}

void UserThread::someOneTakeout()
{
//    qDebug()<<CentreControl::getInstance()->handerIndex<<"-------------";
//    if(index == CentreControl::getInstance()->handerIndex){
//        //出牌。
//        QList<CardItem *> preCardList = CentreControl::getInstance()->preCardList;
//        if(CardUtil::isOvercomePrev(myCardList,preCardList,CardUtil::getCardType(preCardList))){
//            //随便出一张.
//            QList<CardItem *> list;
//            CardItem *item = myCardList.takeLast();
//            item->isFront = true;
//            list << item;
//            CentreControl::getInstance()->showPreCardList(list);
//        }
//        emit takeouted();
//    }
}
