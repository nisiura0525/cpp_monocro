#include "WHITE_BISHOP.h"
#include"window.h"
#include"graphic.h"
#include"ANIM.h"
#include"CONTAINER.h"
#include"GAME.h"
#include"BLACK_WORLD.h"
void WHITE_BISHOP::create() {
    Chara = game()->container()->data().whiteBishopChara;
    WhiteBishop = game()->container()->data().whiteBishop;
    cmap();
}
void WHITE_BISHOP::appear(float wx, float wy, float vx, float vy) {
    Chara.hp = game()->container()->data().whiteBishopChara.hp;
    Chara.wx = wx;
    Chara.wy = wy;
    WhiteBishop.triggerCnt = game()->container()->data().whiteBishop.triggerCnt;
    WhiteBishop.jumpFlag = 0;
}
void WHITE_BISHOP::init() {
    Chara.hp = 0;
    WhiteBishop.elapsedTime = 0;
}
void WHITE_BISHOP::update() {
    Launch();
    Move();
}
void WHITE_BISHOP::Launch() {
    //弾発射
    float vx = -1;
    if (Chara.wx > game()->characterManager()->whitePlayer()->wx()) {
        vx = -1;
    }
    else vx = 1;
    WhiteBishop.elapsedTime += delta;
    if (WhiteBishop.elapsedTime >= WhiteBishop.interval) {
        WhiteBishop.elapsedTime -= WhiteBishop.interval;
        ++WhiteBishop.triggerCnt %= WhiteBishop.triggerInterval;
        if (WhiteBishop.triggerCnt == WhiteBishop.trigger1st ||
            WhiteBishop.triggerCnt == WhiteBishop.trigger2nd ||
            WhiteBishop.triggerCnt == WhiteBishop.trigger3rd ||
            WhiteBishop.triggerCnt == WhiteBishop.trigger4th) {
            game()->characterManager()->bulletAppear(WhiteBishop.bulletCharaId,
                Chara.wx - WhiteBishop.bulletOffsetX, Chara.wy, Chara.campId, vx, 0);
        }
    }
}
void WHITE_BISHOP::Move() {
    /*
    //ジャンプ
    if (WhiteBishop.jumpFlag == 0 && isTrigger(KEY_W)) {
        Chara.vy = WhiteBishop.initVecUp;
        WhiteBishop.jumpFlag = 1;
    }
    if (WhiteBishop.jumpFlag == 1) {
        Chara.vy += WhiteBishop.gravity * delta;
        Chara.wy += Chara.vy * 60 * delta;
    }
    //左右移動
    //  移動ベクトルを決定
    Chara.vx = 0.0f;
    if (isPress(KEY_A)) {
        Chara.vx = -Chara.speed * delta;
        Chara.animId = WhiteBishop.leftAnimId;
    }
    if (isPress(KEY_D)) {
        Chara.vx = Chara.speed * delta;
        Chara.animId = WhiteBishop.rightAnimId;
    }
    //  移動前に現在のChara.wxをBishop.curWxにとっておく
    WhiteBishop.curWx = Chara.wx;
    //  移動
    if (Chara.vx != 0.0f) {//左右キー入力あり
        //とりあえず「次に移動する予定」の位置としてChara.wxを更新しておき
        //あとで、マップに食い込んでいたら、元のBishop.curWxに戻す
        Chara.wx += Chara.vx;
    }
    else {//左右キー入力がないとき
        Chara.animData.imgIdx = 0;
        Chara.animData.elapsedTime = -delta;
    }
*/
}
/*
void White_BISHOP::CollisionWithMap() {
    // マップチップとキャラの右
    if (Chara.animId == WhiteBishop.rightAnimId) {
        if (Chara.camp->collisionCharaRight(Chara.wx, Chara.wy)) {
            //移動予定位置がマップに食い込んでいるので現在の位置に戻す
            Chara.wx = WhiteBishop.curWx;
        }
    }
    // マップチップとキャラの左
    else {
        if (Chara.camp->collisionCharaLeft(Chara.wx, Chara.wy) ||
            Chara.wx < Chara.camp->wx() //または、ウィンドウの左にぶつかったか
            ) {
            Chara.wx = WhiteBishop.curWx;
        }
    }
    // マップチップとキャラの上
    if (Chara.camp->collisionCharaTop(Chara.wx, Chara.wy)) {
        Chara.vy = WhiteBishop.initVecDown;//落ちていく初速度
    }
    // マップチップとキャラの下
    if (Chara.camp->collisionCharaBottom(WhiteBishop.curWx, Chara.wy)) {
        //--「マップチップに食い込んでいる」
        // または「上に立っているとき」もここを通る--
        //ジャンプ（落下）処理の停止
        WhiteBishop.jumpFlag = 0;
        Chara.vy = 0.0f;
        //強制的に上に立っている位置にする
        Chara.wy = (int)Chara.wy / Chara.camp->chipSize() * (float)Chara.camp->chipSize();
    }
    else {
        WhiteBishop.jumpFlag = 1;//落ちてくトリガー。このフラッグを立てるだけで落ちていく。
    }
}
*/
void WHITE_BISHOP::damage() {
    if (Chara.hp > 0) {
        WhiteBishop.damageTime = WhiteBishop.damageInterval;
        Chara.hp--;
        if (Chara.hp == 0) {
            //爆発など
        }
    }
}