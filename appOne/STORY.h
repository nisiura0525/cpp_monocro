#pragma once
#include "SCENE.h"
#include"COLOR.h"
#define tCols 10
#define tRows 25
class STORY :
    public SCENE
{
public:
    struct TBOX {
        float x, y;
    };
    struct DATA {
        float px = 0;
        float py = 0;
        float ofsetx = 0;
        float ofsety = 0;
        int backImage = 0;
        COLOR backColor;
        COLOR boxColor;
        char text[tCols][tRows] = {0};
    };
private:
    DATA Story;
public:
    STORY(class GAME* game) : SCENE(game) {}
    virtual void create();
    virtual void init();
    virtual void update();
    virtual void draw();
    virtual void nextScene();
};

