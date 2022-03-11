#include"window.h"
#include"graphic.h"
#include"input.h"
#include"sound.h"
#include"GAME.h"
#include"CONTAINER.h"
#include"MAP.h"
#include"BLACK_WORLD.h"
#include"WHITE_WORLD.h"
#include"CHARACTER_MANAGER.h"
#include"FADE.h"
#include "STAGE.h"
#include"BLACK_STAGE.h"
#include"WHITE_STAGE.h"

void STAGE::create(){
    Stage = game()->container()->data().stage;
}
void STAGE::init() {
    Stage.backToTitleTime = game()->container()->data().stage.backToTitleTime;
    game()->blackStage()->init();
    game()->whiteStage()->init();
    game()->characterManager()->bulletInit();
    game()->fade()->inTrigger();
    sound();
}
void STAGE::sound() {
    setVolume(Stage.stageSnd,-1250);
    playLoopSound(Stage.stageSnd);
}
void STAGE::proc() {
    update();
    draw();
    nextScene();
}
void STAGE::update() {
    game()->blackStage()->update();
    game()->whiteStage()->update();
    game()->characterManager()->bulletUpdate();
}
void STAGE::draw(){
    BackGround();
    game()->characterManager()->bulletDraw();
    game()->fade()->draw();
    game()->whiteStage()->draw();
    game()->blackStage()->draw();
    if (game()->characterManager()->whitePlayer()->life() <= 0 &&
        game()->characterManager()->blackPlayer()->life() <= 0)
        gameoverLogo(Stage.pinchImg,Stage.gameOverColor);
#ifdef _DEBUG
    game()->characterManager()->blackKing()->deth();
    fill(50);
    float size = 50;
    textSize(size);
    switch (game()->characterManager()->whitePlayer()->life())
    {
    case 3:text("残機3", 900, 50); break;
    case 2:text("残機2", 900,50); break;
    case 1:text("残機1", 900, 50); break;
    default:text("負け犬", 900, 50); break;
    }
    switch (game()->characterManager()->blackPlayer()->life())
    {
    case 3:text("残機3", 900, 500); break;
    case 2:text("残機2", 900, 500); break;
    case 1:text("残機1", 900, 500); break;
    default:text("負け犬", 900, 500); break;
    }
    fill(128);
    float w = 40.0f;
    float h = 45.0f;
    rect(0, 0, game()->container()->data().wplayerChara.hp * w, h);
    rect(0, 450, game()->container()->data().bplayerChara.hp*w,h);
    fill(3, 252, 40);
    rect(0, 0, game()->characterManager()->whitePlayer()->hp() *w, h);
    rect(0, 450, game()->characterManager()->blackPlayer()->hp()*w , h);
    fill(58, 110,194);
    for (int i = 0;i < game()->characterManager()->blackPlayer()->bullets();i++) {
        rect(500.0f+10.0f*i, 450, 5.0f, h);
    }
    for (int i = 0;i < game()->characterManager()->whitePlayer()->bullets();i++) {
        rect(500.0f + 10.0f * i, 0, 5.0f, h);
    }
#endif
}
void STAGE::BackGround(){
    clear();
    rectMode(CORNER);
    imageColor(Stage.backColor);
    game()->whiteStage()->BackGround();
    game()->blackStage()->BackGround();
}
void STAGE::gameoverLogo(int img, const COLOR& color) {
    imageColor(color);
    image(img, Stage.logoPx, Stage.logoPy);
    Stage.backToTitleTime -= delta;
}
void STAGE::gameclearLogo(int img, const COLOR& color,float px,float py) {
    imageColor(color);
    image(img, Stage.logoPx, Stage.logoPy);
    Stage.backToTitleTime -= delta;
}
void STAGE::nextScene() {
    game()->blackStage()->nextScene();
    game()->whiteStage()->nextScene();
    gameover();
    gameclear();
} 
void STAGE::gameover() {
    if (Stage.backToTitleTime <= 0) {
        game()->fade()->outTrigger();
    }
    if (game()->fade()->outEndFlag()) {
        game()->setCurScene(game()->title());   
    }
}
void STAGE::gameclear() {
    if (Stage.backToTitleTime <= 0) {
        game()->fade()->outTrigger();
    }
    if (game()->fade()->outEndFlag()) {
        game()->setCurScene(game()->title());
    }
}
void STAGE::killSound() {
    setVolume(Stage.killSnd, -1250);
    playSound(Stage.killSnd);
}
