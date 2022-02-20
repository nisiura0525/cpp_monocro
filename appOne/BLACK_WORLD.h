#pragma once
#include "MAP.h"
class BLACK_WORLD :
	public MAP
{
public:
	BLACK_WORLD(class GAME* game) : MAP(game) {};
	~BLACK_WORLD();
	void create();//
	//void init();
	void update();
	//MAPから継承
	//ウィンドウ枠からのはみだし判定用---------------------------------------------------
	float wDispLeft();
	float wDispRight();
};

