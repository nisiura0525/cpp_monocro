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
    //�v���C���[����ʂ̒����𒴂����������X�N���[��
    Map.wx += game()->characterManager()->whitePlayer()->overCenterVx(); 
    if (Map.wx > Map.endWorldX) {
        Map.wx = Map.endWorldX;
    }
}
//�E�B���h�E����݂̂͂�������p---------------------------------------------------------
float WHITE_WORLD::wDispLeft() {
    return Map.wx - Map.chipSize;
}
float WHITE_WORLD::wDispRight() {
    return Map.wx + width;
}