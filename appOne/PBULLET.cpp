#include "PBULLET.h"
#include"window.h"
#include"CONTAINER.h"
#include"GAME.h"
#include"MAP.h"
void PBULLET::create() {
	Chara = game()->container()->data().playerBulletChara;
}
void PBULLET::appear(float wx, float wy, float vx, float vy, char campId) {
    Chara.hp = 1;
    Chara.wx = wx;
    Chara.wy = wy;
    Chara.vx = vx;
    Chara.vy = vy;
    Chara.campId = campId;
    this->cmap();
    Chara.initWx = wx;
}