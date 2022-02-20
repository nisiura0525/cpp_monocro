#include "WHITE_QUEEN.h"
#include"rand.h"
#include"window.h"
#include"ANIM.h"
#include"CONTAINER.h"
#include"GAME.h"
#include"MAP.h"
void WHITE_QUEEN::create() {
    Chara = game()->container()->data().whiteQueenChara;
    WhiteQueen = game()->container()->data().whiteQueen;                           
    cmap();
}
void WHITE_QUEEN::appear(float wx, float wy, float vx, float vy) {
    Chara.hp = game()->container()->data().whiteQueenChara.hp;
    Chara.wx = wx;
    Chara.wy = wy;
    Chara.vx = WhiteQueen.initVecX;
    Chara.vy = WhiteQueen.initVecY;
    Chara.animId = WhiteQueen.leftAnimId;
    WhiteQueen.ac = 0;
    WhiteQueen.acCurTime = random(0.0f, -5.0f);
    WhiteQueen.damageTime = 0;
    WhiteQueen.fallFlag = 0;
    WhiteQueen.jelpTime = 0;
    WhiteQueen.jumpFlag = 0;
    WhiteQueen.acTrigger = 0;
}
void WHITE_QUEEN::update() {
    Move();
    CollisionWithMap();
    Launch();
    ChangeColor();
}
void WHITE_QUEEN::Move() {
    //ジャンプ
    if (WhiteQueen.jumpFlag == 0) {
        WhiteQueen.jelpTime += delta;
    }
    if (WhiteQueen.jumpFlag == 0 && WhiteQueen.jelpTime >= WhiteQueen.jumpTrigger
        ) {
        Chara.vy = WhiteQueen.initVecUp;
        WhiteQueen.acCurTime = WhiteQueen.acInterval;
        WhiteQueen.jumpFlag = 1;
    }
    if (WhiteQueen.jumpFlag == 1) {
        WhiteQueen.acCurTime += delta;
        if (Chara.wy >= 0) {
            Chara.wy += Chara.vy;
        }
        Chara.wx += Chara.vx * ((Chara.speed + WhiteQueen.ac) * delta);
        WhiteQueen.jelpTime -= delta;
        if (WhiteQueen.jelpTime <= -WhiteQueen.jumpTrigger * 2) {
            WhiteQueen.jumpFlag = 2;
            Chara.vy = 0;
        }
    }
    if (WhiteQueen.jumpFlag == 2) {
        WhiteQueen.jelpTime = 0;
        Chara.vy += WhiteQueen.gravity * delta;
        Chara.wy += Chara.vy * 60 * delta;
    }
    //落下
    if (WhiteQueen.fallFlag) {
        Chara.vy += WhiteQueen.gravity * delta;
        Chara.wy += Chara.vy * 60 * delta;
    }
    //現在の位置をとっておく
    WhiteQueen.curWx = Chara.wx;
    //左右に一気にうごく
    if (WhiteQueen.acCurTime >= WhiteQueen.acInterval && WhiteQueen.acTrigger == 0) {
        WhiteQueen.acTrigger = 1;
        WhiteQueen.acDurations = random(1.5f, 3.0f);
        Chara.vx = random(1.0f, -1.0f);
    }
    if (WhiteQueen.acTrigger == 1) {
        WhiteQueen.ac = 50.0f + Chara.speed;
        WhiteQueen.acCurTime = 0;
        WhiteQueen.acDurations -= delta;
        if (WhiteQueen.acDurations <= -1) {
            WhiteQueen.ac *= 0.0f;
            WhiteQueen.acTrigger = 0;
            WhiteQueen.acCurTime = 0;
            Chara.vx *= -1;
            WhiteQueen.acDurations = 0;
        }
    }
    if (Chara.wx <= 0) {
        Chara.vx *= -1;
    }
}
void WHITE_QUEEN::CollisionWithMap() {
    // マップチップにぶつかったら向きを変える
    if (WhiteQueen.fallFlag == 0) {
        if (Chara.camp->collisionCharaLeft(Chara.wx, Chara.wy) ||
            Chara.camp->collisionCharaRight(Chara.wx, Chara.wy)) {
            //Chara.vx = -Chara.vx;
            Chara.wx = WhiteQueen.curWx;
        }
    }
    //Chara.animId = 1 - Chara.animId;
// 接地チェック（キャラの下にマップチップがあるかどうか）
    if (Chara.camp->collisionCharaBottom(WhiteQueen.curWx, Chara.wy)) {
        //接地または埋まっている
        WhiteQueen.fallFlag = 0;
        WhiteQueen.jumpFlag = 0;
        Chara.vy = 0;
        //埋まらないように高さを補正する
        Chara.wy = (int)Chara.wy / Chara.camp->chipSize() * (float)Chara.camp->chipSize();
    }
    else {//接地していない
        //WhiteQueen.fallFlag = 1;//落とす
    }
    if (Chara.wx > game()->characterManager()->whitePlayer()->wx()) {
        Chara.animId = WhiteQueen.leftAnimId;
    }
    else Chara.animId = WhiteQueen.rightAnimId;
    // ウィンドウの外に出た
}
void WHITE_QUEEN::Launch() {
    float vx = 1.0f;
    float vy = 1.0f;
    float wx = Chara.wx;
    float wy = Chara.wy;
    if (WhiteQueen.jumpFlag == 1) {
        ++WhiteQueen.triggerCnt %= WhiteQueen.triggerInterval;
        if (WhiteQueen.triggerCnt == WhiteQueen.changeTrigger) {
            WhiteQueen.curBullet = (WhiteQueen.curBullet + 1) % 2;
        }
        if (WhiteQueen.curBullet == 0) {
            if (WhiteQueen.triggerCnt == WhiteQueen.trigger1st ||
                WhiteQueen.triggerCnt == WhiteQueen.trigger2nd ||
                WhiteQueen.triggerCnt == WhiteQueen.trigger3rd ||
                WhiteQueen.triggerCnt == WhiteQueen.trigger4th) {
                game()->characterManager()->bulletAppear(WhiteQueen.bulletCharaId,
                    wx, wy, Chara.campId, vx, vy, WhiteQueen.curBullet);

            }
        }
        if (WhiteQueen.curBullet == 1) {
            if (WhiteQueen.triggerCnt == WhiteQueen.trigger1 ||
                WhiteQueen.triggerCnt == WhiteQueen.trigger2 ||
                WhiteQueen.triggerCnt == WhiteQueen.trigger3 ||
                WhiteQueen.triggerCnt == WhiteQueen.trigger4 ||
                WhiteQueen.triggerCnt == WhiteQueen.trigger5 ||
                WhiteQueen.triggerCnt == WhiteQueen.trigger6 ||
                WhiteQueen.triggerCnt == WhiteQueen.trigger7 ||
                WhiteQueen.triggerCnt == WhiteQueen.trigger8) {
                game()->characterManager()->bulletAppear(WhiteQueen.bulletCharaId,
                    wx, wy, Chara.campId, vx, vy, WhiteQueen.curBullet);
            }
        }
    }
}
void WHITE_QUEEN::ChangeColor() {
    //ダメージを受けたら瞬間だけ色を変える
    if (WhiteQueen.damageTime > 0) {
        WhiteQueen.damageTime -= delta;
        Chara.color = WhiteQueen.damageColor;
    }
    else {
        Chara.color = WhiteQueen.normalColor;
    }
}
void WHITE_QUEEN::damage() {
    if (Chara.hp > 0) {
        WhiteQueen.damageTime = WhiteQueen.damageInterval;
        Chara.hp--;
        if (Chara.hp == 0) {
            game()->characterManager()->appear(WhiteQueen.explosionCharaId,
                Chara.wx, Chara.wy);
        }
    }
}