#pragma once
#include"STORY.h"
#include"TITLE.h"
#include"STAGE.h"
#include"BLACK_STAGE.h"
#include"WHITE_STAGE.h"
#include"FADE.h"
#include"MAP.h"
#include"CHARACTER.h"
#include"CHARACTER_MANAGER.h"
#include"BLACK_PLAYER.h"
#include"WHITE_PLAYER.h"
#include"BLACK_PAWN.h"
#include"WHITE_PAWN.h"
#include"BLACK_ROOK.h"
#include"WHITE_ROOK.h"
#include"BLACK_BISHOP.h"
#include"WHITE_BISHOP.h"
#include"BLACK_KNIGHT.h"
#include"WHITE_KNIGHT.h"
#include"BLACK_QUEEN.h"
#include"WHITE_QUEEN.h"
#include"BLACK_KING.h"
#include"WHITE_KING.h"
#include"PBULLET.h"
#include"QUEEN_BULLET.h"
class CONTAINER
{
private:
    struct DATA {
        STAGE::DATA stage;
        BLACK_STAGE::DATA blackStage;
        WHITE_STAGE::DATA whiteStage;
        TITLE::DATA title;
        FADE::DATA fade;
        STORY::DATA story;
        MAP::DATA blackMap;
        MAP::DATA whiteMap;
        CHARACTER::DATA bplayerChara;
        BLACK_PLAYER::DATA bplayer;
        CHARACTER::DATA wplayerChara;
        WHITE_PLAYER::DATA wplayer;
        CHARACTER::DATA blackPawnChara;
        BLACK_PAWN::DATA blackPawn;
        CHARACTER::DATA blackRookChara;
        BLACK_ROOK::DATA blackRook;
        CHARACTER::DATA whiteRookChara;
        WHITE_ROOK::DATA whiteRook;
        CHARACTER::DATA whitePawnChara;
        WHITE_PAWN::DATA whitePawn;
        CHARACTER::DATA blackBishopChara;
        BLACK_BISHOP::DATA blackBishop;
        CHARACTER_MANAGER::DATA charaMng;
        CHARACTER::DATA whiteBishopChara;
        WHITE_BISHOP::DATA whiteBishop;

        BLACK_KNIGHT::DATA blackKnight;
        WHITE_KNIGHT::DATA whiteKnight;
        BLACK_QUEEN::DATA blackQueen;
        WHITE_QUEEN::DATA whiteQueen;
        BLACK_KING::DATA blackKing;
        WHITE_KING::DATA whiteKing;
        
        //’Ç‰Á—\’è
        CHARACTER::DATA blackKnightChara;
        CHARACTER::DATA blackKingChara;
        CHARACTER::DATA blackQueenChara;

        CHARACTER::DATA whiteKnightChara;
        CHARACTER::DATA whiteQueenChara;
        CHARACTER::DATA whiteKingChara;
        //’e
        CHARACTER::DATA playerBulletChara;
        CHARACTER::DATA bishopBulletChara;
        CHARACTER::DATA knightBulletChara;
        CHARACTER::DATA queenBulletChara;
        CHARACTER::DATA kingBulletChara;
    };
    DATA Data;
    void CreateData();
    void LoadGraphics();
public:
    ~CONTAINER();
    void load();
    const DATA& data() { return Data; }
};

