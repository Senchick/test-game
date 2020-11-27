#ifndef CUSTOMGRAPHICSVIEW_H
#define CUSTOMGRAPHICSVIEW_H
#include <QGraphicsView>
#include <QObject>
#include <QSet>



class CustomGraphicsView: public QGraphicsView
{
public:
    CustomGraphicsView(QGraphicsScene *parent = nullptr) : QGraphicsView(parent) {};
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void resizeEvent(QResizeEvent *event);
    QSet<int> keysPressed;
};

#endif // CUSTOMGRAPHICSVIEW_H
