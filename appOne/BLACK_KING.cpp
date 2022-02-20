#include "BLACK_KING.h"
#include"window.h"
#include"ANIM.h"
#include"rand.h"
#include"CONTAINER.h"
#include"GAME.h"
#include"MAP.h"
void BLACK_KING::create() {
    Chara = game()->container()->data().blackKingChara;
    BlackKing = game()->container()->data().blackKing;
    cmap();
}
void BLACK_KING::appear(float wx, float wy, float vx, float vy) {
    Chara.hp = game()->container()->data().blackKingChara.hp;
    Chara.wx = wx;
    Chara.wy = wy ;
    Chara.vx = BlackKing.initVecX;
    Chara.vy = BlackKing.initVecY;
    Chara.animId = BlackKing.leftAnimId;
    BlackKing.ac = 0;
    BlackKing.acCurTime = BlackKing.acInterval * 0.5f;
    BlackKing.damageTime = 0;
    BlackKing.fallFlag = 0;
}
void BLACK_KING::init() {
    Chara.hp = -1;
}
void BLACK_KING::update() {
    Move();
    CollisionWithMap();
    ChangeColor();
}
void BLACK_KING::Summons() {
    float vx = -1;
    if (Chara.wx > game()->characterManager()->blackPlayer()->wx()) {
        vx = -1;
    }
    else vx = 1;
    if (BlackKing.summonNumber == 0) {
        game()->characterManager()->appear(MAP::CHARA_ID::BLACK_PAWN_ID, Chara.wx, Chara.wy, vx, 0);
    }
    if (BlackKing.summonNumber == 1 || BlackKing.summonNumber == 4) {
        game()->characterManager()->appear(MAP::CHARA_ID::BLACK_ROOK_ID, Chara.wx, Chara.wy, vx, 0);
        game()->characterManager()->appear(MAP::CHARA_ID::BLACK_PAWN_ID, Chara.wx, Chara.wy, vx, 0);
    }
    if (BlackKing.summonNumber == 2) {
        game()->characterManager()->appear(MAP::CHARA_ID::BLACK_BISHOP_ID, Chara.wx, Chara.wy, vx, 0);
        game()->characterManager()->appear(MAP::CHARA_ID::BLACK_PAWN_ID, Chara.wx, Chara.wy, vx, 0);
    }
    if (BlackKing.summonNumber == 3) {
        game()->characterManager()->appear(MAP::CHARA_ID::BLACK_ROOK_ID, Chara.wx, Chara.wy, vx, 0);
    }
    if (BlackKing.summonNumber == 4) {
        game()->characterManager()->appear(MAP::CHARA_ID::BLACK_BISHOP_ID, Chara.wx, Chara.wy, vx, 0);
    }
    if (BlackKing.summonNumber == 5) {
        game()->characterManager()->appear(MAP::CHARA_ID::BLACK_KNIGHT_ID, Chara.wx, Chara.wy, vx, 0);
    }
}
void BLACK_KING::Move() {
    //����
    if (BlackKing.fallFlag) {
        Chara.vy += BlackKing.gravity * delta;
        Chara.wy += Chara.vy * 60 * delta;
    }
    //���݂̈ʒu���Ƃ��Ă���
    BlackKing.curWx = Chara.wx;
    //���E�ɂ�����
    if (BlackKing.acCurTime <= 0) {
        Summons();
        BlackKing.summonNumber = random(0, 5);
        BlackKing.acCurTime = BlackKing.acInterval;
    }
    else BlackKing.acCurTime -= delta;
    Chara.wx += Chara.vx * ((Chara.speed + BlackKing.ac) * delta);
}
void BLACK_KING::CollisionWithMap() {

    Chara.vx = 1;
    // �}�b�v�`�b�v�ɂԂ�������W�����v
    if (BlackKing.fallFlag == 0) {
        if (Chara.camp->collisionCharaLeft(Chara.wx-25 , Chara.wy) ||
            Chara.camp->collisionCharaRight(Chara.wx+25, Chara.wy)) {
            Chara.wx = BlackKing.curWx;
            if (BlackKing.jumpFlag == 0) {
                Chara.vy = BlackKing.initVecUp;
                BlackKing.jumpFlag = 1;
            }
            if (BlackKing.jumpFlag == 1) {
                Chara.vy += BlackKing.gravity * delta;
                Chara.wy += Chara.vy * 60 * delta;
                BlackKing.jumpFlag = 0;
            }
        }
    }
    // �ڒn�`�F�b�N�i�L�����̉��Ƀ}�b�v�`�b�v�����邩�ǂ����j
    if (Chara.camp->collisionCharaBottom(BlackKing.curWx, Chara.wy)) {
        //�ڒn�܂��͖��܂��Ă���
        BlackKing.fallFlag = 0;
        Chara.vy = 0;
        //���܂�Ȃ��悤�ɍ�����␳����
       
        Chara.wy = ((int)Chara.wy/ Chara.camp->chipSize() * (float)Chara.camp->chipSize());
       // Chara.wy +=-50;
    }
    else {//�ڒn���Ă��Ȃ�
        BlackKing.fallFlag = 1;//���Ƃ�
    }
    // �E�B���h�E�̊O�ɏo��
    if (Chara.wx < Chara.camp->wDispLeft()) {
        Chara.hp = 0;
    }
}
void BLACK_KING::draw() {
    imageColor(Chara.color);
    float px = Chara.wx - Chara.camp->wx();
    float py = Chara.wy - Chara.camp->wy()-50;
    image(Chara.img, px, py, Chara.angle, Chara.scale);
    deth();
}
void BLACK_KING::ChangeColor() {
    //�_���[�W���󂯂���u�Ԃ����F��ς���
    if (BlackKing.damageTime > 0) {
        BlackKing.damageTime -= delta;
        Chara.color = BlackKing.damageColor;
    }
    else {
        Chara.color = BlackKing.normalColor;
    }
}
void BLACK_KING::damage() {
    if (Chara.hp > 0) {
        BlackKing.damageTime = BlackKing.damageInterval;
        Chara.hp--;
    }
}
void BLACK_KING::deth() {
   if (Chara.hp == 0) {
        fill(50);
        textSize(100);
        if (Chara.hp <= 0) {
            text("1P�@���̏���", (width - 700) / 2, 200);
            game()->stage()->gameclearLogo(game()->container()->data().stage.gameClearImg, game()->container()->data().stage.stageClearColor, (width - 800) / 2, height / (2 + 300));
        }
   }
}