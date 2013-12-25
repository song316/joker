#ifndef JOKERVIEW_H
#define JOKERVIEW_H

#include <QGraphicsView>

class JokerView : public QGraphicsView
{
    Q_OBJECT

public:
    JokerView(QWidget *parent = 0);
    ~JokerView();
    void init();
};

#endif // JOKERVIEW_H
