#pragma once
#include "CHARACTER.h"
class WHITE_PLAYER :
    public CHARACTER
{
public:
    struct DATA {
        int rightAnimId = 0;
        int leftAnimId = 1;
        int jumpFlag = 0;
        int ReLife = 0;
        float curWx = 0;
        float initVecUp = 0;
        float initVecDown = 0;
        float gravity = 0;
        char bulletCharaId = 0;
        int bulletsR = 0;
        int bulletsM = 0;
        float ReloadInterval = 0;
        float CurTime = 0;
        float bulletOffsetX = 0;
    };
    enum class STATE {
        STRUGGLING, DIED,
        FALL, SURVIVED
    };
private:
    DATA WhitePlayer;
    STATE State = STATE::STRUGGLING;
    //int* Relife = &WhitePlayer.ReLife;
public:
    WHITE_PLAYER(class GAME* game) :CHARACTER(game) {}
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
    bool died();
    bool survived();
    float overCenterVx();
    STATE state() { return State; }
    void resetState();
    //void Reward() { *Relife += 1; }
    int life() { return WhitePlayer.ReLife; }
    int bullets() { return WhitePlayer.bulletsR; }
};

