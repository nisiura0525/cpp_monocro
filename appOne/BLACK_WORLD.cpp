#include "BLACK_WORLD.h"
#include"window.h"
#include"graphic.h"
#include"GAME.h"
#include"CONTAINER.h"
#include "MAP.h"
BLACK_WORLD::~BLACK_WORLD() {
    if (Map.data) { delete[] Map.data; Map.data = 0; }
}
void BLACK_WORLD::create() {
    Map = game()->container()->data().blackMap;
    Map.fileName = Map.fileName1;
}
void BLACK_WORLD::update() {
    //プレイヤーが画面の中央を超えた分だけスクロール
    Map.wx += game()->characterManager()->blackPlayer()->overCenterVx();
    if (Map.wx > Map.endWorldX) {
        Map.wx = Map.endWorldX;
    }
}
//ウィンドウからのはみだし判定用---------------------------------------------------------
float BLACK_WORLD::wDispLeft() {
    return Map.wx - Map.chipSize;
}
float BLACK_WORLD::wDispRight() {
    return Map.wx + width;
}
