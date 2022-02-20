#pragma once
#include "BULLET.h"
class BISHOP_BULLET :
    public BULLET
{
public:
    BISHOP_BULLET(class GAME* game) :BULLET(game) {}
    void create();
    void update();
};

