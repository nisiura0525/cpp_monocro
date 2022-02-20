#include "BLACK_PAWN.h"
#include"window.h"
#include"ANIM.h"
#include"CONTAINER.h"
#include"GAME.h"
#include"MAP.h"
void BLACK_PAWN::create() {
    Chara = game()->container()->data().blackPawnChara;
    BlackPawn = game()->container()->data().blackPawn;
    cmap();
}
void BLACK_PAWN::appear(float wx, float wy, float vx, float vy) {
    Chara.hp = game()->container()->data().blackPawnChara.hp;
    Chara.wx = wx;
    Chara.wy = wy;
    Chara.vx = BlackPawn.initVecX;
    Chara.vy = BlackPawn.initVecY;
    Chara.animId = BlackPawn.leftAnimId;
    BlackPawn.damageTime = 0;
    BlackPawn.fallFlag = 0;
}
void BLACK_PAWN::update() {
    Move();
    CollisionWithMap();
    ChangeColor();
}
void BLACK_PAWN::Move() {
    //落下
    if (BlackPawn.fallFlag) {
        Chara.vy += BlackPawn.gravity * delta;
        Chara.wy += Chara.vy * 60 * delta;
    }
    //現在の位置をとっておく
    BlackPawn.curWx = Chara.wx;
    //左右にうごく
    Chara.wx += Chara.vx * (Chara.speed * delta);
}
void BLACK_PAWN::CollisionWithMap() {
    // マップチップにぶつかったら向きを変える
    if (BlackPawn.fallFlag == 0) {
        if (Chara.camp->collisionCharaLeft(Chara.wx, Chara.wy) ||
            Chara.camp->collisionCharaRight(Chara.wx, Chara.wy)) {
            Chara.animId = 1 - Chara.animId;
            Chara.vx = -Chara.vx;
            Chara.wx = BlackPawn.curWx;
        }
    }
    // 接地チェック（キャラの下にマップチップがあるかどうか）
    if (Chara.camp->collisionCharaBottom(BlackPawn.curWx, Chara.wy)) {
        //接地または埋まっている
        BlackPawn.fallFlag = 0;
        Chara.vy = 0;
        //埋まらないように高さを補正する
        Chara.wy = (int)Chara.wy / Chara.camp->chipSize() * (float)Chara.camp->chipSize();
    }
    else {//接地していない
        BlackPawn.fallFlag = 1;//落とす
    }
    // ウィンドウの外に出た
    if (Chara.wx < Chara.camp->wDispLeft()) {
        Chara.hp = 0;
    }
}
void BLACK_PAWN::ChangeColor() {
    //ダメージを受けたら瞬間だけ色を変える
    if (BlackPawn.damageTime > 0) {
        BlackPawn.damageTime -= delta;
        Chara.color = BlackPawn.damageColor;
    }
    else {
        Chara.color = BlackPawn.normalColor;
    }
}
void BLACK_PAWN::damage() {
    if (Chara.hp > 0) {
        BlackPawn.damageTime = BlackPawn.damageInterval;
        Chara.hp--;
        if (Chara.hp == 0) {
            game()->characterManager()->appear(BlackPawn.explosionCharaId,
                Chara.wx, Chara.wy);
        }
    }
}