#ifndef ENEMY_H
#define ENEMY_H

#include "QGraphicsRectItem"
#include "QObject"
#include <QWidget>
#include <QGraphicsItem>
#include <Player.h>
#include <EnemySlot.h>
#include <Widget.h>

class Enemy: public QObject, public QGraphicsItem {

public:
    Enemy(Player *player, Widget *widget, QPair<int, EnemySlot> enemySlotValid, int type = 0,  QObject *parent = 0);
    ~Enemy();
    void hit(int damage);
    int type = 0;
    QPair<int, EnemySlot> enemySlotValid;

private:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QTimer *timerEnemy;
    Player *player;
    Widget *widget;
    int hp;
    int maxHp;
    int firingType = 0;
    int rof;




private slots:
    void slotTimerEnemy();


    //void keyPressEvent(QKeyEvent * event);

};

#endif // ENEMY_H
