#ifndef WIDGET_H
#define WIDGET_H
#include <QWidget>
#include <QGraphicsScene>
#include <Player.h>
#include <Weapon.h>
#include <EnemySlot.h>

class PlayerStateDuration;
class CustomGraphicsView;

class Widget: public QWidget
{
    Q_OBJECT
public:
    Widget(QWidget *parent = 0);
    QGraphicsScene  *scene;
    CustomGraphicsView  *view;

    Player *player;
    Weapon *weapon;
    int rof = 250;
    int splitBullets = 0;
    int splitAngle = 10;
    int bulletDamage = 1;
    int playerSpeed = 10;
    QMap<int, EnemySlot> enemySlots;
    QMap<int, PlayerState> playerStates;
    QList<PlayerState> listPlayerStates;
    bool invert = false;
    void updateState(PlayerState p, bool d);
    PlayerState defaultPlayerState;


public slots:
    void gameTimer();
    void bulletTimer();
    void spawnTimer();
    void bonusTimer();

private:
    qreal sceneWidth =  1280;
    qreal sceneHeight = 720;
    qreal screenScaleX();
    qreal screenScaleY();
    int currentTime = INT32_MIN;
};

#endif // WIDGET_H
