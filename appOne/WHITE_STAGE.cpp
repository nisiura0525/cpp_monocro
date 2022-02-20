#include "WHITE_STAGE.h"
#include"window.h"
#include"graphic.h"
#include"input.h"
#include"GAME.h"
#include"CONTAINER.h"
#include"MAP.h"
#include"WHITE_WORLD.h"
#include"WHITE_PLAYER.h"
#include"CHARACTER_MANAGER.h"
#include"FADE.h"
#include "STAGE.h"
void WHITE_STAGE::create() {
    WhiteStage = game()->container()->data().whiteStage;
}
void WHITE_STAGE::init() {
    WhiteStage.nextWToTime = game()->container()->data().whiteStage.nextWToTime;
    WhiteStage.loopWToTime = game()->container()->data().whiteStage.loopWToTime;
    game()->whiteWorld()->changeReset();
    game()->whiteWorld()->init();
    game()->characterManager()->initw();
    game()->fade()->whiteInTrigger();
    game()->characterManager()->whitePlayer()->resetState();
    WBf = WBF_ID::STAGE_W1;
}
void WHITE_STAGE::loopinit() {
    game()->characterManager()->bulletLoopInit(CHARACTER::CAMP_ID::WHITE_ID);
    game()->whiteWorld()->init();
    game()->characterManager()->initw();
    game()->fade()->whiteInTrigger();
    WhiteStage.nextWToTime = game()->container()->data().whiteStage.nextWToTime;
    WhiteStage.loopWToTime = game()->container()->data().whiteStage.loopWToTime;
}
void WHITE_STAGE::update() {
    game()->characterManager()->updatew();
    game()->whiteWorld()->update();
}
void WHITE_STAGE::draw() {
    if (WBf == WBF_ID::STAGE_W1 || WBf == WBF_ID::STAGE_W2 || WBf == WBF_ID::STAGE_W3) {
        stage();
    }
    else if (WBf == WBF_ID::GAMEOVER_SCENE) {
        gameoverLogo(WhiteStage.pinchImg, WhiteStage.gameOverColor);
    }
    game()->fade()->halfWdraw();
}
void WHITE_STAGE::BackGround() {
     if(WBf==WBF_ID::STAGE_W1)
     image(WhiteStage.backImg1, 0, 0);
     else if(WBf==WBF_ID::STAGE_W2)
     image(WhiteStage.backImg2, 0, 0);
     else 
     image(WhiteStage.backImg3, 0, 0);
}
void WHITE_STAGE::stage() {
    game()->fade()->whiteInTrigger();
    game()->whiteWorld()->draw();
    game()->characterManager()->draww();
    game()->fade()->halfWdraw();
    if (game()->characterManager()->whitePlayer()->survived()) {
        nextWLogo(WhiteStage.stageClearImg, WhiteStage.stageClearColor);
    }
    if (game()->characterManager()->whitePlayer()->died()) {
        loopWLogo(WhiteStage.pinchImg, WhiteStage.gameOverColor);
    }
}
void WHITE_STAGE::gameoverLogo(int img, const COLOR& color) {
    imageColor(color);
    image(img, WhiteStage.logoWPx, WhiteStage.logoWPy);
}
void WHITE_STAGE::nextWLogo(int img, const COLOR& color) {
    imageColor(color);
    image(img, WhiteStage.logoWPx, WhiteStage.logoWPy);
    WhiteStage.nextWToTime -= delta;
}
void WHITE_STAGE::loopWLogo(int img, const COLOR& color) {
    imageColor(color);
    image(img, WhiteStage.logoWPx, WhiteStage.logoWPy);
    WhiteStage.loopWToTime -= delta;
}
void WHITE_STAGE::nextScene() {
    if (WhiteStage.nextWToTime <= 0) {
        game()->fade()->whiteOutTrigger();
    }
    if (WhiteStage.loopWToTime <= 0) {
        game()->fade()->whiteOutTrigger();
    }
    if (game()->fade()->whiteOutEndFlag()) {
        if (game()->characterManager()->whitePlayer()->state() == WHITE_PLAYER::STATE::SURVIVED) {
            if (WBf == WBF_ID::STAGE_W1) {
                WBf = WBF_ID::STAGE_W2;
                //game()->characterManager()->whitePlayer()->Reward();
                game()->whiteWorld()->change12();
                loopinit();
            }
            else if (WBf == WBF_ID::STAGE_W2) {
                WBf = WBF_ID::STAGE_W3;
                //game()->characterManager()->whitePlayer()->Reward();
                game()->whiteWorld()->change23();
                loopinit();
            }
        }
        else if (game()->characterManager()->whitePlayer()->state()== 
            WHITE_PLAYER::STATE::DIED&&
            game()->characterManager()->whitePlayer()->life() > 0) {
            if (WBf == WBF_ID::STAGE_W1) {
                WBf = WBF_ID::STAGE_W1;
                loopinit();
            }
            if (WBf == WBF_ID::STAGE_W2) {
                WBf = WBF_ID::STAGE_W2;
                loopinit();
            }
            if (WBf == WBF_ID::STAGE_W3) {
                WBf = WBF_ID::STAGE_W3;
                loopinit();
            }
        }
        else{
            WhiteStage.nextWToTime = game()->container()->data().whiteStage.nextWToTime;
            WhiteStage.loopWToTime = game()->container()->data().whiteStage.loopWToTime;
            game()->fade()->whiteInTrigger();
            WBf = WBF_ID::GAMEOVER_SCENE;
        }
    }
}