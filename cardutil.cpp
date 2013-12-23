#pragma warning(disable: 4819)
#include "cardutil.h"

CardUtil::CardUtil()
{
}
/**
 * @brief CardUtil::lessThan    排序方法
 * @param ci1
 * @param ci2
 * @return
 */
bool CardUtil::lessThan(const CardItem *ci1, const CardItem *ci2)
{
    int cn1 = ci1->CardNum;
    int cn2 = ci2->CardNum;
    if(cn1 == cn2){
        if(ci1->cardType < ci2->cardType){
            return true;
        }
    }else if(((cn1==1 || cn1==2 || cn1==14) && (cn2==1 || cn2==2 || cn2==14))
             || (cn1>2 && cn1<14 && cn2>2 && cn2<14)){
        if(cn1>cn2){
            return true;
        }
        return false;
    }else if((cn1==1 || cn1==2 || cn1==14) && (cn2>2 && cn2<14)){
        return true;
    }else if((cn2==1 || cn2==2 || cn2==14) && (cn1>2 && cn1<14)){
        return false;
    }
    return false;
}
/**
 * @brief CardUtil::sortCardList 排序
 * @param list
 * @return
 */
QList<CardItem *> CardUtil::sortCardList(QList<CardItem *> &list)
{
    qSort(list.begin(), list.end(), lessThan);
    return list;
}
/**
 * @brief CardUtil::dealCard        发牌
 * @param myList
 * @param leftList
 * @param rightList
 */
void CardUtil::dealCard(QList<CardItem *> &myList, QList<CardItem *> &leftList, QList<CardItem *> &rightList, QList<CardItem *> &bottomList)
{
    QList<CardItem *> itemList = makeAllCard();
    for(int i=0;i<17;i++){
        qsrand(QTime::currentTime().msec());
        int index = qrand()%(itemList.size());
        CardItem *item = itemList.takeAt(index);
        item->isFront = true;
        myList.append(item);

        qsrand(QTime::currentTime().msec());
        index = qrand()%(itemList.size());
        item = itemList.takeAt(index);
        leftList.append(item);

        qsrand(QTime::currentTime().msec());
        index = qrand()%(itemList.size());
        item = itemList.takeAt(index);
        rightList.append(item);
    }
    bottomList = itemList;
}
/**
 * @brief CardUtil::makeAllCard 生成所有54张牌。
 * @return
 */
QList<CardItem *> CardUtil::makeAllCard()
{
    QList<CardItem *> itemList;
    for(int i=0;i<13;i++){
        CardItem *itema = new CardItem();
        itema->fkPic = QPixmap(":images/image/" + QString::number(i+1) + "a.png");
        itema->CardNum = i+1;
        itema->cardType = "a";
        itema->setSelected(true);
        itemList.append(itema);

        CardItem *itemb = new CardItem();
        itemb->fkPic = QPixmap(":images/image/" + QString::number(i+1) + "b.png");
        itemb->CardNum = i+1;
        itemb->cardType = "b";
        itemb->setSelected(true);
        itemList.append(itemb);

        CardItem *itemc = new CardItem();
        itemc->fkPic = QPixmap(":images/image/" + QString::number(i+1) + "c.png");
        itemc->CardNum = i+1;
        itemc->cardType = "c";
        itemc->setSelected(true);
        itemList.append(itemc);

        CardItem *itemd = new CardItem();
        itemd->fkPic = QPixmap(":images/image/" + QString::number(i+1) + "d.png");
        itemd->CardNum = i+1;
        itemd->cardType = "d";
        itemd->setSelected(true);
        itemList.append(itemd);
    }
    CardItem *itema = new CardItem();
    itema->fkPic = QPixmap(":images/image/a.png");
    itema->CardNum = 14;
    itema->cardType = "a";
    itema->setSelected(true);
    itemList.append(itema);

    CardItem *itemb = new CardItem();
    itemb->fkPic = QPixmap(":images/image/b.png");
    itemb->CardNum = 14;
    itemb->cardType = "b";
    itemb->setSelected(true);
    itemList.append(itemb);
    return itemList;
}

/**
* 判断牌是否为单
* @param myCards 牌的集合
* @return 如果为单，返回true；否则，返回false。
*/
bool CardUtil::isDan(QList<CardItem *> myCards) {
    // 默认不是单
    bool flag = false;
    if (myCards.size() == 1) {
        flag = true;
    }
    return flag;
}

/**
* 判断牌是否为对子
* @param myCards 牌的集合
* @return 如果为对子，返回true；否则，返回false。
*/
bool CardUtil::isDuiZi(QList<CardItem *> myCards) {
    // 默认不是对子
    bool flag = false;
    if (myCards.size() == 2) {
        int grade1 = myCards.at(0)->CardNum;
        int grade2 = myCards.at(1)->CardNum;
        if (grade1 == grade2) {
            flag = true;
        }
    }
    return flag;
}
/** 判断牌是否为3带1
* @param myCards 牌的集合
* @return 如果为3带1，被带牌的位置，0或3，否则返回-1。炸弹返回-1。
*/
int CardUtil::isSanDaiYi(QList<CardItem *> myCards) {
    int flag = -1;
    // 默认不是3带1
    if (myCards.size() == 4) {
        // 对牌进行排序
        qSort(myCards.begin(),myCards.end(),lessThan);
        int grades[4] = {0};
        grades[0] = myCards.at(0)->CardNum;
        grades[1] = myCards.at(1)->CardNum;
        grades[2] = myCards.at(2)->CardNum;
        grades[3] = myCards.at(3)->CardNum;
        // 暂时认为炸弹不为3带1
        if ((grades[1] == grades[0]) && (grades[2] == grades[0])
                && (grades[3] == grades[0])) {
            return -1;
        }
        // 3带1，被带的牌在牌头
        else if ((grades[1] == grades[0] && grades[2] == grades[0])) {
            return 0;
        }
        // 3带1，被带的牌在牌尾
        else if (grades[1] == grades[3] && grades[2] == grades[3]) {
            return 3;
        }
    }
    return flag;
}
/**
* 判断牌是否为3不带
* @param myCards 牌的集合
* @return 如果为3不带，返回true；否则，返回false。
*/
bool CardUtil::isSanBuDai(QList<CardItem *> myCards) {
    // 默认不是3不带
    bool flag = false;
    if (myCards.size() == 3) {
        int grade0 = myCards.at(0)->CardNum;
        int grade1 = myCards.at(1)->CardNum;
        int grade2 = myCards.at(2)->CardNum;
        if (grade0 == grade1 && grade2 == grade0) {
            flag = true;
        }
    }
    return flag;
}
/**
* 判断牌是否为顺子
* @param myCards 牌的集合
* @return 如果为顺子，返回true；否则，返回false。
*/
bool CardUtil::isShunZi(QList<CardItem *> myCards) {
    // 默认是顺子
    bool flag = true;
    int size = myCards.size();
    // 顺子牌的个数在5到12之间
    if (size < 5 || size > 12) {
        return false;
    }
    // 对牌进行排序
    qSort(myCards.begin(),myCards.end(),lessThan);
    for (int n = 0; n < size - 1; n++) {
        int prev = myCards.at(n)->CardNum;
        int next = myCards.at(n + 1)->CardNum;
        // 小王、大王、2不能加入顺子
        if (prev == 17 || prev == 16 || prev == 15 || next == 17
                || next == 16 || next == 15) {
            flag = false;
            break;
        } else {
            if (prev - next != -1) {
                flag = false;
                break;
            }
        }
    }
    return flag;
}
/**
     * 判断牌是否为炸弹
     * @param myCards 牌的集合
     * @return 如果为炸弹，返回true；否则，返回false。
     */
bool CardUtil::isZhaDan(QList<CardItem *> myCards) {
    // 默认不是炸弹
    bool flag = false;
    if (myCards.size() == 4) {
        int grades[4] = {0};
        grades[0] = myCards.at(0)->CardNum;
        grades[1] = myCards.at(1)->CardNum;
        grades[2] = myCards.at(2)->CardNum;
        grades[3] = myCards.at(3)->CardNum;
        if ((grades[1] == grades[0]) && (grades[2] == grades[0])
                && (grades[3] == grades[0])) {
            flag = true;
        }
    }
    return flag;
}
/**
   * 判断牌是否为王炸
   * @param myCards 牌的集合
   * @return 如果为王炸，返回true；否则，返回false。
   */
bool CardUtil::isDuiWang(QList<CardItem *> myCards) {
    // 默认不是对王
    bool flag = false;
    if (myCards.size() == 2) {
        int gradeOne = myCards.at(0)->CardNum;
        int gradeTwo = myCards.at(1)->CardNum;
        // 只有小王和大王的等级之后才可能是33
        if (gradeOne + gradeTwo == 33) {
            flag = true;
        }
    }
    return flag;
}
/**
* 判断牌是否为连对
* @param myCards 牌的集合
* @return 如果为连对，返回true；否则，返回false。
*/
bool CardUtil::isLianDui(QList<CardItem *> myCards) {
    // 默认是连对
    bool flag = true;
    int size = myCards.size();
    if (size < 6 || size % 2 != 0) {
        flag = false;
    } else {
        // 对牌进行排序
        qSort(myCards.begin(),myCards.end(),lessThan);
        for (int i = 0; i < size; i = i + 2) {
            if (myCards.at(i)->CardNum != myCards.at(i + 1)->CardNum) {
                flag = false;
                break;
            }
            if (i < size - 2) {
                if (myCards.at(i)->CardNum - myCards.at(i + 2)->CardNum != -1) {
                    flag = false;
                    break;
                }
            }
        }
    }
    return flag;
}
/**
* 判断牌是否为飞机
* @param myCards 牌的集合
* @return 如果为飞机，返回true；否则，返回false。
*/
bool CardUtil::isFeiJi(QList<CardItem *> myCards) {
    bool flag = false;
    // 默认不是单
    int size = myCards.size();
    if (size >= 6) {
        // 对牌进行排序
        qSort(myCards.begin(),myCards.end(),lessThan);
        if (size % 3 == 0 && size % 4 != 0) {
            flag = isFeiJiBuDai(myCards);
        } else if (size % 3 != 0 && size % 4 == 0) {
            flag = isFeiJiDai(myCards);
        } else if (size == 12) {
            flag = isFeiJiBuDai(myCards) || isFeiJiDai(myCards);
        }
    }
    return flag;
}
/**
  * 判断牌是否为飞机不带
  * @param myCards 牌的集合
  * @return 如果为飞机不带，返回true；否则，返回false。
  */
bool CardUtil::isFeiJiBuDai(QList<CardItem *> myCards) {
    int size = myCards.size();
    int n = size/3;
    int grades[30] = {0};
    if (size % 3 != 0) {
        return false;
    } else {
        for (int i = 0; i < n; i++) {
            QList<CardItem *> tempList;
            tempList.append(myCards.at(i*3));
            tempList.append(myCards.at(i*3+1));
            tempList.append(myCards.at(i*3+2));
            if (!isSanBuDai(tempList)) {
                return false;
            } else {
                // 如果连续的3张牌是一样的，记录其中一张牌的grade
                grades[i] = myCards.at(i * 3)->CardNum;
            }
        }
    }
    for (int i = 0; i < n - 1; i++) {
        if (grades[i] == 15) {// 不允许出现2
            return false;
        }
        if (grades[i + 1] - grades[i] != 1) {
            return false;// grade必须连续,如 333444
        }
    }
    return true;
}
/**
* 判断牌是否为飞机带
* @param myCards 牌的集合
* @return 如果为飞机带，返回true；否则，返回false。
*/
bool CardUtil::isFeiJiDai(QList<CardItem *> myCards) {
    int size = myCards.size();
    int n = size / 4;// 此处为“除”，而非取模
    int i = 0;
    for (i = 0; i + 2 < size; i = i + 3) {
        int grade1 = myCards.at(i)->CardNum;
        int grade2 = myCards.at(i + 1)->CardNum;
        int grade3 = myCards.at(i + 2)->CardNum;
        if (grade1 == grade2 && grade3 == grade1) {
            // return isFeiJiBuDai(myCards.subList(i, i + 3 *
            // n));8张牌时，下标越界,subList不能取到最后一个元素
            QList<CardItem *> cards;
            for (int j = i; j < i + 3 * n; j++) {// 取字串
                cards.append(myCards.at(j));
            }
            return isFeiJiBuDai(cards);
        }
    }
    return false;
}
/**
   * 判断牌是否为4带2
   * @param myCards 牌的集合
   * @return 如果为4带2，返回true；否则，返回false。
   */
bool CardUtil::isSiDaiEr(QList<CardItem *> myCards) {
    bool flag = false;
    if (myCards.size() == 6) {
        // 对牌进行排序
        qSort(myCards.begin(),myCards.end(),lessThan);
        for (int i = 0; i < 3; i++) {
            int grade1 = myCards.at(i)->CardNum;
            int grade2 = myCards.at(i + 1)->CardNum;
            int grade3 = myCards.at(i + 2)->CardNum;
            int grade4 = myCards.at(i + 3)->CardNum;
            if (grade2 == grade1 && grade3 == grade1 && grade4 == grade1) {
                flag = true;
            }
        }
    }
    return flag;
}


/**
* 比较我的牌和上家的牌的大小，决定是否可以出牌
* @param myCards 我想出的牌
* @param myCardType 我的牌的类型
* @param prevCards 上家的牌
* @param prevCardType 上家的牌型
* @return 可以出牌，返回true；否则，返回false。
*/
bool CardUtil::isOvercomePrev(QList<CardItem *> myCards, CardType myCardType, QList<CardItem *> prevCards, CardType prevCardType) {
    // 上一首牌的个数
    int prevSize = prevCards.size();
    int mySize = myCards.size();

    // 我先出牌，上家没有牌
    if (prevSize == 0 && mySize != 0) {
        return true;
    }

    // 集中判断是否王炸，免得多次判断王炸
    if (prevCardType == WANG_ZHA) {
        qDebug("上家王炸，肯定不能出。");
        return false;
    } else if (myCardType == WANG_ZHA) {
        qDebug("我王炸，肯定能出。");
        return true;
    }

    // 集中判断对方不是炸弹，我出炸弹的情况
    if (prevCardType != ZHA_DAN && myCardType == ZHA_DAN) {
        return true;
    }

    // 默认情况：上家和自己想出的牌都符合规则
    qSort(prevCards.begin(),prevCards.end(),lessThan);
    qSort(myCards.begin(),myCards.end(),lessThan);

    int myGrade = myCards.at(0)->CardNum;
    int prevGrade = prevCards.at(0)->CardNum;

    // 比较2家的牌，主要有2种情况，1.我出和上家一种类型的牌，即对子管对子；
    // 2.我出炸弹，此时，和上家的牌的类型可能不同
    // 王炸的情况已经排除

    // 单
    if (prevCardType == DAN && myCardType == DAN) {
        // 一张牌可以大过上家的牌
        return myGrade>prevGrade;
    }
    // 对子
    else if (prevCardType == DUI_ZI
             && myCardType == DUI_ZI) {
        // 2张牌可以大过上家的牌
        return myGrade>prevGrade;

    }
    // 3不带
    else if (prevCardType == SAN_BU_DAI
             && myCardType == SAN_BU_DAI) {
        // 3张牌可以大过上家的牌
        return myGrade>prevGrade;
    }
    // 炸弹
    else if (prevCardType == ZHA_DAN
             && myCardType == ZHA_DAN) {
        // 4张牌可以大过上家的牌
        return myGrade>prevGrade;

    }
    // 3带1
    else if (prevCardType == SAN_DAI_YI
             && myCardType == SAN_DAI_YI) {

        // 3带1只需比较第2张牌的大小
        myGrade = myCards.at(1)->CardNum;
        prevGrade = prevCards.at(1)->CardNum;
        return myGrade>prevGrade;

    }
    // 4带2
    else if (prevCardType == SI_DAI_ER
             && myCardType == SI_DAI_ER) {

        // 4带2只需比较第3张牌的大小
        myGrade = myCards.at(2)->CardNum;
        prevGrade = prevCards.at(2)->CardNum;

    }
    // 顺子
    else if (prevCardType == SHUN_ZI
             && myCardType == SHUN_ZI) {
        if (mySize != prevSize) {
            return false;
        } else {
            // 顺子只需比较最大的1张牌的大小
            myGrade = myCards.at(mySize - 1)->CardNum;
            prevGrade = prevCards.at(prevSize - 1)->CardNum;
            return myGrade > prevGrade;
        }

    }
    // 连对
    else if (prevCardType == LIAN_DUI
             && myCardType == LIAN_DUI) {
        if (mySize != prevSize) {
            return false;
        } else {
            // 顺子只需比较最大的1张牌的大小
            myGrade = myCards.at(mySize - 1)->CardNum;
            prevGrade = prevCards.at(prevSize - 1)->CardNum;
            return myGrade>prevGrade;
        }

    }
    // 飞机
    else if (prevCardType == FEI_JI
             && myCardType == FEI_JI) {
        if (mySize != prevSize) {
            return false;
        } else {
            // 顺子只需比较第5张牌的大小(特殊情况333444555666没有考虑，即12张的飞机，可以有2种出法)
            myGrade = myCards.at(4)->CardNum;
            prevGrade = prevCards.at(4)->CardNum;
            return myGrade>prevGrade;
        }
    }
    // 默认不能出牌
    return false;
}

/**
* 判断我所有的牌中，是否存在能够管住上家的牌，决定出牌按钮是否显示
* @param myCards 我所有的牌 *
* @param prevCards 上家的牌
* @param prevCardType 上家牌的类型
* @return 可以出牌，返回true；否则，返回false。
*/
bool CardUtil::isOvercomePrev(QList<CardItem *> myCards,
    QList<CardItem *> prevCards, CardType prevCardType) {
    // 默认情况：上家和自己想出的牌都符合规则
    qSort(prevCards.begin(),prevCards.end(),lessThan);
    qSort(myCards.begin(),myCards.end(),lessThan);
    // 上一首牌的个数
    int prevSize = prevCards.size();
    int mySize = myCards.size();

    // 我先出牌，上家没有牌
    if (prevSize == 0 && mySize != 0) {
        return true;
    }

    //如果对方为王炸，不能出牌。
    if (prevCardType == WANG_ZHA) {
        qDebug("上家王炸，肯定不能出。");
        return false;
    }
    //如果我有王炸，可以出牌。
    if (mySize >= 2) {
        QList<CardItem *> cards;
        cards.append(myCards.at(0));
        cards.append(myCards.at(1));
        if (isDuiWang(cards)) {
            return true;
        }
    }

    // 集中判断对方不是炸弹，我出炸弹的情况
    if (prevCardType != ZHA_DAN) {
        if (mySize < 4) {
            return false;
        } else {
            for (int i = 0; i < mySize - 3; i++) {
                int grade0 = myCards.at(i)->CardNum;
                int grade1 = myCards.at(i + 1)->CardNum;
                int grade2 = myCards.at(i + 2)->CardNum;
                int grade3 = myCards.at(i + 3)->CardNum;
                if (grade1 == grade0 && grade2 == grade0
                        && grade3 == grade0) {
                    return true;
                }
            }
        }
    }
    int prevGrade = prevCards.at(0)->CardNum;
    // 比较2家的牌，主要有2种情况，1.我出和上家一种类型的牌，即对子管对子；
    // 2.我出炸弹，此时，和上家的牌的类型可能不同
    // 王炸的情况已经排除

    // 上家出单
    if (prevCardType == DAN) {
        // 一张牌可以大过上家的牌
        for (int i = mySize - 1; i >= 0; i--) {
            int grade = myCards.at(i)->CardNum;
            if (grade > prevGrade) {
                // 只要有1张牌可以大过上家，则返回true
                return true;
            }
        }

    }
    // 上家出对子
    else if (prevCardType == DUI_ZI) {
        // 2张牌可以大过上家的牌
        for (int i = mySize - 1; i >= 1; i--) {
            int grade0 = myCards.at(i)->CardNum;
            int grade1 = myCards.at(i - 1)->CardNum;

            if (grade0 == grade1) {
                if (grade0 > prevGrade) {
                    // 只要有1对牌可以大过上家，则返回true
                    return true;
                }
            }
        }

    }
    // 上家出3不带
    else if (prevCardType == SAN_BU_DAI) {
        // 3张牌可以大过上家的牌
        for (int i = mySize - 1; i >= 2; i--) {
            int grade0 = myCards.at(i)->CardNum;
            int grade1 = myCards.at(i - 1)->CardNum;
            int grade2 = myCards.at(i - 2)->CardNum;

            if (grade0 == grade1 && grade0 == grade2) {
                if (grade0 > prevGrade) {
                    // 只要3张牌可以大过上家，则返回true
                    return true;
                }
            }
        }

    }
    // 上家出3带1
    else if (prevCardType == SAN_DAI_YI) {
        // 3带1 3不带 比较只多了一个判断条件
        if (mySize < 4) {
            return false;
        }

        // 3张牌可以大过上家的牌
        for (int i = mySize - 1; i >= 2; i--) {
            int grade0 = myCards.at(i)->CardNum;
            int grade1 = myCards.at(i - 1)->CardNum;
            int grade2 = myCards.at(i - 2)->CardNum;

            if (grade0 == grade1 && grade0 == grade2) {
                if (grade0 > prevGrade) {
                    // 只要3张牌可以大过上家，则返回true
                    return true;
                }
            }
        }

    }
    // 上家出炸弹
    else if (prevCardType == ZHA_DAN) {
        // 4张牌可以大过上家的牌
        for (int i = mySize - 1; i >= 3; i--) {
            int grade0 = myCards.at(i)->CardNum;
            int grade1 = myCards.at(i - 1)->CardNum;
            int grade2 = myCards.at(i - 2)->CardNum;
            int grade3 = myCards.at(i - 3)->CardNum;

            if (grade0 == grade1 && grade0 == grade2 && grade0 == grade3) {
                if (grade0 > prevGrade) {
                    // 只要有4张牌可以大过上家，则返回true
                    return true;
                }
            }
        }

    }
    // 上家出4带2
    else if (prevCardType == SI_DAI_ER) {
        // 4张牌可以大过上家的牌
        for (int i = mySize - 1; i >= 3; i--) {
            int grade0 = myCards.at(i)->CardNum;
            int grade1 = myCards.at(i - 1)->CardNum;
            int grade2 = myCards.at(i - 2)->CardNum;
            int grade3 = myCards.at(i - 3)->CardNum;

            if (grade0 == grade1 && grade0 == grade2 && grade0 == grade3) {
                // 只要有炸弹，则返回true
                return true;
            }
        }
    }
    // 上家出顺子
    else if (prevCardType == SHUN_ZI) {
        if (mySize < prevSize) {
            return false;
        } else {
            for (int i = mySize - 1; i >= prevSize - 1; i--) {
                QList<CardItem *> cards;
                for (int j = 0; j < prevSize; j++) {
                    cards.append(myCards.at(i - j));
                }
                CardType myCardType = getCardType(cards);
                if (myCardType == SHUN_ZI) {
                    int myGrade2 = cards.at(cards.size()-1)->CardNum;// 最大的牌在最后
                    int prevGrade2 = prevCards.at(prevSize - 1)->CardNum;// 最大的牌在最后

                    if (myGrade2 > prevGrade2) {
                        return true;
                    }
                }
            }
        }

    }
    // 上家出连对
    else if (prevCardType == LIAN_DUI) {
        if (mySize < prevSize) {
            return false;
        } else {
            for (int i = mySize - 1; i >= prevSize - 1; i--) {
                QList<CardItem *> cards;
                for (int j = 0; j < prevSize; j++) {
                    cards.append(myCards.at(i - j));
                }

                CardType myCardType = getCardType(cards);
                if (myCardType == LIAN_DUI) {
                    int myGrade2 = cards.at(cards.size()-1)->CardNum;// 最大的牌在最后,getCardType会对列表排序
                    int prevGrade2 = prevCards.at(prevSize - 1)->CardNum;// 最大的牌在最后

                    if (myGrade2 > prevGrade2) {
                        return true;
                    }
                }
            }
        }

    }
    // 上家出飞机
    else if (prevCardType == FEI_JI) {
        if (mySize < prevSize) {
            return false;
        } else {
            for (int i = mySize - 1; i >= prevSize - 1; i--) {
                QList<CardItem *> cards;
                for (int j = 0; j < prevSize; j++) {
                    cards.append(myCards.at(i - j));
                }

                CardType myCardType = getCardType(cards);
                if (myCardType == FEI_JI) {
                    int myGrade4 = cards.at(4)->CardNum; //
                    int prevGrade4 = prevCards.at(4)->CardNum;//

                    if (myGrade4 > prevGrade4) {
                        return true;
                    }
                }
            }
        }
    }
    // 默认不能出牌
    return false;
}
/**
 * 判断拍的类型
 * @brief CardUtil::getCardType
 * @param myCards
 * @return
 */
CardType CardUtil::getCardType(QList<CardItem *> myCards) {
    CardType cardType;
    // 大概率事件放前边，提高命中率
    if (isDan(myCards)) {
        cardType = DAN;
    } else if (isDuiWang(myCards)) {
        cardType = WANG_ZHA;
    } else if (isDuiZi(myCards)) {
        cardType = DUI_ZI;
    } else if (isZhaDan(myCards)) {
        cardType = ZHA_DAN;
    } else if (isSanDaiYi(myCards) != -1) {
        cardType = SAN_DAI_YI;
    } else if (isSanBuDai(myCards)) {
        cardType = SAN_BU_DAI;
    } else if (isShunZi(myCards)) {
        cardType = SHUN_ZI;
    } else if (isLianDui(myCards)) {
        cardType = LIAN_DUI;
    } else if (isSiDaiEr(myCards)) {
        cardType = SI_DAI_ER;
    } else if (isFeiJi(myCards)) {
        cardType = FEI_JI;
    }
    return cardType;
}
