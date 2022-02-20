#include "BISHOP_BULLET.h"
#include"window.h"
#include"CONTAINER.h"
#include"GAME.h"
#include"MAP.h"
void BISHOP_BULLET::create() {
	Chara = game()->container()->data().bishopBulletChara;
}
void BISHOP_BULLET::update() {
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