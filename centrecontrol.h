#ifndef CENTRECONTROL_H
#define CENTRECONTROL_H
#include <QMainWindow>
#include <QMutex>
#include <QMutexLocker>
#include <QDebug>
#include <QGraphicsScene>
#include "userthread.h"
#include "jokerview.h"
#include "buttonitem.h"
class CentreControl : public QMainWindow
{
    Q_OBJECT
public:
    static CentreControl* getInstance(QWidget *parent = 0)
    {
        static QMutex mutex;
        if (!m_instance) {
            QMutexLocker locker(&mutex);
            if (!m_instance)
                m_instance = new CentreControl(parent);
        }
        return m_instance;
    }
private:
    CentreControl(QWidget *parent = 0);
    void nextHander();

public:
    void addItem(QGraphicsItem *item);
    void removeItem(QGraphicsItem *item);
    void updateScene();
    void showPreCardList(QList<CardItem*> &preCardList);
    ~CentreControl(void);

public:
    int handerIndex;
    QList<CardItem*> preCardList;
    UserThread *leftUser;
    UserThread *rightUser;

private:
    static CentreControl* m_instance;
    JokerView *view;
    QGraphicsScene *scene;
    ButtonItem * startButton;
    int master;
signals:
    void startGame(QList<CardItem*> itemList);
    void someOneTakeout();
public slots:
    void startButtonClicked();
    void takeouted();
};

#endif // CENTRECONTROL_H
