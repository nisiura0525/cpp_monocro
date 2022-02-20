#pragma once
#include "GAME_OBJECT.h"
class CHARACTER_MANAGER :
    public GAME_OBJECT
{
public:
    struct DATA {
        int numBlackPlayer = 0;
        int numBlackRook = 0;
        int numBlackPawn = 0;
        int numBlackBishop = 0;
        int numBlackKnight = 0;
        int numBlackQueen = 0;
        int numBlackKing = 0;

        int numWhitePawn = 0;
        int numWhitePlayer= 0;
        int numWhiteRook = 0;
        int numWhiteBishop = 0;
        int numWhiteKnight = 0;
        int numWhiteQueen = 0;
        int numWhiteKing = 0;

        int numPlayerBullets = 0;
        int numBishopBullets = 0;
        int numKnightBullets = 0;
        int numQueenBullets = 0;
        int numKingBullets = 0;
        int numExplosions = 0;
    };
    
private:
    int TotalB = 0;
    int TotalW = 0;
    int BulletTotal = 0;
    DATA CharaMng;
    class BULLET** Bullets = nullptr;
    class CHARACTER** CharactersB = nullptr;
    class CHARACTER** CharactersW = nullptr;
    class BLACK_PLAYER* BlackPlayer = nullptr;
    class WHITE_PLAYER* WhitePlayer = nullptr;
    class BLACK_KING* BlackKing = nullptr;
    class WHITE_KING* WhiteKing = nullptr;
public:
    CHARACTER_MANAGER(class GAME* game);
    ~CHARACTER_MANAGER();
    void create();
    void initb();
    void initw();
    void appear(char charaId, float wx, float wy, float vx = 0, float vy = 0);
    void bulletAppear(char charaId, float wx, float wy,  char cmapId, float vx = 0,float vy = 0,int curbullet = 0);
    void updateb();
    void drawb();
    void updatew();
    void draww();
    void bulletInit();
    void bulletLoopInit(char cmapId);
    void bulletUpdate();
    void bulletDraw();
    class BLACK_PLAYER* blackPlayer() { return BlackPlayer; }
    class WHITE_PLAYER* whitePlayer() { return WhitePlayer; }
    class BLACK_KING* blackKing() { return BlackKing; }
    class WHITE_KING* whiteKing() { return WhiteKing; }
};

