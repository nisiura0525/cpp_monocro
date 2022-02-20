#pragma once
#include "SCENE.h"
#include"graphic.h"
class BLACK_STAGE :
    public SCENE
{
public:
    struct DATA {
        int backImg1 = 0;
        int backImg2 = 0;
        int backImg3 = 0;
        int stageClearImg = 0;
        int pinchImg = 0;
        float nextBToTime = 0;
        float loopBToTime = 0;
        COLOR backColor;
        COLOR gameOverColor;
        COLOR stageClearColor;
        float logoBPx = 0;
        float logoBPy = 0;
    };
    enum class BBF_ID {
        STAGE_B1, STAGE_B2, STAGE_B3,
        GAMEOVER_SCENE
    };
private:
    DATA BlackStage;
    BBF_ID BBf = BBF_ID::STAGE_B1;
public:
    BLACK_STAGE(class GAME* game) : SCENE(game) {}
    void BackGround();
    void create();
    void init();
    void loopinit();
   // void proc();
    void update();
    void draw();
    void stage();
    void nextScene();
    void gameoverLogo(int img, const COLOR& color);
    void nextBLogo(int img, const COLOR& color);
    void loopBLogo(int img, const COLOR& color);
};

