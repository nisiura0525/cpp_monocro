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
    //�e����
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
    //�W�����v
    if (WhiteBishop.jumpFlag == 0 && isTrigger(KEY_W)) {
        Chara.vy = WhiteBishop.initVecUp;
        WhiteBishop.jumpFlag = 1;
    }
    if (WhiteBishop.jumpFlag == 1) {
        Chara.vy += WhiteBishop.gravity * delta;
        Chara.wy += Chara.vy * 60 * delta;
    }
    //���E�ړ�
    //  �ړ��x�N�g��������
    Chara.vx = 0.0f;
    if (isPress(KEY_A)) {
        Chara.vx = -Chara.speed * delta;
        Chara.animId = WhiteBishop.leftAnimId;
    }
    if (isPress(KEY_D)) {
        Chara.vx = Chara.speed * delta;
        Chara.animId = WhiteBishop.rightAnimId;
    }
    //  �ړ��O�Ɍ��݂�Chara.wx��Bishop.curWx�ɂƂ��Ă���
    WhiteBishop.curWx = Chara.wx;
    //  �ړ�
    if (Chara.vx != 0.0f) {//���E�L�[���͂���
        //�Ƃ肠�����u���Ɉړ�����\��v�̈ʒu�Ƃ���Chara.wx���X�V���Ă���
        //���ƂŁA�}�b�v�ɐH������ł�����A����Bishop.curWx�ɖ߂�
        Chara.wx += Chara.vx;
    }
    else {//���E�L�[���͂��Ȃ��Ƃ�
        Chara.animData.imgIdx = 0;
        Chara.animData.elapsedTime = -delta;
    }
*/
}
/*
void White_BISHOP::CollisionWithMap() {
    // �}�b�v�`�b�v�ƃL�����̉E
    if (Chara.animId == WhiteBishop.rightAnimId) {
        if (Chara.camp->collisionCharaRight(Chara.wx, Chara.wy)) {
            //�ړ��\��ʒu���}�b�v�ɐH������ł���̂Ō��݂̈ʒu�ɖ߂�
            Chara.wx = WhiteBishop.curWx;
        }
    }
    // �}�b�v�`�b�v�ƃL�����̍�
    else {
        if (Chara.camp->collisionCharaLeft(Chara.wx, Chara.wy) ||
            Chara.wx < Chara.camp->wx() //�܂��́A�E�B���h�E�̍��ɂԂ�������
            ) {
            Chara.wx = WhiteBishop.curWx;
        }
    }
    // �}�b�v�`�b�v�ƃL�����̏�
    if (Chara.camp->collisionCharaTop(Chara.wx, Chara.wy)) {
        Chara.vy = WhiteBishop.initVecDown;//�����Ă��������x
    }
    // �}�b�v�`�b�v�ƃL�����̉�
    if (Chara.camp->collisionCharaBottom(WhiteBishop.curWx, Chara.wy)) {
        //--�u�}�b�v�`�b�v�ɐH������ł���v
        // �܂��́u��ɗ����Ă���Ƃ��v��������ʂ�--
        //�W�����v�i�����j�����̒�~
        WhiteBishop.jumpFlag = 0;
        Chara.vy = 0.0f;
        //�����I�ɏ�ɗ����Ă���ʒu�ɂ���
        Chara.wy = (int)Chara.wy / Chara.camp->chipSize() * (float)Chara.camp->chipSize();
    }
    else {
        WhiteBishop.jumpFlag = 1;//�����Ă��g���K�[�B���̃t���b�O�𗧂Ă邾���ŗ����Ă����B
    }
}
*/
void WHITE_BISHOP::damage() {
    if (Chara.hp > 0) {
        WhiteBishop.damageTime = WhiteBishop.damageInterval;
        Chara.hp--;
        if (Chara.hp == 0) {
            //�����Ȃ�
        }
    }
}