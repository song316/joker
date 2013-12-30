#pragma warning(disable: 4819)
#include "userthread.h"
#include "cardutil.h"
#include "centrecontrol.h"
#include <QSound>
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
        QThread::msleep(3000);
        if(index == CentreControl::getInstance()->handerIndex){     //如果是该我出牌
			if(index == CentreControl::getInstance()->preHanderIndex){     //如果这一局没人能管住我,
				//清理perCardList
				CentreControl::getInstance()->showPreCardList();
			}
			QThread::msleep(3000);
			//出牌
			CardType type = CardUtil::getCardType(CentreControl::getInstance()->preCardList);
			QList<int> list = CardUtil::getOvercome(myCardList,CentreControl::getInstance()->preCardList,type,false);
			if(list.size() > 0){
				for(int i=0;i<list.size();i++){
					int var = list.takeAt(i);
					CardItem * item = myCardList.takeAt(var);
					item->isFront = true;
					CentreControl::getInstance()->removeItem(item);
					CentreControl::getInstance()->newPreCardList.append(item);
					CentreControl::getInstance()->preHanderIndex = index;
				}
				emit sig_showPreCardList();
				CentreControl::getInstance()->updateScene();
			}else{
				QSound::play(":sounds/sound/pass.wav");
				qDebug() << "pass...........";		
			}
			emit takeouted();
		 }
    }
}

void UserThread::someOneTakeout(){
	
}
