#ifndef CENTRECONTROL_H
#define CENTRECONTROL_H
#include <QtWidgets/QMainWindow>
#include <QtCore/QMutex>
#include <QtCore/QMutexLocker>
#include <QtCore/QDebug>
#include <QtWidgets/QGraphicsScene>
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
	void showPreCardList(QList<CardItem*> &cardList);
};

#endif // CENTRECONTROL_H
