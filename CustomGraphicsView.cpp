#include "CustomGraphicsView.h"
#include <QKeyEvent>

void CustomGraphicsView::keyPressEvent(QKeyEvent *event) {
    keysPressed += event->key();
}

void CustomGraphicsView::keyReleaseEvent(QKeyEvent *event) {
    keysPressed -= event->key();
}

void CustomGraphicsView::mouseReleaseEvent(QMouseEvent *event)
{
     keysPressed -= event->button();
}

void CustomGraphicsView::mousePressEvent(QMouseEvent *event)
{
    keysPressed += event->button();
}

void CustomGraphicsView::resizeEvent(QResizeEvent *event)
{
    fitInView(0, 0, scene()->width(), scene()->height());


    QGraphicsView::resizeEvent(event);
}
