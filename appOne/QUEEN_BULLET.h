#pragma once
#include "BULLET.h"
#include "VECTOR2.h"
class QUEEN_BULLET :
    public BULLET
{
public:
    VECTOR2 player, queen, vec;
    QUEEN_BULLET(class GAME* game) :BULLET(game) {}
    void appear(float wx, float wy, float vx, float vy, char campId, int curbullet = 0);
    void create();
    void update();
};

