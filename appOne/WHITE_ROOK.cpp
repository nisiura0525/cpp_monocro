#include "WHITE_ROOK.h"
#include"rand.h"
#include"window.h"
#include"ANIM.h"
#include"CONTAINER.h"
#include"GAME.h"
#include"MAP.h"
void WHITE_ROOK::create() {
    Chara = game()->container()->data().whiteRookChara;
    WhiteRook = game()->container()->data().whiteRook;
    cmap();
}
void WHITE_ROOK::appear(float wx, float wy, float vx, float vy) {
    Chara.hp = game()->container()->data().whiteRookChara.hp;
    Chara.wx = wx;
    Chara.wy = wy;
    Chara.vx = WhiteRook.initVecX;
    Chara.vy = WhiteRook.initVecY;
    Chara.animId = WhiteRook.leftAnimId;
    WhiteRook.ac = 0;
    WhiteRook.acCurTime = WhiteRook.acInterval * random(0.1f, 5.0f);
    WhiteRook.damageTime = 0;
    WhiteRook.fallFlag = 0;
}
void WHITE_ROOK::update() {
    Move();
    CollisionWithMap();
    ChangeColor();
}
void WHITE_ROOK::Move() {
    //落下
    if (WhiteRook.fallFlag) {
        Chara.vy += WhiteRook.gravity * delta;
        Chara.wy += Chara.vy * 60 * delta;
    }
    //現在の位置をとっておく
    WhiteRook.curWx = Chara.wx;
    //左右にうごく
    if (WhiteRook.acCurTime <= 0) {
        WhiteRook.ac = 500.0f;
    }
    else WhiteRook.acCurTime -= delta;
    Chara.wx += Chara.vx * ((Chara.speed + WhiteRook.ac) * delta);
}
void WHITE_ROOK::CollisionWithMap() {
    // マップチップにぶつかったら向きを変える
    if (WhiteRook.fallFlag == 0) {
        if (Chara.camp->collisionCharaLeft(Chara.wx, Chara.wy) ||
            Chara.camp->collisionCharaRight(Chara.wx, Chara.wy)) {
            Chara.animId = 1 - Chara.animId;
            Chara.vx = -Chara.vx;
            Chara.wx = WhiteRook.curWx;
            WhiteRook.ac *= 0.0f;
            WhiteRook.acCurTime = WhiteRook.acInterval;
        }
    }
    // 接地チェック（キャラの下にマップチップがあるかどうか）
    if (Chara.camp->collisionCharaBottom(WhiteRook.curWx, Chara.wy)) {
        //接地または埋まっている
        WhiteRook.fallFlag = 0;
        Chara.vy = 0;
        //埋まらないように高さを補正する
        Chara.wy = (int)Chara.wy / Chara.camp->chipSize() * (float)Chara.camp->chipSize();
    }
    else {//接地していない
        WhiteRook.fallFlag = 1;//落とす
    }
    // ウィンドウの外に出た
    if (Chara.wx < Chara.camp->wDispLeft()) {
        Chara.hp = 0;
    }
}
void WHITE_ROOK::ChangeColor() {
    //ダメージを受けたら瞬間だけ色を変える
    if (WhiteRook.damageTime > 0) {
        WhiteRook.damageTime -= delta;
        Chara.color = WhiteRook.damageColor;
    }
    else {
        Chara.color = WhiteRook.normalColor;
    }
}
void WHITE_ROOK::damage() {
    if (Chara.hp > 0) {
        WhiteRook.damageTime = WhiteRook.damageInterval;
        Chara.hp--;
        if (Chara.hp == 0) {
            game()->characterManager()->appear(WhiteRook.explosionCharaId,
                Chara.wx, Chara.wy);
        }
    }
}