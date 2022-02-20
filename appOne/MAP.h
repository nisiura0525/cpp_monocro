#pragma once
#include"GAME_OBJECT.h"
class MAP :
    public GAME_OBJECT
{
public:
    struct DATA {
        const char* fileName = 0;
        const char* fileName1 = 0;
        const char* fileName2 = 0;
        const char* fileName3 = 0;
        int blockImg = 0;
        int goalImg = 0;
        int chipSize = 0; //正方形マップチップ画像の一辺のドット数
        char* data = 0; //データ配列のポインタ
        int cols = 0; //データの列数
        int rows = 0; //データの行数
        int dispCols = 0;
        int dispRows = 0;
        float wx = 0;//world position x
        float wy = 0;//world position y
        float worldWidth = 0;
        float worldHeight = 0;
        float endWorldX = 0;
        float endWorldY = 0;
        float centerX = 0;
    };
    enum CHARA_ID {
        PLAYER_ID = 'a',
        BLACK_PAWN_ID = 'p',
        BLACK_ROOK_ID = 'r',
        BLACK_BISHOP_ID = 'b',
        BLACK_KNIGHT_ID = 'n',
        BLACK_QUEEN_ID = 'q',
        BLACK_KING_ID = 'k',

        WHITE_PAWN_ID = 'P',
        WHITE_PLAYER_ID = 'A',
        WHITE_ROOK_ID = 'R',
        WHITE_BISHOP_ID = 'B',
        WHITE_KNIGHT_ID = 'N',
        WHITE_QUEEN_ID = 'Q',
        WHITE_KING_ID = 'K',

        PLAYER_BULLET_ID = 'z',
        BISHOP_BULLET_ID = 'y',
        KNIGHT_BULLET_ID = 'x',
        QUEEN_BULLET_ID = 'w',
        KING_BULLET_ID = 'j',

        EXPLOSION_ID = 'f',
    };
protected:
    DATA Map;
    char c = EXPLOSION_ID;
public:
    MAP(class GAME* game);
    ~MAP();
    virtual void create();
    virtual void init();
    virtual void change12();
    virtual void change23();
    virtual void changeReset();
    virtual void update();
    virtual void draw();
    virtual float wx() { return Map.wx; }
    virtual float wy() { return Map.wy; }
    virtual int chipSize() { return Map.chipSize; }
    //マップチップとキャラの当たり判定に使用する関数群---------------------------------------
    virtual bool collisionCheck(float wx, float wy);//下の当たり判定関数群から呼び出して使う関数
    virtual bool collisionCharaLeft(float wx, float wy);
    virtual bool collisionCharaRight(float wx, float wy);
    virtual bool collisionCharaTop(float wx, float wy);
    virtual bool collisionCharaBottom(float wx, float wy);
    virtual bool collisionCharaRect(float wLeft, float wTop, float wRight, float wBottom);//弾用
    //ウィンドウ枠からのはみだし判定用---------------------------------------------------
    virtual float wDispLeft();
    virtual float wDispRight();
};

