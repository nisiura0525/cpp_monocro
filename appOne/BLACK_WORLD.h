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
	//MAP����p��
	//�E�B���h�E�g����݂̂͂�������p---------------------------------------------------
	float wDispLeft();
	float wDispRight();
};

