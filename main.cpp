#include <QtWidgets/QApplication>
#include <QtCore/QObject>
#include "centrecontrol.h"
#include "mycontrol.h"
#include <vld.h> 
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MyControl c;
    CentreControl *cc = CentreControl::getInstance();
    QObject::connect(cc,SIGNAL(initGame(QList<CardItem*>)),&c,SLOT(initGame(QList<CardItem*>)));
	QObject::connect(&c,SIGNAL(startGame()),cc,SLOT(startGame()));
    QObject::connect(cc,SIGNAL(someOneTakeout()),&c,SLOT(someOneTakeout()));
    QObject::connect(&c,SIGNAL(takeouted()),cc,SLOT(takeouted()));
    cc->show();
	return a.exec();
}
