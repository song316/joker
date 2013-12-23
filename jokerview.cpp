#include "jokerview.h"

JokerView::JokerView(QWidget *parent): QGraphicsView(parent)
{
    setRenderHint(QPainter::Antialiasing);
    setFixedSize(1000,700);
}


JokerView::~JokerView(void)
{
}

void JokerView::init()
{

}
