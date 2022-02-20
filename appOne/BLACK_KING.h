#pragma once
#include "CHARACTER.h"
class BLACK_KING :
    public CHARACTER
{
public:
    struct DATA {
        int   rightAnimId = 0;
        int   leftAnimId = 1;
        int   fallFlag = 0;
        int   jumpFlag = 0;
        float curWx = 0;
        float initVecUp=0;
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
        int summonNumber = 0;
        COLOR damageColor;
        COLOR normalColor;
    };
private:
    DATA BlackKing;
public:
    BLACK_KING(class GAME* game) :CHARACTER(game) {}
    void create();
    void appear(float wx, float wy, float vx, float vy);
    void init();
    void update();
    void deth();
private:
    void Move();
    void Summons();
    void CollisionWithMap();
    void ChangeColor();
    void damage();
    void draw();
public:
    int hp() { return Chara.hp; }
};

