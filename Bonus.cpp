#include "Bonus.h"
#include "QPainter"

static int randomBetween(int low, int high)
{
    return (rand() % ((high + 1) - low) + low);
}

Bonus::Bonus(QPair<int, PlayerState> p, Widget *w, QObject *parent)
    : QObject(parent), QGraphicsItem() {
    playerState = p;
    widget = w;

    deathTimer = new QTimer();
    connect(deathTimer, &QTimer::timeout, this, &Bonus::slotDeathTimer);
    deathTimer->start(randomBetween(3000, 10000));

    setPos(randomBetween(20, 760), randomBetween(360, 540));
}

QRectF Bonus::boundingRect() const
{
    return QRectF(0,0,20,20);
}

void Bonus::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    /* Отрисовываем зеленый квадрат
     * */
    painter->setPen(Qt::black);
    painter->setBrush(Qt::green);
    painter->drawRect(0,0,20,20);

    /* Отрисовываем полоску жизни
     * соизмеримо текущему здоровью
     * относительно максимального здоровья
     * */

    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void Bonus::slotDeathTimer()
{
    delete this;
}

Bonus::~Bonus() {
    delete deathTimer;
}
