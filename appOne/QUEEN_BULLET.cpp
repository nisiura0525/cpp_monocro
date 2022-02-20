#include "QUEEN_BULLET.h"
#include"window.h"
#include"CONTAINER.h"
#include"GAME.h"
#include"MAP.h"
void QUEEN_BULLET::create() {
    Chara = game()->container()->data().queenBulletChara;
}
void QUEEN_BULLET::appear(float wx, float wy, float vx, float vy, char campId, int curbullet) {
    curBullet = curbullet;
    Chara.hp = 1;
    Chara.wx = wx;
    Chara.wy = wy;
    Chara.vx = vx;
    Chara.vy = vy;
    Chara.campId = campId;
    this->cmap();
    Chara.initWx = wx;
    if (Chara.campId == CHARACTER::CAMP_ID::BLACK_ID) {
        player.x = game()->characterManager()->blackPlayer()->wx();
        player.y = game()->characterManager()->blackPlayer()->wy();
    }
    else {
        player.x = game()->characterManager()->whitePlayer()->wx();
        player.y = game()->characterManager()->whitePlayer()->wy();
    }
    queen.x = Chara.wx;
    queen.y = Chara.wy;
    vec = player - queen;
    vec.normalize();
}
void QUEEN_BULLET::update() {
    if (curBullet == 0) {
        if (Chara.campId == CHARACTER::CAMP_ID::BLACK_ID) {
            player.x = game()->characterManager()->blackPlayer()->wx();
            player.y = game()->characterManager()->blackPlayer()->wy();
        }
        else {
            player.x = game()->characterManager()->whitePlayer()->wx();
            player.y = game()->characterManager()->whitePlayer()->wy();
        }
        queen.x = Chara.wx;
        queen.y = Chara.wy;
        vec = player - queen;
        vec.normalize();
    }
    //移動--------------------------------------------------------------------------
    Chara.wx += (Chara.vx * vec.x) *(Chara.speed * delta);
    Chara.wy += (Chara.vy * vec.y) *(Chara.speed * delta);
    //マップ------------------------------------------------------------------------
    // 弾が、マップチップに当たった、または、ウィンドウの外に出た
    if (Chara.camp->collisionCharaRect(wLeft(), wTop(), wRight(), wBottom()) ||
        Chara.wx < Chara.camp->wDispLeft() ||
        Chara.wx > Chara.camp->wDispRight()) {
        Chara.hp = 0;
    }
}