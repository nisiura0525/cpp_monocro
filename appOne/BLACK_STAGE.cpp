#include "BLACK_STAGE.h"
#include"window.h"
#include"graphic.h"
#include"input.h"
#include"GAME.h"
#include"CONTAINER.h"
#include"MAP.h"
#include"BLACK_WORLD.h"
#include"CHARACTER_MANAGER.h"
#include"FADE.h"
#include "STAGE.h"
void BLACK_STAGE::create() {
    BlackStage = game()->container()->data().blackStage;
}
void BLACK_STAGE::init() {
    BlackStage.nextBToTime = game()->container()->data().blackStage.nextBToTime;
    BlackStage.loopBToTime = game()->container()->data().blackStage.loopBToTime;
    game()->blackWorld()->init();
    game()->characterManager()->initb();
    game()->blackWorld()->changeReset();
    game()->fade()->blackInTrigger();
    game()->characterManager()->blackPlayer()->resetState();
    BBf = BBF_ID::STAGE_B1;
}
void BLACK_STAGE::loopinit() {
    game()->characterManager()->bulletLoopInit(CHARACTER::CAMP_ID::BLACK_ID);
    game()->characterManager()->initb();
    game()->blackWorld()->init();
    game()->fade()->blackInTrigger();
    BlackStage.nextBToTime = game()->container()->data().blackStage.nextBToTime;
    BlackStage.loopBToTime = game()->container()->data().blackStage.loopBToTime;
}
void BLACK_STAGE::update() {
    game()->characterManager()->updateb();
    game()->blackWorld()->update();
}
void BLACK_STAGE::draw() {
    if (BBf == BBF_ID::STAGE_B1 || BBf == BBF_ID::STAGE_B2 || BBf == BBF_ID::STAGE_B3) {
        stage();
    }
    else if (BBf == BBF_ID::GAMEOVER_SCENE) {
        gameoverLogo(BlackStage.pinchImg, BlackStage.gameOverColor);
    }
    game()->fade()->halfBdraw();
}
void BLACK_STAGE::BackGround() {
    if (BBf == BBF_ID::STAGE_B1)
        image(BlackStage.backImg1, 0, 450);
    else if (BBf == BBF_ID::STAGE_B2)
        image(BlackStage.backImg2, 0, 450);
    else
        image(BlackStage.backImg3, 0, 450);
}
void BLACK_STAGE::stage() {
    game()->fade()->blackInTrigger();
    game()->characterManager()->drawb();
    game()->blackWorld()->draw();
    game()->fade()->halfBdraw();
    if (game()->characterManager()->blackPlayer()->died()) {
        loopBLogo(BlackStage.pinchImg, BlackStage.gameOverColor);
    }
    if (game()->characterManager()->blackPlayer()->survived()) {
        nextBLogo(BlackStage.stageClearImg, BlackStage.stageClearColor);
    }
}
void BLACK_STAGE::gameoverLogo(int img, const COLOR& color) {
    imageColor(color);
    image(img, BlackStage.logoBPx, BlackStage.logoBPy);
}
void BLACK_STAGE::nextBLogo(int img, const COLOR& color) {
    imageColor(color);
    image(img, BlackStage.logoBPx, BlackStage.logoBPy);
    BlackStage.nextBToTime -= delta;
}
void BLACK_STAGE::loopBLogo(int img, const COLOR& color) {
    imageColor(color);
    image(img, BlackStage.logoBPx, BlackStage.logoBPy);
    BlackStage.loopBToTime -= delta;
}
void BLACK_STAGE::nextScene() {
    if (BlackStage.nextBToTime <= 0) {
        game()->fade()->blackOutTrigger();
    }
    if (BlackStage.loopBToTime <= 0) {
        game()->fade()->blackOutTrigger();
    }
    if (game()->fade()->blackOutEndFlag()) {
        if (game()->characterManager()->blackPlayer()->state() == BLACK_PLAYER::STATE::SURVIVED) {
            if (BBf == BBF_ID::STAGE_B1) {
                BBf = BBF_ID::STAGE_B2;
                //game()->characterManager()->blackPlayer()->Reward();
                game()->blackWorld()->change12();
                loopinit();
            }
            else if (BBf == BBF_ID::STAGE_B2) {
                BBf = BBF_ID::STAGE_B3;
               // game()->characterManager()->blackPlayer()->Reward();
                game()->blackWorld()->change23();
                loopinit();
            }
        }
        else if (game()->characterManager()->blackPlayer()->state() == BLACK_PLAYER::STATE::DIED
                && game()->characterManager()->blackPlayer()->life() > 0) 
        {
            if (BBf == BBF_ID::STAGE_B1) {
                BBf = BBF_ID::STAGE_B1;
                loopinit();
            }
            if (BBf == BBF_ID::STAGE_B2) {
                BBf = BBF_ID::STAGE_B2;
                loopinit();
            }
            if (BBf == BBF_ID::STAGE_B3) {
                BBf = BBF_ID::STAGE_B3;
                loopinit();
            }
        }
        else{
            BlackStage.nextBToTime = game()->container()->data().blackStage.nextBToTime;
            BlackStage.loopBToTime = game()->container()->data().blackStage.loopBToTime;
            loopinit();
            game()->fade()->blackInTrigger();
            BBf = BBF_ID::GAMEOVER_SCENE;
        }
    }
}