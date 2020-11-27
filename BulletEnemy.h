#ifndef BULLETENEMY_H
#define BULLETENEMY_H

#include <Bullet.h>


class BulletEnemy: public Bullet
{
public:
    BulletEnemy(QPointF start, QPointF end, int damageBullet = 1, int speedBullet = 50,  QObject *parent = 0) :
        Bullet(start, end, damageBullet, speedBullet, parent ) {}

private slots:
    void slotTimerBullet() override;
};

#endif // BULLETENEMY_H
