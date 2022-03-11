#pragma once
#include "SCENE.h"
class STAGE :
    public SCENE
{
public:
    struct DATA {
        int backImg1 = 0;
        int backImg2 = 0;
        int backImg3 = 0;
        int stageClearImg = 0;
        int gameClearImg = 0;
        int pinchImg = 0;
        float backToTitleTime = 0;
        COLOR backColor;
        COLOR gameOverColor;
        COLOR stageClearColor;
        float logoPx = 0;
        float logoPy = 0;
        float tSize = 0;
        int stageSnd = 0;
        int killSnd = 0;
    };
private:
    DATA Stage;
    void BackGround();
    void gameoverLogo(int img, const COLOR& color);
public:
    STAGE(class GAME* game) : SCENE(game) {}
    void gameclearLogo(int img, const COLOR& color,float px,float py);
    void create();
    void init();
    void proc();
    void update();
    void draw();
    void nextScene();
    void gameover();
    void gameclear();
    void sound();
    void killSound();
};
