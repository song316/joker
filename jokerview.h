#ifndef JOKER_H
#define JOKER_H

#include <QGraphicsView>

class JokerView : public QGraphicsView
{
    Q_OBJECT

public:
    JokerView(QWidget *parent = 0);
    ~JokerView();
    void init();
};

#endif // JOKER_H
