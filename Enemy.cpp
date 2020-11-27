#include "Enemy.h"
#include "QTimer"
#include "QGraphicsScene"
#include "QDebug"
#include "QPainter"
#include "QRandomGenerator"
#include "BulletEnemy.h"



static int randomBetween(int low, int high)
{
    return (rand() % ((high + 1) - low) + low);
}

Enemy::Enemy(Player *p, Widget *w ,QPair<int, EnemySlot> e, int typeEnemy, QObject *parent)
    : QObject(parent), QGraphicsItem()
{

    type = typeEnemy;
    player = p;
    widget = w;
    enemySlotValid = e;

    switch (type) {
        case 0:
            hp = maxHp = 5;
            rof = 5000;
            firingType = 0;
            break;
        case 1:
            hp = maxHp = 15;
            rof = 4000;
            firingType = 0;
            break;
        case 2:
            hp = maxHp = 50;
            rof = 3000;
            firingType = 0;
            break;
    }



    setPos(e.second.slot);

    timerEnemy = new QTimer();
    connect(timerEnemy, &QTimer::timeout, this, &Enemy::slotTimerEnemy);
    timerEnemy->start(rof);
    //qDebug() << firingType;
}

void Enemy::slotTimerEnemy() {
    qreal offset = boundingRect().center().x() + 1;
    switch (firingType) {
        case 0:
            scene()->addItem(new BulletEnemy(QPointF(x() + offset, y()), QPointF(x() + offset, y()+100)));
            break;
        case 1:
            scene()->addItem(new BulletEnemy(QPointF(x() + offset, y()), QPointF(player->x() + player->rect().width() / 2, player->y() + player->rect().height() /2)));
            break;

    }

}

QRectF Enemy::boundingRect() const
{
    return QRectF(-20,-20,40,40);
}

void Enemy::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    /* Отрисовываем зеленый квадрат
     * */
    painter->setPen(Qt::black);
    painter->setBrush(Qt::green);
    painter->drawRect(-20,-10,40,30);

    /* Отрисовываем полоску жизни
     * соизмеримо текущему здоровью
     * относительно максимального здоровья
     * */
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::red);
    painter->drawRect(-20,-17, (int) 40*hp/maxHp,3);

    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void Enemy::hit(int damage)
{
    hp -= damage;   // Уменьшаем здоровье мишени
    this->update(QRectF(-20,-20,40,40));    // Перерисовываем мишень
    // Если здоровье закончилось, то инициируем смерть мишени
    if(hp <= 0) delete this;
}

Enemy::~Enemy()
{
    widget->enemySlots[enemySlotValid.first].empty = true;
    delete timerEnemy;
}
