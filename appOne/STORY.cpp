#include"window.h"
#include"graphic.h"
#include"input.h"
#include"CONTAINER.h"
#include"FADE.h"
#include"GAME.h"
#include "STORY.h"

void STORY::create() {
    Story = game()->container()->data().story;
}
void STORY::init() {
    game()->fade()->inTrigger();
    game()->container()->data();
}
void STORY::draw() { 
    clear();
    
    colorMode(RGB);
    rectMode(CORNER);
    fill(Story.boxColor);
    rect(Story.px, Story.py, Story.ofsetx, Story.ofsety);
    rect(width /2 ,height/2, 500 , 400);

    rectMode(CORNER);
    imageColor(Story.backColor);
    image(Story.backImage, 0, 0);
    game()->fade()->draw();
}
void STORY::update() {

}
void STORY::nextScene() {
    if (isTrigger(KEY_SPACE)) {
        game()->fade()->outTrigger();
    }
    if (game()->fade()->outEndFlag()) {
        game()->setCurScene(game()->stage());
    }
}