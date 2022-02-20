#include "WHITE_KNIGHT.h"
#include"window.h"
#include"input.h"
#include"graphic.h"
#include"ANIMS.h"
#include"CONTAINER.h"
#include"GAME.h"
#include"WHITE_WORLD.h"
void WHITE_KNIGHT::create() {
    Chara = game()->container()->data().whiteKnightChara;
    WhiteKnight = game()->container()->data().whiteKnight;
    cmap();
}
void WHITE_KNIGHT::appear(float wx, float wy, float vx, float vy) {
    Chara.hp = game()->container()->data().whiteKnightChara.hp;
    Chara.wx = wx;
    Chara.wy = wy;
    Chara.animId = WhiteKnight.rightAnimId;
    WhiteKnight.jumpFlag = 0;
}
void WHITE_KNIGHT::update() {
    Launch();
    Move();
    CollisionWithMap();
}
void WHITE_KNIGHT::Launch() {
    //弾発射
    /*
    if (isTrigger(KEY_F)) {
        float vx = 1.0f;
        if (Chara.animId == WhitePlayer.leftAnimId) vx = -1.0f;
        float wx = Chara.wx + WhitePlayer.bulletOffsetX * vx;
        float wy = Chara.wy;
        game()->characterManager()->bulletAppear(WhitePlayer.bulletCharaId, wx, wy, Chara.campId, vx);
    }
    */
}
void WHITE_KNIGHT::Move() {
    //ジャンプ
    WhiteKnight.jelpTime += delta;
    if (WhiteKnight.jumpFlag == 0&&WhiteKnight.jelpTime >= WhiteKnight.jumpTrigger
        ) {
        Chara.vy = WhiteKnight.initVecUp;
        WhiteKnight.jumpFlag = 1;
        WhiteKnight.jelpTime = 0;
    }
    if (WhiteKnight.jumpFlag == 1) {
        Chara.vy += WhiteKnight.gravity * delta;
        Chara.wy += Chara.vy * 60 * delta;
    }
    //左右移動
    //  移動ベクトルを決定
    Chara.vx = 0.0f;
    Chara.vx = Chara.speed * delta*WhiteKnight.direction;
    if (moveleft(game()->characterManager()->whitePlayer()->wx())&&
        WhiteKnight.jumpFlag == 0){
        WhiteKnight.direction = -1;
        Chara.animId = WhiteKnight.leftAnimId;
    }
    if (moveright(game()->characterManager()->whitePlayer()->wx()) && 
        WhiteKnight.jumpFlag == 0) {
        WhiteKnight.direction = 1;
        Chara.animId = WhiteKnight.rightAnimId;
    }
    //  移動前に現在のChara.wxをKnight.curWxにとっておく
    WhiteKnight.curWx = Chara.wx;
    //  移動
    if (Chara.vx != 0.0f) {//左右キー入力あり
        //とりあえず「次に移動する予定」の位置としてChara.wxを更新しておき
        //あとで、マップに食い込んでいたら、元のKnight.curWxに戻す
        Chara.wx += Chara.vx;
    }
    else {//左右キー入力がないとき
        Chara.animData.imgIdx = 0;
        Chara.animData.elapsedTime = -delta;
    }
}
void WHITE_KNIGHT::CollisionWithMap() {
    // マップチップとキャラの右
    if (Chara.animId == WhiteKnight.rightAnimId) {
        if (Chara.camp->collisionCharaRight(Chara.wx, Chara.wy)) {
            //移動予定位置がマップに食い込んでいるので現在の位置に戻す
            Chara.wx = WhiteKnight.curWx;
        }
    }
    // マップチップとキャラの左
    else {
        if (Chara.camp->collisionCharaLeft(Chara.wx, Chara.wy) ||
            Chara.wx < Chara.camp->wx() //または、ウィンドウの左にぶつかったか
            ) {
            Chara.wx = WhiteKnight.curWx;
        }
    }
    // マップチップとキャラの上
    if (Chara.camp->collisionCharaTop(Chara.wx, Chara.wy)) {
        Chara.vy = WhiteKnight.initVecDown;//落ちていく初速度
    }
    // マップチップとキャラの下
    if (Chara.camp->collisionCharaBottom(WhiteKnight.curWx, Chara.wy)) {
        //--「マップチップに食い込んでいる」
        // または「上に立っているとき」もここを通る--
        //ジャンプ（落下）処理の停止
        WhiteKnight.jumpFlag = 0;
        Chara.vy = 0.0f;
        //強制的に上に立っている位置にする
        Chara.wy = (int)Chara.wy / Chara.camp->chipSize() * (float)Chara.camp->chipSize();
    }
    else {
        WhiteKnight.jumpFlag = 1;//落ちてくトリガー。このフラッグを立てるだけで落ちていく。
    }
}
void WHITE_KNIGHT::damage() {
    if (Chara.hp > 0) {
        Chara.hp--;
    }
}