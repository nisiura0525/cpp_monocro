#include"graphic.h"
#include"window.h"
#include"GAME.h"
#include"CONTAINER.h"
#include"BLACK_PLAYER.h"
#include "FADE.h"
void FADE::create() {
    Fade = game()->container()->data().fade;
}
void FADE::inTrigger(){
    if( State == STATE::OUT_END ){
        State = STATE::IN_TRIGGER;
    }
}
void FADE::outTrigger(){
    if( State == STATE::IN_END ){
        State = STATE::OUT_TRIGGER;
    }
}
void FADE::whiteInTrigger() {
    if (HalfWState == HALFWSTATE::WHF_OUT_END) {
        HalfWState = HALFWSTATE::WHF_IN_TRIGGER;
    }
}
void FADE::whiteOutTrigger() {
    if (HalfWState == HALFWSTATE::WHF_IN_END) {
        HalfWState = HALFWSTATE::WHF_OUT_TRIGGER;
    }

}
void FADE::blackInTrigger() {
    if (HalfBState == HALFBSTATE::BLF_OUT_END) {
        HalfBState = HALFBSTATE::BLF_IN_TRIGGER;
    }
}
void FADE::blackOutTrigger() {
    if (HalfBState == HALFBSTATE::BLF_IN_END) {
        HalfBState = HALFBSTATE::BLF_OUT_TRIGGER;
    }

}
void FADE::draw(){
    if (State == STATE::IN_END ||
        State == STATE::OUT_END) {
        return;
    }
    rectMode(CORNER);
    colorMode(RGB,255);
    switch( State ){
    case STATE::IN_TRIGGER:
        Fade.color.a = 255;
        fill(Fade.color);
        rect(0, 0, width, height);
        State = STATE::IN_NOW;
        break;
    case STATE::IN_NOW:
        fill(Fade.color);
        rect(0, 0, width, height);
        Fade.color.a += -Fade.speed * delta;
        if( Fade.color.a < 0.0 ){
            Fade.color.a = 0.0f;
            State = STATE::IN_END;
        }
        break;
    case STATE::OUT_TRIGGER:
        Fade.color.a = 0.0f;
        State = STATE::OUT_NOW;
        break;
    case STATE::OUT_NOW:
        fill(Fade.color);
        rect(0, 0, width, height);
        Fade.color.a += Fade.speed * delta;
        if( Fade.color.a >= 255.0f ){
            Fade.color.a = 255.0f;
            State = STATE::OUT_END;
        }
        break;
    }
}
void FADE::halfBdraw() {
    if (HalfBState == HALFBSTATE::BLF_IN_END ||
        HalfBState == HALFBSTATE::BLF_OUT_END) {
        return;
    }
    switch (HalfBState) {
    case HALFBSTATE::BLF_IN_TRIGGER:
        Fade.bcolor.a = 255;
        fill(Fade.bcolor);
        rect(0, height / 2, width, height);
        HalfBState = HALFBSTATE::BLF_IN_NOW;
        break;
    case HALFBSTATE::BLF_IN_NOW:
        fill(Fade.bcolor);
        rect(0, height / 2, width, height);
        Fade.bcolor.a += -Fade.speed * delta;
        if (Fade.bcolor.a < 0.0) {
            Fade.bcolor.a = 0.0f;
            HalfBState = HALFBSTATE::BLF_IN_END;
        }
        break;
    case HALFBSTATE::BLF_OUT_TRIGGER:
        Fade.bcolor.a = 0.0f;
        HalfBState = HALFBSTATE::BLF_OUT_NOW;
        break;
    case HALFBSTATE::BLF_OUT_NOW:
        fill(Fade.bcolor);
        rect(0, height / 2, width, height);
        Fade.bcolor.a += Fade.speed * delta;
        if (Fade.bcolor.a >= 255.0f) {
            Fade.bcolor.a = 255.0f;
            HalfBState = HALFBSTATE::BLF_OUT_END;
        }
        break;
    }    
}
void FADE::halfWdraw() {
    if (HalfWState == HALFWSTATE::WHF_IN_END ||
        HalfWState == HALFWSTATE::WHF_OUT_END) {
        return;
    }
    switch (HalfWState) {
    case HALFWSTATE::WHF_IN_TRIGGER:
        Fade.wcolor.a = 255;
        fill(Fade.wcolor);
        rect(0, 0, width, height/2);
        HalfWState = HALFWSTATE::WHF_IN_NOW;
        break;
    case HALFWSTATE::WHF_IN_NOW:
        fill(Fade.wcolor);
        rect(0, 0, width, height/2);
        Fade.wcolor.a += -Fade.speed * delta;
        if (Fade.wcolor.a < 0.0) {
            Fade.wcolor.a = 0.0f;
            HalfWState = HALFWSTATE::WHF_IN_END;
        }
        break;
    case HALFWSTATE::WHF_OUT_TRIGGER:
        Fade.wcolor.a = 0.0f;
        HalfWState = HALFWSTATE::WHF_OUT_NOW;
        break;
    case HALFWSTATE::WHF_OUT_NOW:
        fill(Fade.wcolor);
        rect(0, 0, width, height/2);
        Fade.wcolor.a += Fade.speed * delta;
        if (Fade.wcolor.a >= 255.0f) {
            Fade.wcolor.a = 255.0f;
            HalfWState = HALFWSTATE::WHF_OUT_END;
        }
        break;
    }
}
int FADE::inEndFlag(){
    return ( State == STATE::IN_END );
}
int FADE::outEndFlag() {
    return (State == STATE::OUT_END);
}
int FADE::blackInEndFlag() {
    return (HalfBState == HALFBSTATE::BLF_IN_END);
}
int FADE::blackOutEndFlag() {
    return (HalfBState == HALFBSTATE::BLF_OUT_END);
}
int FADE::whiteInEndFlag(){
    return ( HalfWState == HALFWSTATE::WHF_IN_END );
}
int FADE::whiteOutEndFlag() {
    return (HalfWState == HALFWSTATE::WHF_OUT_END);
}
void FADE::setColor(const COLOR& color){
    Fade.color = color;
}
void FADE::setSpeed( float speed ){
    Fade.speed = speed;
}
