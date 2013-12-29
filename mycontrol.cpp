#include "mycontrol.h"
#include "centrecontrol.h"
#include "cardutil.h"

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
	tip = NULL;

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
    myCardList = itemList;

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
	bool flag = CardUtil::isOvercomePrev(myHandCardMap.values(),CardUtil::getCardType(myHandCardMap.values()),CentreControl::getInstance()->preCardList,CardUtil::getCardType(CentreControl::getInstance()->preCardList));
	//如果已选牌数大于0，且大于上一手牌，则可以出牌，否则弹出错误提示。
	if(flag){
		//从手牌和界面中删除已选牌。
		QMap<QString, CardItem*>::const_iterator i;
		for(i=myHandCardMap.constBegin(); i!=myHandCardMap.constEnd(); ++i)
		{
			myCardList.removeOne(i.value());
			CentreControl::getInstance()->removeItem(i.value());
		}
		//显示已出牌到出牌区
		QList<CardItem*> perList = myHandCardMap.values();
		CentreControl::getInstance()->showPreCardList(perList);
		//清除已选牌map，并更新手牌显示。
		myHandCardMap.clear();
		flashMyCardList();
		//修改三个操作按钮为不可用
		takeoutButton->picShowPos = 2;
		tipButton->picShowPos = 2;
		passButton->picShowPos = 2;
		takeoutButton->update(takeoutButton->boundingRect());
		tipButton->update(tipButton->boundingRect());
		passButton->update(passButton->boundingRect());
		emit takeouted();
	}else{
		//生成选牌格式不对提示
		tip = new TipItem();
		tip->setPos(350,600);
		CentreControl::getInstance()->addItem(tip);
        return;
    }
}
/**
 * 刷新自己所有的牌。
 * @brief MyControl::flashMyCardList
 */
void MyControl::flashMyCardList()
{
    for(int i=0;i<myCardList.size();i++){
        CentreControl::getInstance()->removeItem(myCardList.value(i));
    }
    //显示牌
    int x = myCardPos->x()-(95+myCardList.size()*15)/2;
    int y = myCardPos->y();
    for(int i=0;i<myCardList.size();i++){
        CardItem *item = myCardList.value(i);
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
    if(showCardIndex >= myCardList.size()){
        killTimer(event->timerId());
    }else{
        int x = myCardPos->x()-(95+myCardList.size()*15)/2;
        int y = myCardPos->y();
        CardItem *item = myCardList.value(showCardIndex);
        item->setPos(QPoint(x+15*showCardIndex,y));
        connect(item,SIGNAL(onClick(CardItem*)),this,SLOT(cardSelect(CardItem*)));
        CentreControl::getInstance()->addItem(item);

        showCardIndex++;
    }
//    CentreControl::getInstance()->updateScene();
}

void MyControl::someOneTakeout()
{
    if(CentreControl::getInstance()->handerIndex == 1){
        takeoutButton->picShowPos = 0;
        tipButton->picShowPos = 0;
        passButton->picShowPos = 0;
        takeoutButton->update(takeoutButton->boundingRect());
        tipButton->update(tipButton->boundingRect());
        passButton->update(passButton->boundingRect());
    }
}
