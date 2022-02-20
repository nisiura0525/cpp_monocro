#pragma once
#include "CHARACTER.h"
class BLACK_PLAYER :
    public CHARACTER
{
public:
    struct DATA {
        int rightAnimId = 0;
        int leftAnimId = 1;
        int ReLife = 0;
        int jumpFlag = 0;
        float curWx = 0;
        float initVecUp = 0;
        float initVecDown = 0;
        float gravity = 0;
        int bulletsR = 0;
        int bulletsM = 0;
        float ReloadInterval = 0;
        float CurTime = 0;
        char bulletCharaId = 0;
        float bulletOffsetX = 0;
    };
    enum class STATE { 
        STRUGGLING, DIED, 
        FALL, SURVIVED
    };
private:
    DATA BlackPlayer;
    STATE State = STATE::STRUGGLING;
    //int* Relife = &BlackPlayer.ReLife;
public:
    BLACK_PLAYER(class GAME* game) :CHARACTER(game) {}
    void create();
    void appear(float wx, float wy, float vx, float vy);
    void update();
private:
    void Launch();
    void Move();
    void CollisionWithMap();
    void CheckState();
public:
    void damage();
    //void Reward() { *Relife += 1; }
    bool died();
    bool survived();
    float overCenterVx();
    STATE state() { return State; }
    void resetState();
    int life() { return BlackPlayer.ReLife; }
    int bullets() { return BlackPlayer.bulletsR; }
};

