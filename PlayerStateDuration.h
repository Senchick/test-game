#ifndef PLAYERSTATEDURATION_H
#define PLAYERSTATEDURATION_H
#include <PlayerState.h>
#include <QApplication>
#include <Widget.h>


class PlayerStateDuration: public QObject
{
public:
    PlayerStateDuration(Widget *w, QPair<int, PlayerState>  p);
    Widget *widget;

protected:
    QTimer *deathTimer;
    QPair<int, PlayerState>  playerState;

private slots:
    void slotDeathTimer();
};

#endif // PLAYERSTATEDURATION_H
