#include "BLACK_BISHOP.h"
#include"window.h"
#include"graphic.h"
#include"ANIM.h"
#include"CONTAINER.h"
#include"GAME.h"
#include"BLACK_WORLD.h"
void BLACK_BISHOP::create() {
    Chara = game()->container()->data().blackBishopChara;
    BlackBishop = game()->container()->data().blackBishop;
    cmap();
}
void BLACK_BISHOP::appear(float wx, float wy, float vx, float vy) {
    Chara.hp = game()->container()->data().blackBishopChara.hp;
    Chara.wx = wx;
    Chara.wy = wy;
    BlackBishop.triggerCnt = game()->container()->data().blackBishop.triggerCnt;
    BlackBishop.jumpFlag = 0;
}
void BLACK_BISHOP::init() {
    Chara.hp = 0;
    BlackBishop.elapsedTime = 0;
}
void BLACK_BISHOP::update() {
    Launch();
    Move();
}
void BLACK_BISHOP::Launch() {
    //’e”­ŽË
    float vx = -1;
    if (Chara.wx > game()->characterManager()->blackPlayer()->wx()) {
        vx = -1;
    }
    else vx = 1;
    BlackBishop.elapsedTime += delta;
    if (BlackBishop.elapsedTime >= BlackBishop.interval) {
        BlackBishop.elapsedTime -= BlackBishop.interval;
        ++BlackBishop.triggerCnt %= BlackBishop.triggerInterval;
        if (BlackBishop.triggerCnt == BlackBishop.trigger1st ||
            BlackBishop.triggerCnt == BlackBishop.trigger2nd ||
            BlackBishop.triggerCnt == BlackBishop.trigger3rd ||
            BlackBishop.triggerCnt == BlackBishop.trigger4th) {
            game()->characterManager()->bulletAppear(BlackBishop.bulletCharaId,
                Chara.wx - BlackBishop.bulletOffsetX, Chara.wy,Chara.campId, vx, 0);
        }
    }
}
void BLACK_BISHOP::Move() {
    
}
void BLACK_BISHOP::damage() {
    if (Chara.hp > 0) {
        BlackBishop.damageTime = BlackBishop.damageInterval;
        Chara.hp--;
        if (Chara.hp == 0) {
         //”š”­‚È‚Ç
        }
    }
}