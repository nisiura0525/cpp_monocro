#pragma once
#include "CHARACTER.h"
class WHITE_QUEEN :
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

        int   fallFlag = 0;
        float initVecX = 0;
        float initVecY = 0;
        float ac = 1;
        float acTrigger = 0;
        float acCurTime = 0;
        float acInterval = 0;
        float acDurations = 0;
        float alphaLowVal = 0;
        //tama
        float  bulletOffsetX = 0;
        char bulletCharaId = 0;
        float  elapsedTime = 0;
        float  interval = 0;
        int triggerCnt = 0;
        int triggerInterval = 0;
        int changeTrigger = 0;
        int trigger1st = 0;
        int trigger2nd = 0;
        int trigger3rd = 0;
        int trigger4th = 0;
        int trigger1 = 0;
        int trigger2 = 0;
        int trigger3 = 0;
        int trigger4 = 0;
        int trigger5 = 0;
        int trigger6 = 0;
        int trigger7 = 0;
        int trigger8 = 0;

        int curBullet = 0;
        //damage
        float  damageTime = 0;
        float  damageInterval = 0;
        char  explosionCharaId = 0;
        COLOR  damageColor;
        COLOR  normalColor;
    };
private:
    DATA WhiteQueen;
public:
    WHITE_QUEEN(class GAME* game) :CHARACTER(game) {}
    void create();
    void appear(float wx, float wy, float vx, float vy);
    void update();
private:
    void Launch();
    void ChangeColor();
    void Move();
    void CollisionWithMap();
    void damage();
public:
    int curbullet() { return WhiteQueen.curBullet; }
};

