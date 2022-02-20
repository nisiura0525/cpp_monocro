#include "WHITE_PLAYER.h"
#include"input.h"
#include"window.h"
#include"graphic.h"
#include"CONTAINER.h"
#include"GAME.h"
#include"WHITE_WORLD.h"
#include "PLAYER.h"
void WHITE_PLAYER::create() {
	Chara = game()->container()->data().wplayerChara;
	WhitePlayer = game()->container()->data().wplayer;
	cmap();
}
void WHITE_PLAYER::resetState() {
	WhitePlayer.ReLife = game()->container()->data().wplayer.ReLife;
	State = STATE::STRUGGLING;
}
void WHITE_PLAYER::appear(float wx, float wy, float vx, float vy) {
	Chara.hp = game()->container()->data().wplayerChara.hp;
	Chara.wx = wx;
	Chara.wy = wy;
	Chara.animId = WhitePlayer.rightAnimId;
	WhitePlayer.bulletsR = WhitePlayer.bulletsM;
	WhitePlayer.jumpFlag = 0;
	State = STATE::STRUGGLING;
}
void WHITE_PLAYER::update() {
	Launch();
	Move();
	CollisionWithMap();
	CheckState();
}
void WHITE_PLAYER::Launch() {
	if (isTrigger(MOUSE_LBUTTON)) {
		if (WhitePlayer.bulletsR > 0) {
			float vx = 1.0f;
			if (Chara.animId == WhitePlayer.leftAnimId) {
				vx = -1.0f;
			}
			float wx = Chara.wx + WhitePlayer.bulletOffsetX * vx;
			float wy = Chara.wy;
			game()->characterManager()->bulletAppear(WhitePlayer.bulletCharaId, wx, wy, Chara.campId, vx);
			WhitePlayer.bulletsR--;
		}
	}
	if (isTrigger(MOUSE_RBUTTON)) WhitePlayer.bulletsR = 0;
	if (WhitePlayer.bulletsR <= 0) {
		if (WhitePlayer.CurTime <= 0) {
			WhitePlayer.bulletsR = WhitePlayer.bulletsM;
			WhitePlayer.CurTime = WhitePlayer.ReloadInterval;
		}
		else
			WhitePlayer.CurTime -= delta;
	}
}
void WHITE_PLAYER::Move() {
	//ジャンプ
	if (WhitePlayer.jumpFlag == 0 && isTrigger(KEY_UP)) {
		Chara.vy = WhitePlayer.initVecUp;
		WhitePlayer.jumpFlag = 1;
	}
	if (WhitePlayer.jumpFlag == 1) {
		Chara.vy += WhitePlayer.gravity * delta;
		Chara.wy += Chara.vy * 60 * delta;
	}
	//左右移動
	//  移動ベクトルを決定
	Chara.vx = 0.0f;
	if (isPress(KEY_LEFT)) {
		Chara.vx = -Chara.speed * delta;
		Chara.animId = WhitePlayer.leftAnimId;
	}
	if (isPress(KEY_RIGHT)) {
		Chara.vx = Chara.speed * delta;
		Chara.animId = WhitePlayer.rightAnimId;
	}
	//  移動前に現在のChara.wxをPlayer.curWxにとっておく
	WhitePlayer.curWx = Chara.wx;
	//  移動
	if (Chara.vx != 0.0f) {//左右キー入力あり
		//とりあえず「次に移動する予定」の位置としてChara.wxを更新しておき
		//あとで、マップに食い込んでいたら、元のPlayer.curWxに戻す
		Chara.wx += Chara.vx;
	}
	else {//左右キー入力がないとき
		Chara.animData.imgIdx = 0;
		Chara.animData.elapsedTime = -delta;
	}
}
void WHITE_PLAYER::CollisionWithMap() {
	//マップチップとキャラの→
	if (Chara.animId == WhitePlayer.rightAnimId) {
		if (Chara.camp->collisionCharaRight(Chara.wx, Chara.wy)) {
			Chara.wx = WhitePlayer.curWx;
		}
	}
	//マップチップとキャラの←
	else {
		if (Chara.animId == WhitePlayer.leftAnimId) {
			if (Chara.camp->collisionCharaLeft(Chara.wx, Chara.wy) ||
				Chara.wx < Chara.camp->wx()) {
				Chara.wx = WhitePlayer.curWx;
			}
		}
	}
	if (Chara.camp->collisionCharaTop(Chara.wx, Chara.wy)) {
		Chara.vy = WhitePlayer.initVecDown;
	}
	if (Chara.camp->collisionCharaBottom(WhitePlayer.curWx, Chara.wy)) {
		//--「マップチップに食い込んでいる」
		// または「上に立っているとき」もここを通る--
		//ジャンプ（落下）処理の停止
		WhitePlayer.jumpFlag = 0;
		Chara.vy = 0.0f;
		//強制定期に上に立っている位置にする
		Chara.wy = (int)Chara.wy / Chara.camp->chipSize() * (float)Chara.camp->chipSize();
	}
	else {
		WhitePlayer.jumpFlag = 1;
	}
}
void WHITE_PLAYER::CheckState() {
	if (Chara.wy > height + game()->whiteWorld()->chipSize()) {
		State = STATE::DIED;
		Chara.hp = 0;
		WhitePlayer.ReLife--;
		return;
	}
	//ステージをクリアした
	if (Chara.wx > game()->whiteWorld()->wDispRight()) {
		State = STATE::SURVIVED;
		Chara.hp = 0;
	}
}
void WHITE_PLAYER::damage() {
	if (Chara.hp > 0) {
		Chara.hp--;
		if (Chara.hp == 0) {
			WhitePlayer.ReLife--;
				State = STATE::DIED;
				Chara.vy = WhitePlayer.initVecUp;
		}
	}
}
bool WHITE_PLAYER::died() {
	if (State == STATE::DIED) {
		Chara.vy += WhitePlayer.gravity * delta;
		Chara.wy += Chara.vy * 60 * delta;
		draw();
		return true;
	}
	else if (State == STATE::FALL) {
		return true;
	}
	return false;
}
bool WHITE_PLAYER::survived() {
	return State == STATE::SURVIVED;
}
float WHITE_PLAYER::overCenterVx() {
	//マップをスクロールさせるためのベクトルを求めるMap.wxは現在の画面の一番左
	float centerWx = (game()->whiteWorld()->wx() + width / 2 - game()->whiteWorld()->chipSize());
	float overCenterVx = Chara.wx - centerWx;
	if (overCenterVx < 0 || Chara.hp == 0)overCenterVx = 0;
	return overCenterVx;
}