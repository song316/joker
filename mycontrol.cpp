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

}
MyControl::~MyControl()
{
    //delete errorTip;
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
	//初始化出牌按钮
    takeoutButton = new ButtonItem;
    takeoutButton->picHight = 69;
    takeoutButton->picWidth = 348;
    takeoutButton->picNum = 3;
    takeoutButton->setPos(QPoint(150,230));
    takeoutButton->pic = QPixmap(":images/image/takeout.png");
    takeoutButton->picShowPos = 2;
    connect(takeoutButton,SIGNAL(onClick()),this,SLOT(takeout()));
    CentreControl::getInstance()->addItem(takeoutButton);
	//初始化不出按钮
    passButton = new ButtonItem;
    passButton->picHight = 69;
    passButton->picWidth = 348;
    passButton->picNum = 3;
    passButton->setPos(QPoint(230,230));
    passButton->pic = QPixmap(":images/image/pass.png");
    passButton->picShowPos = 2;
	connect(passButton,SIGNAL(onClick()),this,SLOT(skip()));
    CentreControl::getInstance()->addItem(passButton);
	//初始化提示按钮
    tipButton = new ButtonItem;
    tipButton->picHight = 69;
    tipButton->picWidth = 348;
    tipButton->picNum = 3;
    tipButton->setPos(QPoint(300,230));
    tipButton->pic = QPixmap(":images/image/tip.png");
    tipButton->picShowPos = 2;
	connect(tipButton,SIGNAL(onClick()),this,SLOT(tip()));
    CentreControl::getInstance()->addItem(tipButton);
	//初始化头像
    myHead = new QGraphicsPixmapItem();
	if(CentreControl::getInstance()->master == 1){
		myHead->setPixmap(QPixmap(":images/image/landlord.png"));
	}else{
		myHead->setPixmap(QPixmap(":images/image/farmers.png"));
	}
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
			CentreControl::getInstance()->newPreCardList.append(i.value());
		}
		//显示已出牌到出牌区
		CentreControl::getInstance()->showPreCardList();
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
		errorTip = new TipItem();
		errorTip->setPos(350,600);
		CentreControl::getInstance()->addItem(errorTip);
        return;
    }
}

void MyControl::skip(){
	//把选中的牌归位。
	QMap<QString, CardItem*>::const_iterator i;
	for(i=myHandCardMap.constBegin(); i!=myHandCardMap.constEnd(); ++i)
	{
		CardItem *item = i.value();
		item->moveBy(0,10);
		item->isSelect = false;
	}
	myHandCardMap.clear();
	//发送已出牌信号
	emit takeouted();
	//修改按钮状态为不可用。
	//修改三个操作按钮为不可用
	takeoutButton->picShowPos = 2;
	tipButton->picShowPos = 2;
	passButton->picShowPos = 2;
	takeoutButton->update(takeoutButton->boundingRect());
	tipButton->update(tipButton->boundingRect());
	passButton->update(passButton->boundingRect());
	//更新界面
	CentreControl::getInstance()->updateScene();
}

void MyControl::tip(){
	CardType type = CardUtil::getCardType(CentreControl::getInstance()->preCardList);
	QList<int> list = CardUtil::getOvercome(myCardList,CentreControl::getInstance()->preCardList,type,false);
	for(int i=0;i<list.size();i++){
		int var = list.takeAt(i);
		CardItem * item = myCardList.at(var);
		item->move();
		myHandCardMap.insert(QString::number(item->CardNum)+item->cardType,item);
	}
	//更新界面
	CentreControl::getInstance()->updateScene();
}

/**
 * 刷新自己所有的牌。
 * @brief MyControl::flashMyCardList
 */
void MyControl::flashMyCardList()
{
    //显示牌
    int x = myCardPos->x()-(95+myCardList.size()*15)/2;
    int y = myCardPos->y();
    for(int i=0;i<myCardList.size();i++){
        CardItem *item = myCardList.value(i);
        item->setPos(QPoint(x+15*i,y));
    }
	CentreControl::getInstance()->updateScene();
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
    if(showCardIndex >= myCardList.size()){
        killTimer(event->timerId());
		emit startGame();
    }else{
        int x = myCardPos->x()-(95+myCardList.size()*15)/2;
        int y = myCardPos->y();
        CardItem *item = myCardList.value(showCardIndex);
        item->setPos(QPoint(x+15*showCardIndex,y));
        connect(item,SIGNAL(onClick(CardItem*)),this,SLOT(cardSelect(CardItem*)));
        CentreControl::getInstance()->addItem(item);

        showCardIndex++;
    }
}

void MyControl::someOneTakeout()
{
    if(CentreControl::getInstance()->handerIndex == 1){
		if(1 == CentreControl::getInstance()->preHanderIndex){     //如果这一局没人能管住我,
			//清理perCardList
			CentreControl::getInstance()->showPreCardList();
		}
        takeoutButton->picShowPos = 0;
        tipButton->picShowPos = 0;
		if(CentreControl::getInstance()->preCardList.size() > 0){
			passButton->picShowPos = 0;		
		}else{
			passButton->picShowPos = 2;
		}
        takeoutButton->update(takeoutButton->boundingRect());
        tipButton->update(tipButton->boundingRect());
        passButton->update(passButton->boundingRect());
    }
}