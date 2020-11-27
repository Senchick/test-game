#ifndef PLAYERSTATE_H
#define PLAYERSTATE_H

struct PlayerState {
    int type;
    int priority = 0;
    int duration = -1; //если -1 то эффект длится всегда (мс)
    int rof = 300;
    int splitBullets = 0;
    int bulletDamage = 1;
    int splitAngle = 10;
    int playerSpeed = 10;
    bool invert = false;
};

#endif // PLAYERSTATE_H
