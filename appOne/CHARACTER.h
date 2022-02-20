#pragma once
#include"GAME_OBJECT.h"
#include"COLOR.h"
#include"ANIMS.h"
class CHARACTER :
	public GAME_OBJECT
{
public:
	struct DATA {
		//�����A�j��or�P�̃A�j��or�Î~����g�p����
		//�����A�j���[�V����
		class ANIMS* anims = nullptr;
		int animId = 0;
		//�P�̃A�j���[�V����
		class ANIM* anim = nullptr;
		ANIM_DATA animData;
		//�Î~��
		int img = 0;
		//�����F
		COLOR color;

		class MAP* camp = nullptr;
		char charaId = 0;
		char campId = 0;
		int groupId = 0;
		float wx = 0;
		float wy = 0;
		float initWx = 0;
		float vx = 0;
		float vy = 0;
		float speed = 0;
		float angle = 0;
		float scale = 1;

		int hp = 0;
		float offsetLeft = 0;
		float offsetTop = 0;
		float offsetRight = 0;
		float offsetBottom = 0;
	};
	enum CAMP_ID {
		BLACK_ID = 'B',
		WHITE_ID = 'W'
	};
protected:
	DATA Chara;
public:
	CHARACTER(class GAME* game);
	virtual void cmap();
	virtual void create();
	virtual void init();
	virtual void appear(float wx, float wy, float vx, float vy);
	virtual void update();
	virtual void draw();
	virtual void damage();
	virtual bool moveleft(float wx);
	virtual bool moveright(float wx);
	int  hp() { return Chara.hp; }
	int  groupId() { return Chara.groupId; }
	char charaId() { return Chara.charaId; }
	char  campId() { return Chara.campId; }
	float wx() { return Chara.wx; }
	float wy() { return Chara.wy; }
	float wLeft() { return Chara.wx + Chara.offsetLeft; }
	float wTop() { return Chara.wy + Chara.offsetTop; }
	float wRight() { return Chara.wx + Chara.offsetRight; }
	float wBottom() { return Chara.wy + Chara.offsetBottom; }
	void setImgIdx(int i) { Chara.animData.imgIdx = i; }
};

