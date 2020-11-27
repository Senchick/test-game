#include "Player.h"
#include "Bullet.h"

#include <QKeyEvent>
#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QWidget>
#include <QCursor>
#include <PlayerState.h>

void Player::hit(qreal damage)
{
    hp -= damage;
    if (hp <= 0) {
        qDebug() << "player dead";
    }
}
