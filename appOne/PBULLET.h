#pragma once
#include "BULLET.h"
class PBULLET :
    public BULLET
{
public:
    PBULLET(class GAME* game) :BULLET(game) {}
    void create();
    void appear(float wx, float wy, float vx, float vy, char campId);
};

