#include "BLACK_PLAYER.h"
#include"window.h"
#include"input.h"
#include"graphic.h"
#include"ANIMS.h"
#include"CONTAINER.h"
#include"GAME.h"
#include"BLACK_WORLD.h"
#include"PBULLET.h"
void BLACK_PLAYER::create() {
    Chara = game()->container()->data().bplayerChara;
    BlackPlayer = game()->container()->data().bplayer;
    cmap();
}
void BLACK_PLAYER::appear(float wx, float wy, float vx, float vy) {
    Chara.hp = game()->container()->data().bplayerChara.hp;
    Chara.wx = wx;
    Chara.wy = wy;
    Chara.animId = BlackPlayer.rightAnimId;
    BlackPlayer.jumpFlag = 0;
    BlackPlayer.bulletsR = BlackPlayer.bulletsM;
    BlackPlayer.CurTime = BlackPlayer.ReloadInterval;
    State = STATE::STRUGGLING;
}
void BLACK_PLAYER::resetState() {
    BlackPlayer.ReLife = game()->container()->data().bplayer.ReLife;
    State = STATE::STRUGGLING;
}
void BLACK_PLAYER::update() {
    Launch();
    Move();
    CollisionWithMap();
    CheckState();
}
void BLACK_PLAYER::Launch() {
    //弾発射
    if (isTrigger(KEY_F)) {
        if (BlackPlayer.bulletsR > 0) {
            float vx = 1.0f;
            if (Chara.animId == BlackPlayer.leftAnimId) vx = -1.0f;
            float wx = Chara.wx + BlackPlayer.bulletOffsetX * vx;
            float wy = Chara.wy;
            game()->characterManager()->bulletAppear(BlackPlayer.bulletCharaId, wx, wy, Chara.campId, vx);
            BlackPlayer.bulletsR--;
        }
    }
    if (isTrigger(KEY_R)) BlackPlayer.bulletsR = 0;
    if (BlackPlayer.bulletsR <= 0) {
        if (BlackPlayer.CurTime <= 0) {
            BlackPlayer.bulletsR = BlackPlayer.bulletsM;
            BlackPlayer.CurTime = BlackPlayer.ReloadInterval;
        }
        else
            BlackPlayer.CurTime -= delta;
    }
}
void BLACK_PLAYER::Move() {
    //ジャンプ
    if (BlackPlayer.jumpFlag == 0 && isTrigger(KEY_W)) {
        Chara.vy = BlackPlayer.initVecUp;
        BlackPlayer.jumpFlag = 1;
    }
    if (BlackPlayer.jumpFlag == 1) {
        Chara.vy += BlackPlayer.gravity * delta;
        Chara.wy += Chara.vy * 60 * delta;
    }
    //左右移動
    //  移動ベクトルを決定
    Chara.vx = 0.0f;
    if (isPress(KEY_A)) {
        Chara.vx = -Chara.speed * delta;
        Chara.animId = BlackPlayer.leftAnimId;
    }
    if (isPress(KEY_D)) {
        Chara.vx = Chara.speed * delta;
        Chara.animId = BlackPlayer.rightAnimId;
    }
    //  移動前に現在のChara.wxをPlayer.curWxにとっておく
    BlackPlayer.curWx = Chara.wx;
    //  移動
    if (Chara.vx != 0.0f) {//左右キー入力あり
        //とりあえず「次に移動する予定」の位置としてChara.wxを更新しておき
        //あとで、マップに食い込んでいたら、元のPlayer.curWxに戻す
        Chara.wx += Chara.vx;
    }
    else {//左右キー入力がないとき
        Chara.animData.imgIdx = 0;
        Chara.animData.elapsedTime = -delta;
    }
}
void BLACK_PLAYER::CollisionWithMap() {
    // マップチップとキャラの右
    if (Chara.animId == BlackPlayer.rightAnimId) {
        if (Chara.camp->collisionCharaRight(Chara.wx, Chara.wy)) {
            //移動予定位置がマップに食い込んでいるので現在の位置に戻す
            Chara.wx = BlackPlayer.curWx;
        }
    }
    // マップチップとキャラの左
    else {
        if (Chara.camp->collisionCharaLeft(Chara.wx, Chara.wy) ||
            Chara.wx < Chara.camp->wx() //または、ウィンドウの左にぶつかったか
            ) {
            Chara.wx = BlackPlayer.curWx;
        }
    }
    // マップチップとキャラの上
    if (Chara.camp->collisionCharaTop(Chara.wx, Chara.wy)) {
        Chara.vy = BlackPlayer.initVecDown;//落ちていく初速度
    }
    // マップチップとキャラの下
    if (Chara.camp->collisionCharaBottom(BlackPlayer.curWx, Chara.wy)) {
        //--「マップチップに食い込んでいる」
        // または「上に立っているとき」もここを通る--
        //ジャンプ（落下）処理の停止
        BlackPlayer.jumpFlag = 0;
        Chara.vy = 0.0f;
        //強制的に上に立っている位置にする
        Chara.wy = (int)Chara.wy / Chara.camp->chipSize() * (float)Chara.camp->chipSize();
    }
    else {
        BlackPlayer.jumpFlag = 1;//落ちてくトリガー。このフラッグを立てるだけで落ちていく。
    }
}
void BLACK_PLAYER::CheckState() {
    //画面の下に落ちた
    if (Chara.wy > height + game()->blackWorld()->chipSize()) {
        State = STATE::DIED;
        Chara.hp = 0;
        BlackPlayer.ReLife--;
        return;
    }
    //ステージクリアした
    if (Chara.wx > game()->blackWorld()->wDispRight()) {
        State = STATE::SURVIVED;
        Chara.hp = 0;
    }
}
void BLACK_PLAYER::damage() {
    if (Chara.hp > 0) {
        Chara.hp--;
        if (Chara.hp == 0) {
            BlackPlayer.ReLife--;
            State = STATE::DIED;
            Chara.vy = BlackPlayer.initVecUp;//はね始めのトリガー
        }
    }
}
bool BLACK_PLAYER::died() {
    if (State == STATE::DIED) {
        Chara.vy += BlackPlayer.gravity * delta;
        Chara.wy += Chara.vy * 60 * delta;
        draw();
        return true;
    }
    else if (State == STATE::FALL) {
        return true;
    }
    return false;
}
bool BLACK_PLAYER::survived() {
    return State == STATE::SURVIVED;
}
float BLACK_PLAYER::overCenterVx() {
    //マップをスクロールさせるためのベクトルを求める
    float centerWx = (game()->blackWorld()->wx() + width / 2 - game()->blackWorld()->chipSize() / 2);
    float overCenterVx = Chara.wx - centerWx;
    if (overCenterVx < 0 || Chara.hp == 0)overCenterVx = 0;
    return overCenterVx;
}