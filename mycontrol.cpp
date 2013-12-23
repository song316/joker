#include "mycontrol.h"
#include "centrecontrol.h"

MyControl::MyControl(QObject *parent) :
    QObject(parent)
{
    showCardIndex = 0;
    errorTip = NULL;
    myHead = NULL;
    myCardPos = new QPoint(270,270);
    passButton = NULL;
    tipButton = NULL;
    takeoutButton = NULL;

}
MyControl::~MyControl()
{
    delete errorTip;
    delete myHead;
    delete myCardPos;
    delete passButton;
    delete tipButton;
    delete takeoutButton;
    errorTip = NULL;
    myHead = NULL;
    myCardPos = NULL;
    passButton = NULL;
    tipButton = NULL;
    takeoutButton = NULL;
}

/**
 * 初始化牌。
 * @brief MyControl::initGame
 * @param item
 */
void MyControl::initGame(QList<CardItem*> itemList)
{
    myCard = itemList;

    takeoutButton = new ButtonItem;
    takeoutButton->picHight = 69;
    takeoutButton->picWidth = 348;
    takeoutButton->picNum = 3;
    takeoutButton->setPos(QPoint(150,230));
    takeoutButton->pic = QPixmap(":images/image/takeout.png");
    takeoutButton->picShowPos = 2;
    connect(takeoutButton,SIGNAL(onClick()),this,SLOT(takeout()));
    CentreControl::getInstance()->addItem(takeoutButton);

    passButton = new ButtonItem;
    passButton->picHight = 69;
    passButton->picWidth = 348;
    passButton->picNum = 3;
    passButton->setPos(QPoint(230,230));
    passButton->pic = QPixmap(":images/image/pass.png");
    passButton->picShowPos = 2;
    CentreControl::getInstance()->addItem(passButton);

    tipButton = new ButtonItem;
    tipButton->picHight = 69;
    tipButton->picWidth = 348;
    tipButton->picNum = 3;
    tipButton->setPos(QPoint(300,230));
    tipButton->pic = QPixmap(":images/image/tip.png");
    tipButton->picShowPos = 2;
    CentreControl::getInstance()->addItem(tipButton);

    myHead = new QGraphicsPixmapItem();
    myHead->setPixmap(QPixmap(":images/image/farmers.png"));
    myHead->setPos(30,570);
    CentreControl::getInstance()->addItem(myHead);

    startTimer(230);
    QSound::play(":sounds/sound/sendcard.wav");
}
/**
 * 出牌
 * @brief MyControl::takeout
 */
void MyControl::takeout()
{
    if(myHandCardMap.size() <= 0){
        errorTip = new QGraphicsPixmapItem();
        errorTip->setPixmap(QPixmap(":images/image/error.png"));
        errorTip->setPos(350,600);
        CentreControl::getInstance()->addItem(errorTip);
        return;
    }
    QMap<QString, CardItem*>::const_iterator i;
    for(i=myHandCardMap.constBegin(); i!=myHandCardMap.constEnd(); ++i)
    {
        myCard.removeOne(i.value());
        CentreControl::getInstance()->removeItem(i.value());
    }
    QList<CardItem*> perList = myHandCardMap.values();
    CentreControl::getInstance()->showPreCardList(perList);
    myHandCardMap.clear();
    flashMyCardList();
    takeoutButton->picShowPos = 2;
    tipButton->picShowPos = 2;
    passButton->picShowPos = 2;
    takeoutButton->update(takeoutButton->boundingRect());
    tipButton->update(tipButton->boundingRect());
    passButton->update(passButton->boundingRect());
//    CentreControl::getInstance()->updateScene();
    emit takeouted();
}
/**
 * 刷新自己所有的牌。
 * @brief MyControl::flashMyCardList
 */
void MyControl::flashMyCardList()
{
    for(int i=0;i<myCard.size();i++){
        CentreControl::getInstance()->removeItem(myCard.value(i));
    }
    //显示牌
    int x = myCardPos->x()-(95+myCard.size()*15)/2;
    int y = myCardPos->y();
    for(int i=0;i<myCard.size();i++){
        CardItem *item = myCard.value(i);
        item->setPos(QPoint(x+15*i,y));
        CentreControl::getInstance()->addItem(item);
    }
}
/**
 * 牌被选择了。
 * @brief MyControl::cardSelect
 * @param item
 */
void MyControl::cardSelect(CardItem *item)
{
    if(item->isSelect){
        myHandCardMap.insert(QString::number(item->CardNum)+item->cardType,item);
    }else{
        myHandCardMap.remove(QString::number(item->CardNum)+item->cardType);
    }
}
/**
 * 发牌动画，时间事件。
 * @brief MyControl::timerEvent
 * @param event
 */
void MyControl::timerEvent(QTimerEvent *event)
{
    qDebug() << "timerevent....";
    if(showCardIndex >= myCard.size()){
        killTimer(event->timerId());
    }else{
        int x = myCardPos->x()-(95+myCard.size()*15)/2;
        int y = myCardPos->y();
        CardItem *item = myCard.value(showCardIndex);
        item->setPos(QPoint(x+15*showCardIndex,y));
        connect(item,SIGNAL(onClick(CardItem*)),this,SLOT(cardSelect(CardItem*)));
        CentreControl::getInstance()->addItem(item);

        showCardIndex++;
    }
//    CentreControl::getInstance()->updateScene();
}

void MyControl::someOneTakeout()
{
    qDebug()<<CentreControl::getInstance()->handerIndex<<"------sss-------";
    if(CentreControl::getInstance()->handerIndex == 1){
        takeoutButton->picShowPos = 0;
        tipButton->picShowPos = 0;
        passButton->picShowPos = 0;
        takeoutButton->update(takeoutButton->boundingRect());
        tipButton->update(tipButton->boundingRect());
        passButton->update(passButton->boundingRect());
//        CentreControl::getInstance()->updateScene();
    }
}
