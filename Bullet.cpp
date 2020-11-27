#include "Bullet.h"
#include "math.h"
#include "QTimer"
#include "QGraphicsScene"
#include "QDebug"
#include "Enemy.h"
#include "Bonus.h"



static qreal normalizeAngle(qreal angle)
{
    while (angle < 0)
        angle += M_PI * 2;
    while (angle > M_PI * 2)
        angle -= M_PI * 2;
    return angle;
}

Bullet::Bullet(QPointF start, QPointF end, int damageBullet, int speedBullet, QObject *parent)
    : QObject(parent), QGraphicsItem()
{
    damage = damageBullet;
    speed = speedBullet;


    this->setRotation(0);
    this->setPos(start);
    this->setZValue(-1);

    QLineF lineToTarget(start, end);
    qreal angleToTarget = ::acos(lineToTarget.dx() / lineToTarget.length());
    if (lineToTarget.dy() < 0)
        angleToTarget = M_PI * 2 - angleToTarget;
    angleToTarget = normalizeAngle((M_PI - angleToTarget) + M_PI / 2);


    if (angleToTarget >= 0 && angleToTarget <= M_PI) {
        setRotation(rotation() - angleToTarget * 180 /M_PI);
    } else if (angleToTarget <= M_PI * 2 && angleToTarget > M_PI) {
        setRotation(rotation() + (angleToTarget - M_PI * 2 )* (-180) /M_PI);
    }
    timerBullet = new QTimer();
    connect(timerBullet, &QTimer::timeout, this, &Bullet::slotTimerBullet);
    timerBullet->start(speed);
}

QRectF Bullet::boundingRect() const
{
    return QRectF(0,0,2,4);
}

void Bullet::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(Qt::black);
    painter->setBrush(Qt::black);
    painter->drawRect(0,0,2,4);

    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void Bullet::move() {
    setPos(mapToParent(0, -10));
}

void Bullet::slotTimerBullet()
{
    move();

    QList<QGraphicsItem *> foundItems = scene()->items(
        QPolygonF() << mapToScene(0, 0) << mapToScene(-1, -1)<< mapToScene(1, -1)
    );
    for (auto item : foundItems) {
        if (dynamic_cast<Enemy*>(item) == nullptr)
            continue;
        Enemy *enemy = static_cast<Enemy*>(item);
        enemy->hit(damage);
        this->deleteLater();
    }


    if(x() < 0 || x() > scene()->width() || y() < 0 || y() > scene()->height()){
        this->deleteLater();      
    }

}

Bullet::~Bullet()
{
   // scene()->removeItem(this);
    //delete this;
    delete timerBullet;
}
