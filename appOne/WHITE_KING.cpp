#include "WHITE_KING.h"
#include"window.h"
#include"ANIM.h"
#include"rand.h"
#include"CONTAINER.h"
#include"GAME.h"
#include"MAP.h"
void WHITE_KING::create() {
    Chara = game()->container()->data().whiteKingChara;
    WhiteKing = game()->container()->data().whiteKing;
    cmap();
}
void WHITE_KING::appear(float wx, float wy, float vx, float vy) {
    Chara.hp = game()->container()->data().whiteKingChara.hp;
    Chara.wx = wx;
    Chara.wy = wy;
    Chara.vx = WhiteKing.initVecX;
    Chara.vy = WhiteKing.initVecY;
    Chara.animId = WhiteKing.leftAnimId;
    WhiteKing.ac = 0;
    WhiteKing.acCurTime = WhiteKing.acInterval*0.5f;
    WhiteKing.damageTime = 0;
    WhiteKing.fallFlag = 0;
}
void WHITE_KING::init() {
    Chara.hp = -1;
}
void WHITE_KING::update() {
    Move();
    CollisionWithMap();
    ChangeColor();
}
void WHITE_KING::Summons() {
    float vx = -1;
    if (Chara.wx > game()->characterManager()->whitePlayer()->wx()) {
        vx = -1;
    }
    else vx = 1;
    if (WhiteKing.summonNumber == 0) {
        game()->characterManager()->appear(MAP::CHARA_ID::WHITE_PAWN_ID, Chara.wx, Chara.wy, vx, 0);
    }
    if (WhiteKing.summonNumber == 1|| WhiteKing.summonNumber == 4) {
        game()->characterManager()->appear(MAP::CHARA_ID::WHITE_ROOK_ID, Chara.wx, Chara.wy, vx, 0);
        game()->characterManager()->appear(MAP::CHARA_ID::WHITE_PAWN_ID, Chara.wx, Chara.wy, vx, 0);
    }
    if (WhiteKing.summonNumber == 2) {
        game()->characterManager()->appear(MAP::CHARA_ID::WHITE_BISHOP_ID, Chara.wx, Chara.wy, vx, 0);
        game()->characterManager()->appear(MAP::CHARA_ID::WHITE_PAWN_ID, Chara.wx, Chara.wy, vx, 0);
    }
    if (WhiteKing.summonNumber == 3) {
        game()->characterManager()->appear(MAP::CHARA_ID::WHITE_ROOK_ID, Chara.wx, Chara.wy, vx, 0);
    }
    if (WhiteKing.summonNumber == 4) {
        game()->characterManager()->appear(MAP::CHARA_ID::WHITE_BISHOP_ID, Chara.wx, Chara.wy, vx, 0);
    }
    if (WhiteKing.summonNumber == 5) {
        game()->characterManager()->appear(MAP::CHARA_ID::WHITE_KNIGHT_ID, Chara.wx, Chara.wy, vx, 0);
    }
}
void WHITE_KING::Move() {
    //落下
    if (WhiteKing.fallFlag) {
        Chara.vy += WhiteKing.gravity * delta;
        Chara.wy += Chara.vy * 60 * delta;
    }
    //現在の位置をとっておく
    WhiteKing.curWx = Chara.wx;
    //左右にうごく
    if (WhiteKing.acCurTime <= 0) {
        Summons();
        WhiteKing.summonNumber = random(0,5);
        WhiteKing.acCurTime = WhiteKing.acInterval;
    }
    else WhiteKing.acCurTime -= delta;
    Chara.wx += Chara.vx * ((Chara.speed + WhiteKing.ac) * delta);
}
void WHITE_KING::CollisionWithMap() {
    Chara.vx = 1;
    // マップチップにぶつかったらジャンプ
    if (WhiteKing.fallFlag == 0) {
        if (Chara.camp->collisionCharaLeft(Chara.wx, Chara.wy) ||
            Chara.camp->collisionCharaRight(Chara.wx, Chara.wy)) {
            Chara.wx = WhiteKing.curWx;
            if (WhiteKing.jumpFlag == 0) {
                Chara.vy = WhiteKing.initVecUp;
                WhiteKing.jumpFlag = 1;
            }
            if (WhiteKing.jumpFlag == 1) {
                Chara.vy += WhiteKing.gravity * delta;
                Chara.wy += Chara.vy * 60 * delta;
                WhiteKing.jumpFlag = 0;
            }
        }
    }
    // 接地チェック（キャラの下にマップチップがあるかどうか）
    if (Chara.camp->collisionCharaBottom(WhiteKing.curWx, Chara.wy)) {
        //接地または埋まっている
        WhiteKing.fallFlag = 0;
        Chara.vy = 0;
        //埋まらないように高さを補正する
        Chara.wy = (int)Chara.wy / Chara.camp->chipSize() * (float)Chara.camp->chipSize();
    }
    else {//接地していない
        WhiteKing.fallFlag = 1;//落とす
    }
    // ウィンドウの外に出た
    if (Chara.wx < Chara.camp->wDispLeft()) {
        Chara.hp = 0;
    }
}
void WHITE_KING::draw() {
    imageColor(Chara.color);
    float px = Chara.wx - Chara.camp->wx();
    float py = Chara.wy - Chara.camp->wy() -50;
    image(Chara.img, px, py, Chara.angle, Chara.scale);
}
void WHITE_KING::ChangeColor() {
    //ダメージを受けたら瞬間だけ色を変える
    if (WhiteKing.damageTime > 0) {
        WhiteKing.damageTime -= delta;
        Chara.color = WhiteKing.damageColor;
    }
    else {
        Chara.color = WhiteKing.normalColor;
    }
}
void WHITE_KING::damage() {
    if (Chara.hp > 0) {
        WhiteKing.damageTime = WhiteKing.damageInterval;
        Chara.hp--;
    }
}
void WHITE_KING::deth() {
    if (Chara.hp == 0) {
        fill(50);
        textSize(100);
        if (Chara.hp <= 0) {
            text("2P　白の勝ち", (width - 700) / 2, 200);
            game()->stage()->gameclearLogo(game()->container()->data().stage.gameClearImg, game()->container()->data().stage.stageClearColor, (width - 800) / 2, height / (2 + 300));
        }
    }
}