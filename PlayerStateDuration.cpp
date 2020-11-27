#include "PlayerStateDuration.h"
#include "QTimer"

static int randomBetween(int low, int high)
{
    return (rand() % ((high + 1) - low) + low);
}

PlayerStateDuration::PlayerStateDuration(Widget *w, QPair<int, PlayerState> p)

{
    playerState = p;
    widget = w;
    deathTimer = new QTimer();
    connect(deathTimer, &QTimer::timeout, this, &PlayerStateDuration::slotDeathTimer);
    deathTimer->start(playerState.second.duration * 1000);
}

void PlayerStateDuration::slotDeathTimer()
{

    widget->playerStates.remove(playerState.first);
    widget->updateState(widget->defaultPlayerState, true);
    delete deathTimer;
    deleteLater();
}
