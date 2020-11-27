#include "BulletEnemy.h"
#include "Player.h"
#include "QGraphicsScene"
#include "QDebug"




void BulletEnemy::slotTimerBullet()
{
    move();

    QList<QGraphicsItem *> foundItems = scene()->items(
        QPolygonF() << mapToScene(0, 0) << mapToScene(-1, -1)<< mapToScene(1, -1)
    );
    for (auto item : foundItems) {
        if (dynamic_cast<Player*>(item) == nullptr)
            continue;
        Player *player = static_cast<Player*>(item);
        player->hit(damage);
        this->deleteLater();
    }


    if(x() < 0 || x() > scene()->width() || y() < 0 || y() > scene()->height()){
        this->deleteLater();
    }
}
