#include"graphic.h"
#include"ANIMS.h"
#include"CONTAINER.h"
#include"GAME.h"
#include"MAP.h"
#include"CHARACTER.h"
CHARACTER::CHARACTER(GAME* game):
     GAME_OBJECT(game){
}
void CHARACTER::create() {//
	cmap();
}
void CHARACTER::cmap() {
	if (Chara.campId == BLACK_ID) {
		Chara.camp = game()->blackWorld();
	}
	else if (Chara.campId == WHITE_ID) {
		Chara.camp = game()->whiteWorld();
	}
}
void CHARACTER::init(){//
	Chara.hp = 0;
}
void CHARACTER::appear(float wx, float wy, float vx, float vy) {//
	Chara.wx = wx;
	Chara.wy = wy;
	Chara.hp = 1;
}
void CHARACTER::update() {//<-
	float px = Chara.wx - Chara.camp->wx();
	if (px < -Chara.camp->chipSize()) {
		Chara.hp = 0;
	}
}
void CHARACTER::draw() {//<-
	imageColor(Chara.color);
	float px = Chara.wx - Chara.camp->wx();
	float py = Chara.wy - Chara.camp->wy();
	if (Chara.anims) {
		Chara.anims->anim(Chara.animId)->draw(&Chara.animData,
			px, py, Chara.angle, Chara.scale);
	}
	else if (Chara.anim) {
		Chara.anim->draw(&Chara.animData,
			px, py, Chara.angle, Chara.scale);
	}
	else {
		image(Chara.img, px, py, Chara.angle, Chara.scale);
	}
}
bool CHARACTER::moveleft(float wx) {
	if (wx - Chara.wx < 0) return true;
	else return false;
}
bool CHARACTER::moveright(float wx) {
	if (wx - Chara.wx > 0) return true;
	else return false;
}
void CHARACTER::damage() {
	if (Chara.hp > 0) {
		Chara.hp--;
	}
}
