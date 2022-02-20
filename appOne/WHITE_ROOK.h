#pragma once
#include "CHARACTER.h"
class WHITE_ROOK :
    public CHARACTER
{
public:
    struct DATA {
        int   rightAnimId = 0;
        int   leftAnimId = 1;
        int   fallFlag = 0;
        float curWx = 0;
        float initVecX = 0;
        float initVecY = 0;
        float ac = 1;
        float acCurTime = 0;
        float acInterval = 0;
        float gravity = 0;
        float alphaLowVal = 0;
        float damageTime = 0;
        float damageInterval = 0;
        char explosionCharaId = 0;
        COLOR damageColor;
        COLOR normalColor;
    };
private:
    DATA WhiteRook;
public:
    WHITE_ROOK(class GAME* game) :CHARACTER(game) {}
    void create();
    void appear(float wx, float wy, float vx, float vy);
    void update();
private:
    void Move();
    void CollisionWithMap();
    void ChangeColor();
    void damage();
};

