#pragma once
#include "CHARACTER.h"
class BLACK_KNIGHT :
    public CHARACTER
{
public:
    struct DATA {
        int direction = -1;
        int rightAnimId = 0;
        int leftAnimId = 1;
        int jumpFlag = 0;
        float curWx = 0;
        float initVecUp = 0;
        float initVecDown = 0;
        float gravity = 0;
        float jelpTime = 0;
        float jumpTrigger = 0;
        //tama
        float  bulletOffsetX = 0;
        char bulletCharaId = 0;
        float  elapsedTime = 0;
        float  interval = 0;
        int triggerCnt = 0;
        int triggerInterval = 0;
        int trigger1st = 0;
        int trigger2nd = 0;
        int trigger3rd = 0;
        int trigger4th = 0;
        //damage
        float  damageTime = 0;
        float  damageInterval = 0;
        char  explosionCharaId =0;
        COLOR  damageColor;
        COLOR  normalColor;
    };
private:
    DATA BlackKnight;
public:
    BLACK_KNIGHT(class GAME* game) :CHARACTER(game) {}
    void create();
    void appear(float wx, float wy, float vx, float vy);
    void update();
private:
    void Launch();
    void Move();
    void CollisionWithMap();
    void damage();
};

