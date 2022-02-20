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
    //����
    if (WhitePawn.fallFlag) {
        Chara.vy += WhitePawn.gravity * delta;
        Chara.wy += Chara.vy * 60 * delta;
    }
    //���݂̈ʒu���Ƃ��Ă���
    WhitePawn.curWx = Chara.wx;
    //���E�ɂ�����
    Chara.wx += Chara.vx * (Chara.speed * delta);
}
void WHITE_PAWN::CollisionWithMap() {
    // �}�b�v�`�b�v�ɂԂ������������ς���
    if (WhitePawn.fallFlag == 0) {
        if (Chara.camp->collisionCharaLeft(Chara.wx, Chara.wy) ||
            Chara.camp->collisionCharaRight(Chara.wx, Chara.wy)) {
            Chara.animId = 1 - Chara.animId;
            Chara.vx = -Chara.vx;
            Chara.wx = WhitePawn.curWx;
        }
    }
    // �ڒn�`�F�b�N�i�L�����̉��Ƀ}�b�v�`�b�v�����邩�ǂ����j
    if (Chara.camp->collisionCharaBottom(WhitePawn.curWx, Chara.wy)) {
        //�ڒn�܂��͖��܂��Ă���
        WhitePawn.fallFlag = 0;
        Chara.vy = 0;
        //���܂�Ȃ��悤�ɍ�����␳����
        Chara.wy = (int)Chara.wy / Chara.camp->chipSize() * (float)Chara.camp->chipSize();
    }
    else {//�ڒn���Ă��Ȃ�
        WhitePawn.fallFlag = 1;//���Ƃ�
    }
    // �E�B���h�E�̊O�ɏo��
    if (Chara.wx < Chara.camp->wDispLeft()) {
        Chara.hp = 0;
    }
}
void WHITE_PAWN::ChangeColor() {
    //�_���[�W���󂯂���u�Ԃ����F��ς���
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