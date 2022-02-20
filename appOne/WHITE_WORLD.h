#pragma once
#include "MAP.h"
class WHITE_WORLD :
    public MAP
{
public:
    WHITE_WORLD(class GAME* game) : MAP(game) {};
    ~WHITE_WORLD();
    void create();//
    //void init();
    void update();
    //ウィンドウ枠からのはみだし判定用---------------------------------------------------
    float wDispLeft();
    float wDispRight();
};

