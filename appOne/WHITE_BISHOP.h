#pragma once
#include "CHARACTER.h"
class WHITE_BISHOP :
    public CHARACTER
{
public:
    struct DATA {
        int rightAnimId = 0;
        int leftAnimId = 1;
        int jumpFlag = 0;
        float curWx = 0;
        float initVecUp = 0;
        float initVecDown = 0;
        float gravity = 0;
        char bulletCharaId = 0;
        float bulletOffsetX = 0;
        float elapsedTime = 0;
        float interval = 0;
        int triggerCnt = 0;
        int triggerInterval = 0;
        int trigger1st = 0;
        int trigger2nd = 0;
        int trigger3rd = 0;
        int trigger4th = 0;
        float damageTime = 0;
        float damageInterval = 0;
        char explosionCharaId = 0;
        COLOR damageColor;
        COLOR normalColor;
    };
    enum class STATE {
        STRUGGLING, DIED,
        FALL, SURVIVED
    };
private:
    DATA WhiteBishop;
    STATE State = STATE::STRUGGLING;
public:
    WHITE_BISHOP(class GAME* game) :CHARACTER(game) {}
    void create();
    void appear(float wx, float wy, float vx, float vy);
    void init();
    void update();
private:
    void Launch();
    void Move();
public:
    void damage();
};

