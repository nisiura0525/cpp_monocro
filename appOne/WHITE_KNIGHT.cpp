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
    //�e����
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
    //�W�����v
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
    //���E�ړ�
    //  �ړ��x�N�g��������
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
    //  �ړ��O�Ɍ��݂�Chara.wx��Knight.curWx�ɂƂ��Ă���
    WhiteKnight.curWx = Chara.wx;
    //  �ړ�
    if (Chara.vx != 0.0f) {//���E�L�[���͂���
        //�Ƃ肠�����u���Ɉړ�����\��v�̈ʒu�Ƃ���Chara.wx���X�V���Ă���
        //���ƂŁA�}�b�v�ɐH������ł�����A����Knight.curWx�ɖ߂�
        Chara.wx += Chara.vx;
    }
    else {//���E�L�[���͂��Ȃ��Ƃ�
        Chara.animData.imgIdx = 0;
        Chara.animData.elapsedTime = -delta;
    }
}
void WHITE_KNIGHT::CollisionWithMap() {
    // �}�b�v�`�b�v�ƃL�����̉E
    if (Chara.animId == WhiteKnight.rightAnimId) {
        if (Chara.camp->collisionCharaRight(Chara.wx, Chara.wy)) {
            //�ړ��\��ʒu���}�b�v�ɐH������ł���̂Ō��݂̈ʒu�ɖ߂�
            Chara.wx = WhiteKnight.curWx;
        }
    }
    // �}�b�v�`�b�v�ƃL�����̍�
    else {
        if (Chara.camp->collisionCharaLeft(Chara.wx, Chara.wy) ||
            Chara.wx < Chara.camp->wx() //�܂��́A�E�B���h�E�̍��ɂԂ�������
            ) {
            Chara.wx = WhiteKnight.curWx;
        }
    }
    // �}�b�v�`�b�v�ƃL�����̏�
    if (Chara.camp->collisionCharaTop(Chara.wx, Chara.wy)) {
        Chara.vy = WhiteKnight.initVecDown;//�����Ă��������x
    }
    // �}�b�v�`�b�v�ƃL�����̉�
    if (Chara.camp->collisionCharaBottom(WhiteKnight.curWx, Chara.wy)) {
        //--�u�}�b�v�`�b�v�ɐH������ł���v
        // �܂��́u��ɗ����Ă���Ƃ��v��������ʂ�--
        //�W�����v�i�����j�����̒�~
        WhiteKnight.jumpFlag = 0;
        Chara.vy = 0.0f;
        //�����I�ɏ�ɗ����Ă���ʒu�ɂ���
        Chara.wy = (int)Chara.wy / Chara.camp->chipSize() * (float)Chara.camp->chipSize();
    }
    else {
        WhiteKnight.jumpFlag = 1;//�����Ă��g���K�[�B���̃t���b�O�𗧂Ă邾���ŗ����Ă����B
    }
}
void WHITE_KNIGHT::damage() {
    if (Chara.hp > 0) {
        Chara.hp--;
    }
}