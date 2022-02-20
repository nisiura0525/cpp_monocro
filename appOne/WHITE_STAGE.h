#pragma once
#include"SCENE.h"
#include"graphic.h"
class WHITE_STAGE :
    public SCENE
{
public:
    struct DATA {
        int backImg1 = 0;
        int backImg2 = 0;
        int backImg3 = 0;
        int stageClearImg = 0;
        int pinchImg = 0;
        float nextWToTime = 0;
        float loopWToTime = 0;
        COLOR backColor;
        COLOR gameOverColor;
        COLOR stageClearColor;
        float logoWPx = 0;
        float logoWPy = 0;
    };
    enum class WBF_ID {
        STAGE_W1, STAGE_W2, STAGE_W3,
        GAMEOVER_SCENE
    };
private:
    DATA WhiteStage;
    WBF_ID WBf = WBF_ID::STAGE_W1;
public:
    WHITE_STAGE(class GAME* game) : SCENE(game) {}
    void BackGround();
    void create();
    void init();
    void loopinit();
    //void proc();
    void update();
    void draw();
    void stage();
    void nextScene();
    void gameoverLogo(int img, const COLOR& color);
    void nextWLogo(int img, const COLOR& color);
    void loopWLogo(int img, const COLOR& color);
};

