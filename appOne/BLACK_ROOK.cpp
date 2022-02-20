#include "BLACK_ROOK.h"
#include"rand.h"
#include"window.h"
#include"ANIM.h"
#include"CONTAINER.h"
#include"GAME.h"
#include"MAP.h"
void BLACK_ROOK::create() {
    Chara = game()->container()->data().blackRookChara;
    BlackRook = game()->container()->data().blackRook;
    cmap();
}
void BLACK_ROOK::appear(float wx, float wy, float vx, float vy) {
    Chara.hp = game()->container()->data().blackRookChara.hp;
    Chara.wx = wx;
    Chara.wy = wy;
    Chara.vx = BlackRook.initVecX;
    Chara.vy = BlackRook.initVecY;
    Chara.animId = BlackRook.leftAnimId;
    BlackRook.ac = 0;
    BlackRook.acCurTime = BlackRook.acInterval*random(0.1f, 5.0f);
    BlackRook.damageTime = 0;
    BlackRook.fallFlag = 0;
}
void BLACK_ROOK::update() {
    Move();
    CollisionWithMap();
    ChangeColor();
}
void BLACK_ROOK::Move() {
    //落下
    if (BlackRook.fallFlag) {
        Chara.vy += BlackRook.gravity * delta;
        Chara.wy += Chara.vy * 60 * delta;
    }
    //現在の位置をとっておく
    BlackRook.curWx = Chara.wx;
    //左右にうごく
    if (BlackRook.acCurTime <= 0) {
        BlackRook.ac = 810.0f;
    }
    else BlackRook.acCurTime -= delta;
    Chara.wx += Chara.vx * ((Chara.speed+BlackRook.ac) * delta) ;
}
void BLACK_ROOK::CollisionWithMap() {
    // マップチップにぶつかったら向きを変える
    if (BlackRook.fallFlag == 0) {
        if (Chara.camp->collisionCharaLeft(Chara.wx, Chara.wy) ||
            Chara.camp->collisionCharaRight(Chara.wx, Chara.wy)) {
            Chara.animId = 1 - Chara.animId;
            Chara.vx = -Chara.vx;
            Chara.wx = BlackRook.curWx;
            BlackRook.ac *= 0.0f;
            BlackRook.acCurTime = BlackRook.acInterval;
        }
    }
    // 接地チェック（キャラの下にマップチップがあるかどうか）
    if (Chara.camp->collisionCharaBottom(BlackRook.curWx, Chara.wy)) {
        //接地または埋まっている
        BlackRook.fallFlag = 0;
        Chara.vy = 0;
        //埋まらないように高さを補正する
        Chara.wy = (int)Chara.wy / Chara.camp->chipSize() * (float)Chara.camp->chipSize();
    }
    else {//接地していない
        BlackRook.fallFlag = 1;//落とす
    }
    // ウィンドウの外に出た
    if (Chara.wx < Chara.camp->wDispLeft()) {
        Chara.hp = 0;
    }
}
void BLACK_ROOK::ChangeColor() {
    //ダメージを受けたら瞬間だけ色を変える
    if (BlackRook.damageTime > 0) {
        BlackRook.damageTime -= delta;
        Chara.color = BlackRook.damageColor;
    }
    else {
        Chara.color = BlackRook.normalColor;
    }
}
void BLACK_ROOK::damage() {
    if (Chara.hp > 0) {
        BlackRook.damageTime = BlackRook.damageInterval;
        Chara.hp--;
        if (Chara.hp == 0) {
            game()->characterManager()->appear(BlackRook.explosionCharaId,
                Chara.wx, Chara.wy);
        }
    }
}