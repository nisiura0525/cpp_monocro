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
    //�e����
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
    //�W�����v
    if (BlackPlayer.jumpFlag == 0 && isTrigger(KEY_W)) {
        Chara.vy = BlackPlayer.initVecUp;
        BlackPlayer.jumpFlag = 1;
    }
    if (BlackPlayer.jumpFlag == 1) {
        Chara.vy += BlackPlayer.gravity * delta;
        Chara.wy += Chara.vy * 60 * delta;
    }
    //���E�ړ�
    //  �ړ��x�N�g��������
    Chara.vx = 0.0f;
    if (isPress(KEY_A)) {
        Chara.vx = -Chara.speed * delta;
        Chara.animId = BlackPlayer.leftAnimId;
    }
    if (isPress(KEY_D)) {
        Chara.vx = Chara.speed * delta;
        Chara.animId = BlackPlayer.rightAnimId;
    }
    //  �ړ��O�Ɍ��݂�Chara.wx��Player.curWx�ɂƂ��Ă���
    BlackPlayer.curWx = Chara.wx;
    //  �ړ�
    if (Chara.vx != 0.0f) {//���E�L�[���͂���
        //�Ƃ肠�����u���Ɉړ�����\��v�̈ʒu�Ƃ���Chara.wx���X�V���Ă���
        //���ƂŁA�}�b�v�ɐH������ł�����A����Player.curWx�ɖ߂�
        Chara.wx += Chara.vx;
    }
    else {//���E�L�[���͂��Ȃ��Ƃ�
        Chara.animData.imgIdx = 0;
        Chara.animData.elapsedTime = -delta;
    }
}
void BLACK_PLAYER::CollisionWithMap() {
    // �}�b�v�`�b�v�ƃL�����̉E
    if (Chara.animId == BlackPlayer.rightAnimId) {
        if (Chara.camp->collisionCharaRight(Chara.wx, Chara.wy)) {
            //�ړ��\��ʒu���}�b�v�ɐH������ł���̂Ō��݂̈ʒu�ɖ߂�
            Chara.wx = BlackPlayer.curWx;
        }
    }
    // �}�b�v�`�b�v�ƃL�����̍�
    else {
        if (Chara.camp->collisionCharaLeft(Chara.wx, Chara.wy) ||
            Chara.wx < Chara.camp->wx() //�܂��́A�E�B���h�E�̍��ɂԂ�������
            ) {
            Chara.wx = BlackPlayer.curWx;
        }
    }
    // �}�b�v�`�b�v�ƃL�����̏�
    if (Chara.camp->collisionCharaTop(Chara.wx, Chara.wy)) {
        Chara.vy = BlackPlayer.initVecDown;//�����Ă��������x
    }
    // �}�b�v�`�b�v�ƃL�����̉�
    if (Chara.camp->collisionCharaBottom(BlackPlayer.curWx, Chara.wy)) {
        //--�u�}�b�v�`�b�v�ɐH������ł���v
        // �܂��́u��ɗ����Ă���Ƃ��v��������ʂ�--
        //�W�����v�i�����j�����̒�~
        BlackPlayer.jumpFlag = 0;
        Chara.vy = 0.0f;
        //�����I�ɏ�ɗ����Ă���ʒu�ɂ���
        Chara.wy = (int)Chara.wy / Chara.camp->chipSize() * (float)Chara.camp->chipSize();
    }
    else {
        BlackPlayer.jumpFlag = 1;//�����Ă��g���K�[�B���̃t���b�O�𗧂Ă邾���ŗ����Ă����B
    }
}
void BLACK_PLAYER::CheckState() {
    //��ʂ̉��ɗ�����
    if (Chara.wy > height + game()->blackWorld()->chipSize()) {
        State = STATE::DIED;
        Chara.hp = 0;
        BlackPlayer.ReLife--;
        return;
    }
    //�X�e�[�W�N���A����
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
            Chara.vy = BlackPlayer.initVecUp;//�͂ˎn�߂̃g���K�[
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
    //�}�b�v���X�N���[�������邽�߂̃x�N�g�������߂�
    float centerWx = (game()->blackWorld()->wx() + width / 2 - game()->blackWorld()->chipSize() / 2);
    float overCenterVx = Chara.wx - centerWx;
    if (overCenterVx < 0 || Chara.hp == 0)overCenterVx = 0;
    return overCenterVx;
}