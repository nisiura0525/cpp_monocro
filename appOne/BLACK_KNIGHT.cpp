#include "BLACK_KNIGHT.h"
#include"window.h"
#include"input.h"
#include"graphic.h"
#include"ANIMS.h"
#include"CONTAINER.h"
#include"GAME.h"
#include"BLACK_WORLD.h"
void BLACK_KNIGHT::create() {
    Chara = game()->container()->data().blackKnightChara;
    BlackKnight = game()->container()->data().blackKnight;
    cmap();
}
void BLACK_KNIGHT::appear(float wx, float wy, float vx, float vy) {
    Chara.hp = game()->container()->data().blackKnightChara.hp;
    Chara.wx = wx;
    Chara.wy = wy;
    Chara.animId = BlackKnight.rightAnimId;
    BlackKnight.jumpFlag = 0;
}
void BLACK_KNIGHT::update() {
    Launch();
    Move();
    CollisionWithMap();
}
void BLACK_KNIGHT::Launch() {
    //弾発射
    /*
    if (isTrigger(KEY_F)) {
        float vx = 1.0f;
        if (Chara.animId == BlackPlayer.leftAnimId) vx = -1.0f;
        float wx = Chara.wx + BlackPlayer.bulletOffsetX * vx;
        float wy = Chara.wy;
        game()->characterManager()->bulletAppear(BlackPlayer.bulletCharaId, wx, wy, Chara.campId, vx);
    }
    */
}
void BLACK_KNIGHT::Move() {
    //ジャンプ
    BlackKnight.jelpTime += delta;
    if (BlackKnight.jumpFlag == 0&&BlackKnight.jelpTime >= BlackKnight.jumpTrigger
        ) {
        Chara.vy = BlackKnight.initVecUp;
        BlackKnight.jumpFlag = 1;
        BlackKnight.jelpTime = 0;
    }
    if (BlackKnight.jumpFlag == 1) {
        Chara.vy += BlackKnight.gravity * delta;
        Chara.wy += Chara.vy * 60 * delta;
    }
    //左右移動
    //  移動ベクトルを決定
    Chara.vx = 0.0f;
    Chara.vx = Chara.speed * delta*BlackKnight.direction;
    if (moveleft(game()->characterManager()->blackPlayer()->wx())&&
        BlackKnight.jumpFlag == 0){
        BlackKnight.direction = -1;
        Chara.animId = BlackKnight.leftAnimId;
    }
    if (moveright(game()->characterManager()->blackPlayer()->wx()) && 
        BlackKnight.jumpFlag == 0) {
        BlackKnight.direction = 1;
        Chara.animId = BlackKnight.rightAnimId;
    }
    //  移動前に現在のChara.wxをKnight.curWxにとっておく
    BlackKnight.curWx = Chara.wx;
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
void BLACK_KNIGHT::CollisionWithMap() {
    // マップチップとキャラの右
    if (Chara.animId == BlackKnight.rightAnimId) {
        if (Chara.camp->collisionCharaRight(Chara.wx, Chara.wy)) {
            //移動予定位置がマップに食い込んでいるので現在の位置に戻す
            Chara.wx = BlackKnight.curWx;
        }
    }
    // マップチップとキャラの左
    else {
        if (Chara.camp->collisionCharaLeft(Chara.wx, Chara.wy) ||
            Chara.wx < Chara.camp->wx() //または、ウィンドウの左にぶつかったか
            ) {
            Chara.wx = BlackKnight.curWx;
        }
    }
    // マップチップとキャラの上
    if (Chara.camp->collisionCharaTop(Chara.wx, Chara.wy)) {
        Chara.vy = BlackKnight.initVecDown;//落ちていく初速度
    }
    // マップチップとキャラの下
    if (Chara.camp->collisionCharaBottom(BlackKnight.curWx, Chara.wy)) {
        //--「マップチップに食い込んでいる」
        // または「上に立っているとき」もここを通る--
        //ジャンプ（落下）処理の停止
        BlackKnight.jumpFlag = 0;
        Chara.vy = 0.0f;
        //強制的に上に立っている位置にする
        Chara.wy = (int)Chara.wy / Chara.camp->chipSize() * (float)Chara.camp->chipSize();
    }
    else {
        BlackKnight.jumpFlag = 1;//落ちてくトリガー。このフラッグを立てるだけで落ちていく。
    }
}
void BLACK_KNIGHT::damage() {
    if (Chara.hp > 0) {
        Chara.hp--;
    }
}