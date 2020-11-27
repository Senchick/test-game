#ifndef BONUS_H
#define BONUS_H

#include "QGraphicsRectItem"
#include "QObject"
#include <QWidget>
#include <QGraphicsItem>
#include <QTimer>
#include <PlayerState.h>
#include <Widget.h>

class Bonus: public QObject, public QGraphicsItem {

public:
    Bonus(QPair<int, PlayerState> playerState, Widget *widget, QObject *parent = 0);
    ~Bonus();
    int type;
    QPair<int, PlayerState> playerState;
    Widget *widget;

private:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QTimer *deathTimer;

private slots:
    void slotDeathTimer();
    //void keyPressEvent(QKeyEvent * event);

};

#endif // BONUS_H
