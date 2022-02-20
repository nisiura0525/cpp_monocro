#include "WHITE_ROOK.h"
#include"rand.h"
#include"window.h"
#include"ANIM.h"
#include"CONTAINER.h"
#include"GAME.h"
#include"MAP.h"
void WHITE_ROOK::create() {
    Chara = game()->container()->data().whiteRookChara;
    WhiteRook = game()->container()->data().whiteRook;
    cmap();
}
void WHITE_ROOK::appear(float wx, float wy, float vx, float vy) {
    Chara.hp = game()->container()->data().whiteRookChara.hp;
    Chara.wx = wx;
    Chara.wy = wy;
    Chara.vx = WhiteRook.initVecX;
    Chara.vy = WhiteRook.initVecY;
    Chara.animId = WhiteRook.leftAnimId;
    WhiteRook.ac = 0;
    WhiteRook.acCurTime = WhiteRook.acInterval * random(0.1f, 5.0f);
    WhiteRook.damageTime = 0;
    WhiteRook.fallFlag = 0;
}
void WHITE_ROOK::update() {
    Move();
    CollisionWithMap();
    ChangeColor();
}
void WHITE_ROOK::Move() {
    //����
    if (WhiteRook.fallFlag) {
        Chara.vy += WhiteRook.gravity * delta;
        Chara.wy += Chara.vy * 60 * delta;
    }
    //���݂̈ʒu���Ƃ��Ă���
    WhiteRook.curWx = Chara.wx;
    //���E�ɂ�����
    if (WhiteRook.acCurTime <= 0) {
        WhiteRook.ac = 500.0f;
    }
    else WhiteRook.acCurTime -= delta;
    Chara.wx += Chara.vx * ((Chara.speed + WhiteRook.ac) * delta);
}
void WHITE_ROOK::CollisionWithMap() {
    // �}�b�v�`�b�v�ɂԂ������������ς���
    if (WhiteRook.fallFlag == 0) {
        if (Chara.camp->collisionCharaLeft(Chara.wx, Chara.wy) ||
            Chara.camp->collisionCharaRight(Chara.wx, Chara.wy)) {
            Chara.animId = 1 - Chara.animId;
            Chara.vx = -Chara.vx;
            Chara.wx = WhiteRook.curWx;
            WhiteRook.ac *= 0.0f;
            WhiteRook.acCurTime = WhiteRook.acInterval;
        }
    }
    // �ڒn�`�F�b�N�i�L�����̉��Ƀ}�b�v�`�b�v�����邩�ǂ����j
    if (Chara.camp->collisionCharaBottom(WhiteRook.curWx, Chara.wy)) {
        //�ڒn�܂��͖��܂��Ă���
        WhiteRook.fallFlag = 0;
        Chara.vy = 0;
        //���܂�Ȃ��悤�ɍ�����␳����
        Chara.wy = (int)Chara.wy / Chara.camp->chipSize() * (float)Chara.camp->chipSize();
    }
    else {//�ڒn���Ă��Ȃ�
        WhiteRook.fallFlag = 1;//���Ƃ�
    }
    // �E�B���h�E�̊O�ɏo��
    if (Chara.wx < Chara.camp->wDispLeft()) {
        Chara.hp = 0;
    }
}
void WHITE_ROOK::ChangeColor() {
    //�_���[�W���󂯂���u�Ԃ����F��ς���
    if (WhiteRook.damageTime > 0) {
        WhiteRook.damageTime -= delta;
        Chara.color = WhiteRook.damageColor;
    }
    else {
        Chara.color = WhiteRook.normalColor;
    }
}
void WHITE_ROOK::damage() {
    if (Chara.hp > 0) {
        WhiteRook.damageTime = WhiteRook.damageInterval;
        Chara.hp--;
        if (Chara.hp == 0) {
            game()->characterManager()->appear(WhiteRook.explosionCharaId,
                Chara.wx, Chara.wy);
        }
    }
}