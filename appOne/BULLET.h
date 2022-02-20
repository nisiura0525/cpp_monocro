#pragma once
#include "CHARACTER.h"
class BULLET :
    public CHARACTER
{
public:
    int curBullet = 0;
    BULLET(class GAME* game) :CHARACTER(game) {}
    virtual void create();
    virtual void appear(float wx, float wy, float vx, float vy,char campId ,int curbullet = 0);
    virtual void update();
};
