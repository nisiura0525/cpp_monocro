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
    //�e����
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
    //�W�����v
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
    //���E�ړ�
    //  �ړ��x�N�g��������
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
    //  �ړ��O�Ɍ��݂�Chara.wx��Knight.curWx�ɂƂ��Ă���
    BlackKnight.curWx = Chara.wx;
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
void BLACK_KNIGHT::CollisionWithMap() {
    // �}�b�v�`�b�v�ƃL�����̉E
    if (Chara.animId == BlackKnight.rightAnimId) {
        if (Chara.camp->collisionCharaRight(Chara.wx, Chara.wy)) {
            //�ړ��\��ʒu���}�b�v�ɐH������ł���̂Ō��݂̈ʒu�ɖ߂�
            Chara.wx = BlackKnight.curWx;
        }
    }
    // �}�b�v�`�b�v�ƃL�����̍�
    else {
        if (Chara.camp->collisionCharaLeft(Chara.wx, Chara.wy) ||
            Chara.wx < Chara.camp->wx() //�܂��́A�E�B���h�E�̍��ɂԂ�������
            ) {
            Chara.wx = BlackKnight.curWx;
        }
    }
    // �}�b�v�`�b�v�ƃL�����̏�
    if (Chara.camp->collisionCharaTop(Chara.wx, Chara.wy)) {
        Chara.vy = BlackKnight.initVecDown;//�����Ă��������x
    }
    // �}�b�v�`�b�v�ƃL�����̉�
    if (Chara.camp->collisionCharaBottom(BlackKnight.curWx, Chara.wy)) {
        //--�u�}�b�v�`�b�v�ɐH������ł���v
        // �܂��́u��ɗ����Ă���Ƃ��v��������ʂ�--
        //�W�����v�i�����j�����̒�~
        BlackKnight.jumpFlag = 0;
        Chara.vy = 0.0f;
        //�����I�ɏ�ɗ����Ă���ʒu�ɂ���
        Chara.wy = (int)Chara.wy / Chara.camp->chipSize() * (float)Chara.camp->chipSize();
    }
    else {
        BlackKnight.jumpFlag = 1;//�����Ă��g���K�[�B���̃t���b�O�𗧂Ă邾���ŗ����Ă����B
    }
}
void BLACK_KNIGHT::damage() {
    if (Chara.hp > 0) {
        Chara.hp--;
    }
}