#include "WHITE_PAWN.h"
#include"window.h"
#include"ANIM.h"
#include"CONTAINER.h"
#include"GAME.h"
#include"MAP.h"
void WHITE_PAWN::create() {
    Chara = game()->container()->data().whitePawnChara;
    WhitePawn = game()->container()->data().whitePawn;
    cmap();
}
void WHITE_PAWN::appear(float wx, float wy, float vx, float vy) {
    Chara.hp = game()->container()->data().whitePawnChara.hp;
    Chara.wx = wx;
    Chara.wy = wy;
    Chara.vx = WhitePawn.initVecX;
    Chara.vy = WhitePawn.initVecY;
    Chara.animId = WhitePawn.leftAnimId;
    WhitePawn.damageTime = 0;
    WhitePawn.fallFlag = 0;
}
void  WHITE_PAWN::update() {
    Move();
    CollisionWithMap();
    ChangeColor();
}
void WHITE_PAWN::Move() {
    //落下
    if (WhitePawn.fallFlag) {
        Chara.vy += WhitePawn.gravity * delta;
        Chara.wy += Chara.vy * 60 * delta;
    }
    //現在の位置をとっておく
    WhitePawn.curWx = Chara.wx;
    //左右にうごく
    Chara.wx += Chara.vx * (Chara.speed * delta);
}
void WHITE_PAWN::CollisionWithMap() {
    // マップチップにぶつかったら向きを変える
    if (WhitePawn.fallFlag == 0) {
        if (Chara.camp->collisionCharaLeft(Chara.wx, Chara.wy) ||
            Chara.camp->collisionCharaRight(Chara.wx, Chara.wy)) {
            Chara.animId = 1 - Chara.animId;
            Chara.vx = -Chara.vx;
            Chara.wx = WhitePawn.curWx;
        }
    }
    // 接地チェック（キャラの下にマップチップがあるかどうか）
    if (Chara.camp->collisionCharaBottom(WhitePawn.curWx, Chara.wy)) {
        //接地または埋まっている
        WhitePawn.fallFlag = 0;
        Chara.vy = 0;
        //埋まらないように高さを補正する
        Chara.wy = (int)Chara.wy / Chara.camp->chipSize() * (float)Chara.camp->chipSize();
    }
    else {//接地していない
        WhitePawn.fallFlag = 1;//落とす
    }
    // ウィンドウの外に出た
    if (Chara.wx < Chara.camp->wDispLeft()) {
        Chara.hp = 0;
    }
}
void WHITE_PAWN::ChangeColor() {
    //ダメージを受けたら瞬間だけ色を変える
    if (WhitePawn.damageTime > 0) {
        WhitePawn.damageTime -= delta;
        Chara.color = WhitePawn.damageColor;
    }
    else {
        Chara.color = WhitePawn.normalColor;
    }
}
void WHITE_PAWN::damage() {
    if (Chara.hp > 0) {
        WhitePawn.damageTime = WhitePawn.damageInterval;
        Chara.hp--;
        if (Chara.hp == 0) {
            game()->characterManager()->appear(WhitePawn.explosionCharaId,
                Chara.wx, Chara.wy);
        }
    }
}