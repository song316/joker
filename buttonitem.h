#ifndef BUTTONITEM_H
#define BUTTONITEM_H
#include <QGraphicsObject>
#include <QPainter>
class ButtonItem:
        public QGraphicsObject
{
    Q_OBJECT
public:
    ButtonItem(QGraphicsItem *parent = 0);
    QRectF  boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
public:
    QPixmap pic;
    int picShowPos;
    int picWidth;
    int picHight;
    int picNum;

signals:
    void onClick();
};

#endif // BUTTONITEM_H
