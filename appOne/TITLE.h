#pragma once
#include"SCENE.h"
#include"COLOR.h"
class TITLE :
    public SCENE
{
public:
    struct DATA {
        int backImg = 0;
        COLOR backColor;
    };
private:
    DATA Title;
public:
    TITLE(class GAME* game) : SCENE(game) {}
    void create();
    void init();
    void draw();
    void nextScene();
};
