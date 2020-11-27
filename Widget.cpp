#include "Widget.h"
#include <Player.h>
#include <math.h>
#include "Weapon.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Bonus.h"
#include "CustomGraphicsView.h"
#include <PlayerStateDuration.h>

#include <QDebug>
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTimer>
#include <QObject>
#include <QWidget>
#include <QCursor>
#include <QKeyEvent>
#include <QGuiApplication>
#include <QTransform>
#include <QDateTime>

static qreal normalizeAngle(qreal angle)
{
    while (angle < 0)
        angle += M_PI* 2;
    while (angle > M_PI* 2)
        angle -= M_PI* 2;
    return angle;
}

static QMap<int, EnemySlot> randomize(QMap<int, EnemySlot> in) {
    QMap<int, EnemySlot> nl;

    while (in.count() != 0) {
        int index = rand() * in.count();
        int nindex = index;
        bool f = false;
        qDebug() << nl.size();
        qDebug() << in.size();
        while (index + 1 < in.count()) {
            if (!in.contains(index))
                nindex++;
            else {
                f = true;
                nl.insert(nindex, in[nindex]);
                in.remove(nindex);
                break;
            }
        }
        qDebug() << nl.size();
        qDebug() << in.size();
        if (f) continue;
        nindex = index;
        nindex--;
        while (nindex > -1) {
            if (!in.contains(nindex)){
                nindex--;
            } else {
                nl.insert(nindex, in[nindex]);
                in.remove(nindex);
                break;
            }
        }

    }
    qDebug() << nl.size();
    qDebug() << in.size();
}

Widget::Widget(QWidget *parent) : QWidget(parent) {


    setMouseTracking(true);
    resize(sceneWidth, sceneHeight);
    //setFixedSize(sceneWidth, sceneHeight);
    setFocusPolicy( Qt::StrongFocus );


    scene = new QGraphicsScene(this);
    scene->setSceneRect(0, 0, sceneWidth, sceneHeight);



    view = new CustomGraphicsView(scene);
    view->setRenderHint(QPainter::Antialiasing);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->resize(sceneWidth, sceneHeight);

    //view->setFixedSize(sceneWidth, sceneHeight);
    //view->scale(0.5,0.5);
    view->show();

    int count = 0;
    int enemySize = 45;

    for (int i = 0; i < (sceneWidth - (int)sceneWidth % enemySize) / enemySize; i++ ) {
        for (int j = 0; j < (sceneHeight / 2 - 20) / enemySize; j++ ) {
            EnemySlot e;
            e.slot = QPoint(30 + enemySize * i, 20 + enemySize * j);
            enemySlots[count] = e;
            count++;
        }
    }
    defaultPlayerState = PlayerState {-1, -1, -1, 300, 0, 1, 10, 10, false};
    //добавить бонусы, которые можно будет использовать на горячие клавиши
    //int type;int priority = 0;int duration = -1;int rof = 300;int splitBullets = 0;int bulletDamage = 1;int splitAngle = 10;int playerSpeed = 10;bool invert = false;
    listPlayerStates.append(PlayerState {0, 0, 15, 100});
    listPlayerStates.append(PlayerState {0, 1, 10, 50});
    listPlayerStates.append(PlayerState {0, 2, 5, 10});
    listPlayerStates.append(PlayerState {0, 3, 3, 1});
    //std::random_shuffle(enemySlots.begin(), enemySlots.end());

    for(auto ee: enemySlots) {
        qDebug() << ee.slot;
    }
    qDebug() << enemySlots.count();
    //randomize(enemySlots);


    int playerSizeW = 40;
    int playerSizeH = 60;
    int weaponSize = 8;
    player = new Player(0, 0, playerSizeW, playerSizeH);

    player->setPos((sceneWidth -  playerSizeW )/ 2, sceneHeight - playerSizeH - 40);


    weapon = new Weapon(0, 0, weaponSize, playerSizeH);
    weapon->setParentItem(&*player);

    scene->addItem(player);
    weapon->setPos((playerSizeW + weaponSize) / 2, playerSizeH / 2);
    weapon->setRotation(180);

    //target = new QPointF(0, 0);
    //scene->addItem(weapon);

    QCursor cursor = QCursor(QPixmap(":/cursor/cursor.png"));
    view->setCursor(cursor);

    QTimer *timer = new QTimer();
    connect(timer, &QTimer::timeout, this, &Widget::gameTimer);
    timer->start(1000 / 50);

    QTimer *bulletTimer = new QTimer();
    connect(bulletTimer, &QTimer::timeout, this, &Widget::bulletTimer);
    bulletTimer->start(5);

    QTimer *spawnTimer = new QTimer();
    connect(spawnTimer, &QTimer::timeout, this, &Widget::spawnTimer);
    spawnTimer->start(500);

    QTimer *bonusTimer = new QTimer();
    connect(bonusTimer, &QTimer::timeout, this, &Widget::bonusTimer);
    bonusTimer->start(5000);

}
void Widget::bonusTimer()
{
    
    std::random_shuffle(listPlayerStates.begin(), listPlayerStates.end());
    
    
    PlayerState p = listPlayerStates.first();

    scene->addItem(new Bonus(QPair<int, PlayerState>(p.type, p), this));

    //for(auto item: playerStates) {
       // if (item.type == p.type && item.priority > p.priority) {
            

       // }
    //}
}
void Widget::spawnTimer()
{
    auto end = enemySlots.cend();
    for(auto it = enemySlots.cbegin(); it != end; ++it) {
        if (it.value().empty == true) {
            auto *enemy = new Enemy(player, this, QPair<int, EnemySlot>(it.key(), it.value()));
            scene->addItem(enemy);
            enemySlots[it.key()].empty = false;
            break;
        }
    }


}
void Widget::updateState(PlayerState p, bool d = false) {
    if (d) {
       rof = p.rof;
       splitBullets = p.splitBullets;
       bulletDamage = p.bulletDamage;
       splitAngle = p.splitAngle;
       playerSpeed = p.playerSpeed;
       invert = p.invert;
    } else {
        if (p.rof < rof)
            rof = p.rof;
        if (splitBullets < p.splitBullets)
            splitBullets = p.splitBullets;
        if (bulletDamage < p.bulletDamage)
            bulletDamage = p.bulletDamage;
        if (splitAngle > p.splitAngle)
            splitAngle = p.splitAngle;
        if (playerSpeed < p.playerSpeed)
            playerSpeed = p.playerSpeed;
        invert = p.invert;
    }
}

void Widget::gameTimer()
{

    for (auto item: scene->collidingItems(player)) {
        if (dynamic_cast<Bonus*>(item) != nullptr) {
            auto bonus = dynamic_cast<Bonus*>(item);
            auto p = bonus->playerState;
            updateState(p.second);
            new PlayerStateDuration(this, p);
            delete item;
        }
    }


    QPoint p = mapFromGlobal(QCursor::pos());
    QRect r = view->geometry();

    qreal x1 = (p.x() - r.x())  * screenScaleX();
    qreal y1 = (p.y() - r.y())  * screenScaleY();
    //qDebug() << x1 <<" " << y1 << " " << view->rect();



    if(!QGuiApplication::focusWindow() || !r.contains(p))
        return;
    if (!view->keysPressed.empty())
        for (auto key: view->keysPressed) {
            qreal lr = 1.6;
            if (invert) {
                switch (key) {
                    case Qt::Key_Up:
                    case Qt::Key_W:
                        player->setPos(player->mapToParent(0, playerSpeed));
                    break;
                    case Qt::Key_Down:
                    case Qt::Key_S:
                        player->setPos(player->mapToParent(0, -playerSpeed));
                    break;
                    case Qt::Key_Left:
                    case Qt::Key_A:
                        player->setPos(player->mapToParent(playerSpeed, 0));
                    break;
                    case Qt::Key_Right:
                    case Qt::Key_D:
                        player->setPos(player->mapToParent(-playerSpeed, 0));
                    break;
                 }
            } else {
                switch (key) {
                    case Qt::Key_Up:
                    case Qt::Key_W:
                        player->setPos(player->mapToParent(0, -playerSpeed));
                    break;
                    case Qt::Key_Down:
                    case Qt::Key_S:
                        player->setPos(player->mapToParent(0, playerSpeed));
                    break;
                    case Qt::Key_Left:
                    case Qt::Key_A:
                        player->setPos(player->mapToParent(-playerSpeed * lr, 0));
                    break;
                    case Qt::Key_Right:
                    case Qt::Key_D:
                        player->setPos(player->mapToParent(playerSpeed * lr, 0));
                    break;
                 }
            }
        }
    qreal w = width() - player->rect().width();
    qreal h = height() - player->rect().height();

    if (player->x() < 0) player->setX(0);
    if (player->x() > w) player->setX(w);
    if (player->y() - h / 1.5 < 0) player->setY(h / 1.5);
    if (player->y() > h) player->setY(h);


    if(player->x() <= x1 && player->x() + player->rect().width() >= x1 && player->y() <= y1 && player->y() + player->rect().height() >= y1) return;

    qreal weaponWidth = weapon->rect().width() / 2;

    QLineF lineToTarget(QPointF(weaponWidth, weaponWidth), weapon->mapFromScene(QPointF(x1, y1)));

    qreal angleToTarget = ::acos(lineToTarget.dx() / lineToTarget.length());
    if (lineToTarget.dy() < 0)
        angleToTarget = M_PI * 2 - angleToTarget;
    angleToTarget = normalizeAngle((M_PI - angleToTarget) + M_PI / 2);

    QTransform tr;
    tr.translate(-(weapon->rect().width() / 2), 0);
    qreal n = 0;

    if (angleToTarget >= 0 && angleToTarget < M_PI) {
        n = weapon->rotation() - angleToTarget * 180 / M_PI;
    } else if (angleToTarget <= M_PI * 2 && angleToTarget > M_PI) {
        n = weapon->rotation() + (angleToTarget - M_PI * 2 )* (-180) /M_PI;
    }
    tr.rotate(n);
    tr.translate(weapon->rect().width() / 2, 0);
    //qDebug() << n;
    weapon->setTransform(tr, true);




    //qDebug() << weapon->rotation();
    //qDebug() <<   " " << p << " " << view->geometry() << " " << ;

}

qreal Widget::screenScaleX() {
    return sceneWidth / view->rect().width();
}
qreal Widget::screenScaleY() {
    return sceneHeight / view->rect().height();
}

void Widget::bulletTimer()
{
    QPoint p = mapFromGlobal(QCursor::pos());
    QRect r = view->geometry();

    if (!QGuiApplication::focusWindow() || !r.contains(p)) return;
    qreal x1 = (p.x() - r.x()) * screenScaleX();
    qreal y1 = (p.y() - r.y()) * screenScaleY();

    qreal h = player->rect().height();
    qreal w = player->rect().width();
    if (
        player->x() - h + w / 2 <= x1 &&
        player->x() + h + w / 2 >= x1 &&
        player->y() - h + h / 2 <= y1 &&
        player->y() + h + h / 2 >= y1
      ) return;

    if (view->keysPressed.contains(Qt::LeftButton) ) {
        int ms = QDateTime::currentMSecsSinceEpoch();
        qDebug() << ms << " " << currentTime << " " << rof;

        if (ms - rof > currentTime ) {

            //qDebug() << ;
            for (int i = -splitBullets; i<=splitBullets ;i++ ) {
                //x1 += 10;


                qreal x2 = player->x() + weapon->x() - weapon->rect().width() / 2 - 1;
                qreal y2 = player->y() + weapon->y() ;
                qreal r = weapon->rect().height();

                qreal t = r/sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
                qreal x3 = x2 * (1 - t) + x1 * t;
                qreal y3 = y2 * (1 - t) + y1 * t;
                Bullet *b = new Bullet(QPointF(x3, y3), QPointF(x1, y1));

                QTransform tr;
                tr.rotate(i * splitAngle);
                b->setTransform(tr);

                scene->addItem(b);
            }
            currentTime = ms;
        }

    }

}
