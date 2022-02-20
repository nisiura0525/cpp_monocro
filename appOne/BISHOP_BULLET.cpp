#include "BISHOP_BULLET.h"
#include"window.h"
#include"CONTAINER.h"
#include"GAME.h"
#include"MAP.h"
void BISHOP_BULLET::create() {
	Chara = game()->container()->data().bishopBulletChara;
}
void BISHOP_BULLET::update() {
    //移動--------------------------------------------------------------------------
    Chara.wx += Chara.vx * (Chara.speed * delta);
    //マップ------------------------------------------------------------------------
    // 弾が、マップチップに当たった、または、ウィンドウの外に出た
    if (Chara.camp->collisionCharaRect(wLeft(), wTop(), wRight(), wBottom()) ||
        Chara.wx < Chara.camp->wDispLeft() ||
        Chara.wx > Chara.camp->wDispRight()) {
        Chara.hp = 0;
    }
}