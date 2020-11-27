#ifndef BULLET_H
#define BULLET_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>

class Bullet: public QObject, public QGraphicsItem {

public:
    Bullet(QPointF start, QPointF end, int damageBullet = 1, int speedBullet = 7, QObject *parent = 0);
    ~Bullet();
    int damage;
    int speed;
    void move();

private:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QTimer *timerBullet;




private slots:
    virtual void slotTimerBullet();
};


#endif // BULLET_H
