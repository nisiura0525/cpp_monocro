#include"graphic.h"
#include"input.h"
#include"GAME.h"
#include"CONTAINER.h"
#include"STAGE.h"
#include"FADE.h"
#include "TITLE.h"
void TITLE::create() {
    Title = game()->container()->data().title;
}
void TITLE::init() {
    game()->fade()->inTrigger();
    game()->container()->data();
}
void TITLE::draw() {
    clear();
    rectMode(CORNER);
    imageColor(255);
    image(Title.backImg, 0, 0);

    float size;
    size = 100;
    textSize(size);
    fill(0);
    int c[11];
    for (int i = 0;i < 11;i++) {
        c[i] = 10-i;
    }
    int sizeX = 25;
    game()->fade()->draw();
}
void TITLE::nextScene(){
    if (isTrigger(KEY_SPACE)) {
        game()->fade()->outTrigger();
    }
    if(game()->fade()->outEndFlag()){
        game()->setCurScene(game()->stage());
    }
}
