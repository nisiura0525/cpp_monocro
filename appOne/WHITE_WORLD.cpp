#include "WHITE_WORLD.h"
#include"window.h"
#include"graphic.h"
#include"GAME.h"
#include"CONTAINER.h"
#include "MAP.h"
WHITE_WORLD::~WHITE_WORLD() {
    if (Map.data) { delete[] Map.data; Map.data = 0; }
}
void WHITE_WORLD::create() {
    Map = game()->container()->data().whiteMap;
    Map.fileName = Map.fileName2;
}
void WHITE_WORLD::update() {
    //プレイヤーが画面の中央を超えた分だけスクロール
    Map.wx += game()->characterManager()->whitePlayer()->overCenterVx(); 
    if (Map.wx > Map.endWorldX) {
        Map.wx = Map.endWorldX;
    }
}
//ウィンドウからのはみだし判定用---------------------------------------------------------
float WHITE_WORLD::wDispLeft() {
    return Map.wx - Map.chipSize;
}
float WHITE_WORLD::wDispRight() {
    return Map.wx + width;
}