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
    //�E�B���h�E�g����݂̂͂�������p---------------------------------------------------
    float wDispLeft();
    float wDispRight();
};

