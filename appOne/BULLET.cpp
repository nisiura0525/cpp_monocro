#include "BULLET.h"
#include"window.h"
#include"ANIM.h"
#include"CONTAINER.h"
#include"GAME.h"
#include"MAP.h"
void BULLET::create() {
    //Chara = game()->container()->data().blackBulletChara;
}
void BULLET::appear(float wx, float wy, float vx, float vy,char campId,int curbullet) {
    curBullet = curbullet;
    Chara.hp = 1;
    Chara.wx = wx;
    Chara.wy = wy;
    Chara.vx = vx;
    Chara.vy = vy;
    Chara.campId = campId;
    this->cmap();
    Chara.initWx = wx;
}
void BULLET::update() {
    //�ړ�--------------------------------------------------------------------------
    Chara.wx += Chara.vx * (Chara.speed * delta);
    //�}�b�v------------------------------------------------------------------------
    // �e���A�}�b�v�`�b�v�ɓ��������A�܂��́A�E�B���h�E�̊O�ɏo��
    if (Chara.camp->collisionCharaRect(wLeft(), wTop(), wRight(), wBottom()) ||
        Chara.wx < Chara.camp->wDispLeft() ||
        Chara.wx > Chara.camp->wDispRight()) {
        Chara.hp = 0;
    }
}