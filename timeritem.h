#ifndef TIMERITEM_H
#define TIMERITEM_H
#include <QtGui/QPixmap>
#include <QtWidgets/QGraphicsPixmapItem>
#include <QtCore/QTimerEvent>
class TimerItem : public QGraphicsPixmapItem,public QObject
{
public:
    TimerItem();
    ~TimerItem();
    int timeCount;
    QString pic;
    int imageWidth;
    int imageHight;
    int imageNum;
    void timerEvent(QTimerEvent *event);
    QRectF  boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // TIMERITEM_H
