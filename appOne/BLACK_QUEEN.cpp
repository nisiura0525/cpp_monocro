#include "BLACK_QUEEN.h"
#include"rand.h"
#include"window.h"
#include"ANIM.h"
#include"CONTAINER.h"
#include"GAME.h"
#include"MAP.h"
void BLACK_QUEEN::create() {
    Chara = game()->container()->data().blackQueenChara;
    BlackQueen = game()->container()->data().blackQueen;
    cmap();
}
void BLACK_QUEEN::appear(float wx, float wy, float vx, float vy) {
    Chara.hp = game()->container()->data().blackQueenChara.hp;
    Chara.wx = wx;
    Chara.wy = wy;
    Chara.vx = BlackQueen.initVecX;
    Chara.vy = BlackQueen.initVecY;
    Chara.animId = BlackQueen.leftAnimId;
    BlackQueen.ac = 0;
    BlackQueen.acCurTime = random(0.0f,-5.0f);
    BlackQueen.damageTime = 0;
    BlackQueen.fallFlag = 0;
    BlackQueen.jelpTime = 0;
    BlackQueen.jumpFlag = 0;
    BlackQueen.acTrigger = 0;
}
void BLACK_QUEEN::update() {
    Move();
    CollisionWithMap();
    Launch();
    ChangeColor();
}
void BLACK_QUEEN::Move() {
    //ジャンプ
    if (BlackQueen.jumpFlag == 0) {
        BlackQueen.jelpTime += delta;
    }
    if (BlackQueen.jumpFlag == 0 && BlackQueen.jelpTime >= BlackQueen.jumpTrigger
        ) {
        Chara.vy = BlackQueen.initVecUp;
        BlackQueen.acCurTime = BlackQueen.acInterval;
        BlackQueen.jumpFlag = 1;
    }
    if (BlackQueen.jumpFlag == 1) {
        BlackQueen.acCurTime += delta;
        if (Chara.wy >= 400) {
            Chara.wy += Chara.vy;
        }
         Chara.wx += Chara.vx * ((Chara.speed + BlackQueen.ac) * delta);
        BlackQueen.jelpTime -= delta;
        if (BlackQueen.jelpTime <= -BlackQueen.jumpTrigger*2) {
            BlackQueen.jumpFlag = 2;
            Chara.vy = 0;  
        }
    }
    if (BlackQueen.jumpFlag == 2) {
        BlackQueen.jelpTime = 0;
        Chara.vy += BlackQueen.gravity * delta;
        Chara.wy += Chara.vy * 60 * delta;
    }
    //落下
    if (BlackQueen.fallFlag) {
        Chara.vy += BlackQueen.gravity * delta;
        Chara.wy += Chara.vy * 60 * delta;
    }
    //現在の位置をとっておく
    BlackQueen.curWx = Chara.wx;
    //左右に一気にうごく
    if (BlackQueen.acCurTime >= BlackQueen.acInterval && BlackQueen.acTrigger == 0) {
        BlackQueen.acTrigger = 1;
        BlackQueen.acDurations = random(1.5f, 3.0f);
        Chara.vx = random(1.0f,-1.0f);
    }
    if (BlackQueen.acTrigger == 1) {
        BlackQueen.ac = 50.0f+Chara.speed;
        BlackQueen.acCurTime = 0;
        BlackQueen.acDurations -= delta;
        if (BlackQueen.acDurations <= -1) {
            BlackQueen.ac *= 0.0f;
            BlackQueen.acTrigger = 0;
            BlackQueen.acCurTime = 0;
            Chara.vx *= -1;
            BlackQueen.acDurations = 0;
        }
    }
    if (Chara.wx <= 0) {
        Chara.vx *= -1;
    }
}
void BLACK_QUEEN::CollisionWithMap() {
    // マップチップにぶつかったら向きを変える
    if (BlackQueen.fallFlag == 0) {
        if (Chara.camp->collisionCharaLeft(Chara.wx, Chara.wy) ||
            Chara.camp->collisionCharaRight(Chara.wx, Chara.wy)) {
            //Chara.vx = -Chara.vx;
            Chara.wx = BlackQueen.curWx;
        }
    }
            //Chara.animId = 1 - Chara.animId;
    // 接地チェック（キャラの下にマップチップがあるかどうか）
    if (Chara.camp->collisionCharaBottom(BlackQueen.curWx, Chara.wy)) {
        //接地または埋まっている
        BlackQueen.fallFlag = 0;
        BlackQueen.jumpFlag = 0;
        Chara.vy = 0;
        //埋まらないように高さを補正する
        Chara.wy = (int)Chara.wy / Chara.camp->chipSize() * (float)Chara.camp->chipSize();
    }
    else {//接地していない
        //BlackQueen.fallFlag = 1;//落とす
    }
    if (Chara.wx > game()->characterManager()->blackPlayer()->wx()) {
        Chara.animId = BlackQueen.leftAnimId;
    }
    else Chara.animId = BlackQueen.rightAnimId;
    // ウィンドウの外に出た
}
void BLACK_QUEEN::Launch() {
        float vx = 1.0f;
        float vy = 1.0f;
        float wx = Chara.wx;
        float wy = Chara.wy;
        if (BlackQueen.jumpFlag == 1) {
            ++BlackQueen.triggerCnt %= BlackQueen.triggerInterval;
            if (BlackQueen.triggerCnt == BlackQueen.changeTrigger) {
                BlackQueen.curBullet = (BlackQueen.curBullet + 1) % 2;
            }
            if (BlackQueen.curBullet == 0) {
                if (BlackQueen.triggerCnt == BlackQueen.trigger1st ||
                    BlackQueen.triggerCnt == BlackQueen.trigger2nd ||
                    BlackQueen.triggerCnt == BlackQueen.trigger3rd ||
                    BlackQueen.triggerCnt == BlackQueen.trigger4th ) {
                    game()->characterManager()->bulletAppear(BlackQueen.bulletCharaId,
                        wx, wy, Chara.campId, vx, vy,BlackQueen.curBullet);
                    
                }
            }
            if (BlackQueen.curBullet == 1) {
                if (BlackQueen.triggerCnt == BlackQueen.trigger1 ||
                    BlackQueen.triggerCnt == BlackQueen.trigger2 ||
                    BlackQueen.triggerCnt == BlackQueen.trigger3 ||
                    BlackQueen.triggerCnt == BlackQueen.trigger4 ||
                    BlackQueen.triggerCnt == BlackQueen.trigger5 ||
                    BlackQueen.triggerCnt == BlackQueen.trigger6 ||
                    BlackQueen.triggerCnt == BlackQueen.trigger7 ||
                    BlackQueen.triggerCnt == BlackQueen.trigger8) {
                    game()->characterManager()->bulletAppear(BlackQueen.bulletCharaId,
                        wx, wy, Chara.campId, vx, vy, BlackQueen.curBullet);
                }
            }
        }
}
void BLACK_QUEEN::ChangeColor() {
    //ダメージを受けたら瞬間だけ色を変える
    if (BlackQueen.damageTime > 0) {
        BlackQueen.damageTime -= delta;
        Chara.color = BlackQueen.damageColor;
    }
    else {
        Chara.color = BlackQueen.normalColor;
    }
}
void BLACK_QUEEN::damage() {
    if (Chara.hp > 0) {
        BlackQueen.damageTime = BlackQueen.damageInterval;
        Chara.hp--;
        if (Chara.hp == 0) {
            game()->characterManager()->appear(BlackQueen.explosionCharaId,
                Chara.wx, Chara.wy);
        }
    }
}