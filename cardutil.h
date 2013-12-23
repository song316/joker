#ifndef CARDUTIL_H
#define CARDUTIL_H
#include "carditem.h"
#include <QList>
#include <QTime>
enum CardType{
    DAN,DUI_ZI,ZHA_DAN,
    SAN_DAI_YI,SAN_BU_DAI,SHUN_ZI,
    LIAN_DUI,SI_DAI_ER,FEI_JI,WANG_ZHA
};

class CardUtil
{
public:
    CardUtil();
    static bool lessThan(const CardItem *ci1, const CardItem *ci2);
    static QList<CardItem *> makeAllCard();
    static QList<CardItem *> sortCardList(QList<CardItem *> &list);
    static void dealCard(QList<CardItem *> &myList,QList<CardItem *> &leftList,QList<CardItem *> &rightList, QList<CardItem *> &bottomList);
    static bool isDan(QList<CardItem *> myCards);
    static bool isDuiZi(QList<CardItem *> myCards);
    static int isSanDaiYi(QList<CardItem *> myCards);
    static bool isSanBuDai(QList<CardItem *> myCards);
    static bool isShunZi(QList<CardItem *> myCards);
    static bool isZhaDan(QList<CardItem *> myCards);
    static bool isDuiWang(QList<CardItem *> myCards);
    static bool isLianDui(QList<CardItem *> myCards);
    static bool isFeiJi(QList<CardItem *> myCards);
    static bool isFeiJiBuDai(QList<CardItem *> myCards);
    static bool isFeiJiDai(QList<CardItem *> myCards);
    static bool isSiDaiEr(QList<CardItem *> myCards);
    static bool isOvercomePrev(QList<CardItem *> myCards,CardType myCardType,
                               QList<CardItem *> prevCards, CardType prevCardType);
    static bool isOvercomePrev(QList<CardItem *> myCards,
                               QList<CardItem *> prevCards, CardType prevCardType);
    static CardType getCardType(QList<CardItem *> myCards);
};

#endif // CARDUTIL_H
