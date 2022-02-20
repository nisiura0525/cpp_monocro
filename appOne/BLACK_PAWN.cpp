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
    //����
    if (BlackPawn.fallFlag) {
        Chara.vy += BlackPawn.gravity * delta;
        Chara.wy += Chara.vy * 60 * delta;
    }
    //���݂̈ʒu���Ƃ��Ă���
    BlackPawn.curWx = Chara.wx;
    //���E�ɂ�����
    Chara.wx += Chara.vx * (Chara.speed * delta);
}
void BLACK_PAWN::CollisionWithMap() {
    // �}�b�v�`�b�v�ɂԂ������������ς���
    if (BlackPawn.fallFlag == 0) {
        if (Chara.camp->collisionCharaLeft(Chara.wx, Chara.wy) ||
            Chara.camp->collisionCharaRight(Chara.wx, Chara.wy)) {
            Chara.animId = 1 - Chara.animId;
            Chara.vx = -Chara.vx;
            Chara.wx = BlackPawn.curWx;
        }
    }
    // �ڒn�`�F�b�N�i�L�����̉��Ƀ}�b�v�`�b�v�����邩�ǂ����j
    if (Chara.camp->collisionCharaBottom(BlackPawn.curWx, Chara.wy)) {
        //�ڒn�܂��͖��܂��Ă���
        BlackPawn.fallFlag = 0;
        Chara.vy = 0;
        //���܂�Ȃ��悤�ɍ�����␳����
        Chara.wy = (int)Chara.wy / Chara.camp->chipSize() * (float)Chara.camp->chipSize();
    }
    else {//�ڒn���Ă��Ȃ�
        BlackPawn.fallFlag = 1;//���Ƃ�
    }
    // �E�B���h�E�̊O�ɏo��
    if (Chara.wx < Chara.camp->wDispLeft()) {
        Chara.hp = 0;
    }
}
void BLACK_PAWN::ChangeColor() {
    //�_���[�W���󂯂���u�Ԃ����F��ς���
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