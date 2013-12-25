#pragma warning(disable: 4819)
#include "centrecontrol.h"
#include "cardutil.h"

CentreControl *CentreControl::m_instance = 0;

CentreControl::CentreControl(QWidget *parent) :
    QMainWindow(parent)
{
    view = NULL;
    scene = NULL;
    startButton = NULL;
    handerIndex = 0;
    master = 0;
    leftUser = NULL;
    rightUser = NULL;

    setFixedSize(1000,700);
    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,998,698);
    scene->addPixmap(QPixmap(":images/image/background.jpg"));
    view = new JokerView(this);
    view->setScene(scene);
    view->setFixedSize(1000,700);
    view->show();

    startButton = new ButtonItem;
    startButton->picHight = 56;
    startButton->picWidth = 294;
    startButton->picNum = 2;
    startButton->setPos(QPoint(230,150));
    startButton->pic = QPixmap(":images/image/start.png");
    scene->addItem(startButton);

    connect(startButton,SIGNAL(onClick()),this,SLOT(startButtonClicked()));

//    layer = new QMediaPlayer;
//    player->setMedia(QUrl::fromLocalFile("/Users/me/Music/coolsong.mp3"));
//    player->setVolume(50);
//    player->play();
}


CentreControl::~CentreControl(void)
{
    delete view;
    delete scene;
    delete startButton;
    view = NULL;
    scene = NULL;
    startButton = NULL;
    leftUser = NULL;
    rightUser = NULL;
}

void CentreControl::startButtonClicked()
{
    //删除开始按钮
    delete startButton;
    //定义三人的牌和底牌，并排序
    QList<CardItem *> myCard;
    QList<CardItem *> leftCard;
    QList<CardItem *> rightCard;
    QList<CardItem *> bottomList;
    CardUtil::dealCard(myCard,leftCard,rightCard,bottomList);

    //选地主
    qsrand(QTime::currentTime().msec());
    master = qrand()%3+1;
    handerIndex = master;
    QString leftHeadImage = ":images/image/farmers_left.png";
    QString rightHeadImage = ":images/image/farmers_left.png";
    switch (master) {
    case 1:
        foreach(CardItem * item,bottomList){
            item->isFront = true;
            myCard.append(item);
        }
        break;
    case 2:
        rightCard << bottomList.at(0)<<bottomList.at(1)<< bottomList.at(2);
        rightHeadImage = ":images/image/lord_left.png";
        break;
    case 3:
        leftCard << bottomList.at(0)<<bottomList.at(1)<< bottomList.at(2);
        leftHeadImage = ":images/image/lord_left.png";
        break;
    default:
        break;
    }
    CardUtil::sortCardList(myCard);
    CardUtil::sortCardList(rightCard);
    CardUtil::sortCardList(leftCard);
    //创建右边玩家头像（旋转头像），和用户线程，并初始化
    QGraphicsPixmapItem *rightHead = new QGraphicsPixmapItem();
    rightHead->setPixmap(QPixmap(rightHeadImage));
    rightHead->setPos(850,10);
    QRectF rect = rightHead->boundingRect();
    rightHead->setTransformOriginPoint(rect.x()+(rect.width())/2,rect.y()+(rect.height())/2);
    rightHead->setRotation(90);
    rightUser = new UserThread();
    rightUser->index = 2;
    QPoint *rightPos = new QPoint(420,195);
    rightUser->init(rightCard,rightPos,rightHead);
//    connect(this,SIGNAL(someOneTakeout()),rightUser,SLOT(someOneTakeout()));
    connect(rightUser,SIGNAL(takeouted()),this,SLOT(takeouted()));
    rightUser->start();

    //创建左边玩家头像，和用户线程，并初始化
    QGraphicsPixmapItem *leftHead = new QGraphicsPixmapItem();
    leftHead->setPixmap(QPixmap(leftHeadImage));
    leftHead->setPos(30,10);
    leftUser = new UserThread();
    leftUser->index = 3;
    QPoint *leftPos =new QPoint(30,195);
    leftUser->init(leftCard,leftPos,leftHead);
//    connect(this,SIGNAL(someOneTakeout()),leftUser,SLOT(someOneTakeout()));
    connect(leftUser,SIGNAL(takeouted()),this,SLOT(takeouted()));
    leftUser->start();
    //发送开始游戏信号。
    emit startGame(myCard);
    //发送出牌信号
    emit someOneTakeout();
}

void CentreControl::nextHander()
{
    if(handerIndex == 0){
        handerIndex = master;
    }else if(handerIndex == 1){
        handerIndex = 2;
    }else if(handerIndex == 2){
        handerIndex = 3;
    }else if(handerIndex == 3){
        handerIndex = 1;
    }
}
/**
 * scene添加item
 * @brief CentreControl::addItem
 * @param item
 */
void CentreControl::addItem(QGraphicsItem *item)
{
    scene->addItem(item);
}
/**
 * scene删除item。
 * @brief CentreControl::removeItem
 * @param item
 */
void CentreControl::removeItem(QGraphicsItem *item)
{
    scene->removeItem(item);
}
/**
 *更新scene
 * @brief CentreControl::updateScene
 */
void CentreControl::updateScene()
{
    scene->update(0,0,998,698);
}

void CentreControl::showPreCardList(QList<CardItem*> &cardList)
{
    //删除已出牌。
    if(preCardList.size() > 0){
        foreach(CardItem *item,preCardList){
            scene->removeItem(item);
            delete item;
        }
    }
    this->preCardList = cardList;
    int x = 230;
    int y = 100;
    int j = 0;
    foreach (CardItem *item, preCardList) {
        item->setPos(QPoint(x+j*15,y));
        item->setScale(0.8);
        item->update(item->boundingRect());
        item->setSelected(false);
        scene->addItem(item);
        j++;
    }
}

void CentreControl::takeouted()
{
    nextHander();
    emit someOneTakeout();
}
