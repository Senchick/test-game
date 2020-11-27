#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsRectItem>
#include <QObject>
#include <QWidget>
#include <QGraphicsItem>

#include <PlayerState.h>

class Player: public QGraphicsRectItem, public QObject {

public:
    Player(qreal x, qreal y, qreal w, qreal h, QWidget *parent = 0) :
        QGraphicsRectItem (x, y, w, h),
        QObject(parent) {
        //setBrush(Qt::green);
    }
    int hp = 3;
    QMap<int, PlayerState> states;
    void hit(qreal damage);

    //void keyPressEvent(QKeyEvent * event);

};

#endif // PLAYER_H
