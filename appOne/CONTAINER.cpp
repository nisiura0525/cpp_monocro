#include"graphic.h"
#include "CONTAINER.h"
#include"ANIMS.h"
CONTAINER::~CONTAINER() {
   //キャライメージANIMdelet
    delete Data.bplayerChara.anims;
    delete Data.wplayerChara.anims;
    delete Data.blackPawnChara.anims;
    delete Data.whitePawnChara.anims;
    delete Data.whiteBishopChara.anim;
    delete Data.blackBishopChara.anim;
    delete Data.blackKnightChara.anims;
    delete Data.whiteKnightChara.anims;
    delete Data.blackQueenChara.anims;
    delete Data.whiteQueenChara.anims;
    delete Data.blackKingChara.anim;
    delete Data.whiteKingChara.anim;
}
void CONTAINER::load() {
    CreateData();
    LoadGraphics();
}
void CONTAINER::CreateData() {
    Data.fade.color = (60, 60, 60);
    Data.fade.wcolor = (60, 60, 60);
    Data.fade.bcolor = (60, 60, 60);
    Data.fade.speed = 255 * 2;
    
    Data.stage.backToTitleTime = 2;
    Data.stage.backColor = COLOR(255, 255, 255, 255);
    Data.stage.gameOverColor = COLOR(255, 0, 0);
    Data.stage.stageClearColor = COLOR(255, 255, 0);
    Data.stage.logoPx = (width - 800) / 2;
    Data.stage.logoPy = 220;
    
    Data.blackStage.nextBToTime = 2;
    Data.blackStage.loopBToTime = 2;
    Data.blackStage.backColor = COLOR(255, 255, 255, 255);
    Data.blackStage.gameOverColor = COLOR(255, 0, 0);
    Data.blackStage.stageClearColor = COLOR(255, 255, 0);
    Data.blackStage.logoBPx = (width - 800) / 2;
    Data.blackStage.logoBPy = height / 2 + 100;

    Data.whiteStage.nextWToTime = 2;
    Data.whiteStage.loopWToTime = 2;
    Data.whiteStage.backColor = COLOR(255, 255, 255, 255);
    Data.whiteStage.gameOverColor = COLOR(255, 0, 0);
    Data.whiteStage.stageClearColor = COLOR(255, 255, 0);
    Data.whiteStage.logoWPx = (width - 800) / 2;
    Data.whiteStage.logoWPy = height / 2 - 100;
    //ブラック
    Data.blackMap.fileName1 = "assets\\mapB1.txt";
    Data.blackMap.fileName2 = "assets\\mapB2.txt";
    Data.blackMap.fileName3 = "assets\\mapB3.txt";
    Data.blackMap.chipSize = 50;
    Data.blackMap.centerX = width / 2 - Data.blackMap.chipSize / 2;
    //ホワイトマップ
    Data.whiteMap.fileName1 = "assets\\mapW1.txt";
    Data.whiteMap.fileName2 = "assets\\mapW2.txt";
    Data.whiteMap.fileName3 = "assets\\mapW3.txt";
    Data.whiteMap.chipSize = 50;
    Data.whiteMap.centerX = width / 2 - Data.whiteMap.chipSize / 2;
    //キャラクター

    //ブラック軍
    //プレイヤー１
    Data.bplayerChara.charaId = MAP::PLAYER_ID;
    Data.bplayerChara.hp = 10;
    Data.bplayerChara.campId = CHARACTER::BLACK_ID;
    Data.bplayerChara.groupId = 0;//味方グループは0
    Data.bplayerChara.speed = 3.4f * 60;
    Data.bplayerChara.offsetLeft = 10.0f;
    Data.bplayerChara.offsetTop = 1.0f;
    Data.bplayerChara.offsetRight = 40.0f;
    Data.bplayerChara.offsetBottom = 49.0f;
    Data.bplayer.rightAnimId = 0;
    Data.bplayer.leftAnimId = 1;
    Data.bplayer.ReLife = 3;
    Data.bplayer.jumpFlag = 0;
    Data.bplayer.initVecUp = -16.0f;
    Data.bplayer.initVecDown = 3.0f;
    Data.bplayer.gravity = 48;
    Data.bplayer.bulletsM = 15;
    Data.bplayer.ReloadInterval = 15.0f*0.16f;
    Data.bplayer.bulletOffsetX = 20.0f;
    Data.bplayer.bulletCharaId = MAP::PLAYER_BULLET_ID;
    // 黒ポーン
    Data.blackPawnChara.charaId = MAP::BLACK_PAWN_ID;
    Data.blackPawnChara.groupId = 1;//敵グループは1
    Data.blackPawnChara.campId = CHARACTER::BLACK_ID;
    Data.blackPawnChara.hp = 4;
    Data.blackPawnChara.speed = 1.4f * 60;
    Data.blackPawnChara.offsetLeft = 10.0f;
    Data.blackPawnChara.offsetTop = 12.0f;
    Data.blackPawnChara.offsetRight = 40.0f;
    Data.blackPawnChara.offsetBottom = 40.0f;
    Data.blackPawn.rightAnimId = 0;
    Data.blackPawn.leftAnimId = 1;
    Data.blackPawn.damageInterval = 5 * 0.016f;
    Data.blackPawn.initVecX = -1;
    Data.blackPawn.initVecY = 0;
    Data.blackPawn.gravity = 0.8f * 60;
    Data.blackPawn.alphaLowVal = 25;
    Data.blackPawn.damageColor = COLOR(255, 0, 0);
    Data.blackPawn.explosionCharaId = MAP::EXPLOSION_ID;
    //黒ルーク
    Data.blackRookChara.charaId = MAP::BLACK_ROOK_ID;
    Data.blackRookChara.groupId = 1;//敵グループは1
    Data.blackRookChara.campId = CHARACTER::BLACK_ID;
    Data.blackRookChara.hp = 4;
    Data.blackRookChara.speed = 1.0f * 60;
    Data.blackRookChara.offsetLeft = 10.0f;
    Data.blackRookChara.offsetTop = 12.0f;
    Data.blackRookChara.offsetRight = 40.0f;
    Data.blackRookChara.offsetBottom = 40.0f;
    Data.blackRook.rightAnimId = 0;
    Data.blackRook.leftAnimId = 1;
    Data.blackRook.acInterval = 10.0f*0.16f;
    Data.blackRook.damageInterval = 5 * 0.016f;
    Data.blackRook.initVecX = -1;
    Data.blackRook.initVecY = 0;
    Data.blackRook.gravity = 0.8f * 60;
    Data.blackRook.alphaLowVal = 25;
    Data.blackRook.damageColor = COLOR(255, 0, 0);
    Data.blackRook.explosionCharaId = MAP::EXPLOSION_ID;
    //黒ビショップ
    Data.blackBishopChara.charaId = MAP::BLACK_BISHOP_ID;
    Data.blackBishopChara.hp = 7;
    Data.blackBishopChara.campId = CHARACTER::BLACK_ID;
    Data.blackBishopChara.groupId = 1;//敵グループは1
    Data.blackBishopChara.offsetLeft = 10.0f;
    Data.blackBishopChara.offsetTop = 10.0f;
    Data.blackBishopChara.offsetRight = 30.0f;
    Data.blackBishopChara.offsetBottom = 35.0f;
    Data.blackBishop.elapsedTime = 0;
    Data.blackBishop.interval = 0.016f;
    Data.blackBishop.triggerCnt = 60;
    Data.blackBishop.triggerInterval = 240;
    Data.blackBishop.trigger1st = 220;
    Data.blackBishop.trigger2nd = 225;
    Data.blackBishop.trigger3rd = 230;
    Data.blackBishop.trigger4th = 235;
    Data.blackBishop.bulletCharaId = MAP::BISHOP_BULLET_ID;
    Data.blackBishop.damageTime = 0;
    Data.blackBishop.damageInterval = 5 * 0.016f;
    Data.blackBishop.bulletOffsetX = 20.0f;
    Data.blackBishop.explosionCharaId = MAP::EXPLOSION_ID;
    Data.blackBishop.damageColor = COLOR(255, 0, 0, 25);
    Data.blackBishop.normalColor = COLOR(255, 255, 255);
    //黒ナイト
    Data.blackKnightChara.charaId = MAP::BLACK_KNIGHT_ID;
    Data.blackKnightChara.hp = 4;
    Data.blackKnightChara.campId = CHARACTER::BLACK_ID;
    Data.blackKnightChara.speed = 2.50f * 60;
    Data.blackKnightChara.groupId = 1;//敵グループは1
    Data.blackKnightChara.offsetLeft = 10.0f;
    Data.blackKnightChara.offsetTop = 10.0f;
    Data.blackKnightChara.offsetRight = 30.0f;
    Data.blackKnightChara.offsetBottom = 35.0f;
    Data.blackKnight.jumpTrigger = 10 * 0.16f;
    //move
    Data.blackKnight.rightAnimId = 0;
    Data.blackKnight.leftAnimId = 1;
    Data.blackKnight.jumpFlag = 0;
    Data.blackKnight.initVecUp = -16.0f;
    Data.blackKnight.initVecDown = 3.0f;
    Data.blackKnight.gravity = 48;
    //tama
    Data.blackKnight.bulletCharaId = MAP::KNIGHT_BULLET_ID;
    Data.blackKnight.bulletOffsetX = 20.0f;
    /*
    Data.blackKnight.elapsedTime = 0;
    Data.blackKnight.interval = 0.016f;
    Data.blackKnight.triggerCnt = 60;
    Data.blackKnight.triggerInterval = 240;
    Data.blackKnight.trigger1st = 220;
    Data.blackKnight.trigger2nd = 225;
    Data.blackKnight.trigger3rd = 230;
    Data.blackKnight.trigger4th = 235;
    */
    //ダメージ
    Data.blackKnight.damageTime = 0;
    Data.blackKnight.damageInterval = 5 * 0.016f;
    Data.blackKnight.explosionCharaId = MAP::EXPLOSION_ID;
    Data.blackKnight.damageColor = COLOR(255, 0, 0, 25);
    Data.blackKnight.normalColor = COLOR(255, 255, 255);
    //黒クイーン
    Data.blackQueenChara.charaId = MAP::BLACK_QUEEN_ID;
    Data.blackQueenChara.groupId = 1;//敵グループは1
    Data.blackQueenChara.campId = CHARACTER::BLACK_ID;
    Data.blackQueenChara.hp = 10;
    Data.blackQueenChara.speed = 1.0f * 60;
    Data.blackQueenChara.offsetLeft = 10.0f;
    Data.blackQueenChara.offsetTop = 12.0f;
    Data.blackQueenChara.offsetRight = 40.0f;
    Data.blackQueenChara.offsetBottom = 40.0f;
    Data.blackQueen.rightAnimId = 0;
    Data.blackQueen.leftAnimId = 1;

    Data.blackQueen.acInterval = 2.0f * 0.16f;
    Data.blackQueen.damageInterval = 5 * 0.016f;
    Data.blackQueen.initVecX = -1;
    Data.blackQueen.initVecY = 0;
    Data.blackQueen.initVecUp = -16.0f;
    Data.blackQueen.initVecDown = 3.0f;
    Data.blackQueen.gravity = 0.8f * 60;
    Data.blackQueen.jumpTrigger = 10 * 0.16f;
    Data.blackQueen.alphaLowVal = 25;
    Data.blackQueen.damageColor = COLOR(255, 0, 0);
    Data.blackQueen.explosionCharaId = MAP::EXPLOSION_ID;

    Data.blackQueen.changeTrigger = 265;
    Data.blackQueen.triggerCnt = 0;
    Data.blackQueen.triggerInterval = 270;
    Data.blackQueen.trigger1st = 65;
    Data.blackQueen.trigger2nd = 130;
    Data.blackQueen.trigger3rd = 195;
    Data.blackQueen.trigger4th = 260;
    Data.blackQueen.trigger1 = 190;
    Data.blackQueen.trigger2 = 200;
    Data.blackQueen.trigger3 = 210;
    Data.blackQueen.trigger4 = 220;
    Data.blackQueen.trigger5 = 230;
    Data.blackQueen.trigger6 = 240;
    Data.blackQueen.trigger7 = 250;
    Data.blackQueen.trigger8 = 260;
    Data.blackQueen.bulletCharaId = MAP::QUEEN_BULLET_ID;
    Data.blackQueen.bulletOffsetX = 20.0f;
    //黒キング
    Data.blackKingChara.charaId = MAP::BLACK_KING_ID;
    Data.blackKingChara.groupId = 1;//敵グループは1
    Data.blackKingChara.campId = CHARACTER::BLACK_ID;
    Data.blackKingChara.hp = 15;
    Data.blackKingChara.speed = 1.0f * 60;
    Data.blackKingChara.offsetLeft = 10.0f*2;
    Data.blackKingChara.offsetTop = 12.0f*2;
    Data.blackKingChara.offsetRight = 40.0f*2;
    Data.blackKingChara.offsetBottom = 40.0f*2;
    Data.blackKing.rightAnimId = 0;
    Data.blackKing.leftAnimId = 1;
    Data.blackKing.acInterval = 22.5f * 0.16f;
    Data.blackKing.damageInterval = 5 * 0.016f;
    Data.blackKing.jumpFlag = 0;
    Data.blackKing.initVecUp = -16.0f;
    Data.blackKing.initVecX = -1;
    Data.blackKing.initVecY = 0;
    Data.blackKing.gravity = 0.8f * 60;
    Data.blackKing.alphaLowVal = 25;
    Data.blackKing.damageColor = COLOR(255, 0, 0);
    Data.blackKing.explosionCharaId = MAP::EXPLOSION_ID;
    //ホワイト
    //2p
    Data.wplayerChara.charaId = MAP::WHITE_PLAYER_ID;
    Data.wplayerChara.hp = 10;
    Data.wplayerChara.campId = CHARACTER::WHITE_ID;
    Data.wplayerChara.groupId = 0;//味方グループは0
    Data.wplayerChara.speed = 3.4f * 60;
    Data.wplayerChara.offsetLeft = 10.0f;
    Data.wplayerChara.offsetTop = 1.0f;
    Data.wplayerChara.offsetRight = 40.0f;
    Data.wplayerChara.offsetBottom = 49.0f;
    Data.wplayer.rightAnimId = 0;
    Data.wplayer.leftAnimId = 1;
    Data.wplayer.ReLife = 3;
    Data.wplayer.jumpFlag = 0;
    Data.wplayer.initVecUp = -16.0f;
    Data.wplayer.initVecDown = 3.0f;
    Data.wplayer.gravity = 48;
    Data.wplayer.bulletsM = 15;
    Data.wplayer.ReloadInterval = 15.0f * 0.16f;
    Data.wplayer.bulletOffsetX = 20.0f;
    Data.wplayer.bulletCharaId = MAP::PLAYER_BULLET_ID;
    //白ポーン
    Data.whitePawnChara.charaId = MAP::WHITE_PAWN_ID;
    Data.whitePawnChara.groupId = 1;//敵グループは1
    Data.whitePawnChara.campId = CHARACTER::WHITE_ID;
    Data.whitePawnChara.hp = 4;
    Data.whitePawnChara.speed = 1.4f * 60;
    Data.whitePawnChara.offsetLeft = 10.0f;
    Data.whitePawnChara.offsetTop = 12.0f;
    Data.whitePawnChara.offsetRight = 40.0f;
    Data.whitePawnChara.offsetBottom = 40.0f;
    Data.whitePawn.rightAnimId = 0;
    Data.whitePawn.leftAnimId = 1;
    Data.whitePawn.damageInterval = 5 * 0.016f;
    Data.whitePawn.initVecX = -1;
    Data.whitePawn.initVecY = 0;
    Data.whitePawn.gravity = 0.8f * 60;
    Data.whitePawn.alphaLowVal = 25;
    Data.whitePawn.damageColor = COLOR(255, 0, 0);
    Data.whitePawn.explosionCharaId = MAP::EXPLOSION_ID;
    //白ルーク
    Data.whiteRookChara.charaId = MAP::WHITE_ROOK_ID;
    Data.whiteRookChara.groupId = 1;//敵グループは1
    Data.whiteRookChara.campId = CHARACTER::WHITE_ID;
    Data.whiteRookChara.hp = 4;
    Data.whiteRookChara.speed = 1.0f * 60;
    Data.whiteRookChara.offsetLeft = 10.0f;
    Data.whiteRookChara.offsetTop = 12.0f;
    Data.whiteRookChara.offsetRight = 40.0f;
    Data.whiteRookChara.offsetBottom = 40.0f;
    Data.whiteRook.rightAnimId = 0;
    Data.whiteRook.leftAnimId = 1;
    Data.whiteRook.acInterval = 10.0f * 0.16f;
    Data.whiteRook.damageInterval = 5 * 0.016f;
    Data.whiteRook.initVecX = -1;
    Data.whiteRook.initVecY = 0;
    Data.whiteRook.gravity = 0.8f * 60;
    Data.whiteRook.alphaLowVal = 25;
    Data.whiteRook.damageColor = COLOR(255, 0, 0);
    Data.whiteRook.explosionCharaId = MAP::EXPLOSION_ID;
    //ホワイトビショップ
    Data.whiteBishopChara.charaId = MAP::WHITE_BISHOP_ID;
    Data.whiteBishopChara.hp = 7;
    Data.whiteBishopChara.campId = CHARACTER::WHITE_ID;
    Data.whiteBishopChara.groupId = 1;//敵グループは1
    Data.whiteBishopChara.offsetLeft = 10.0f;
    Data.whiteBishopChara.offsetTop = 10.0f;
    Data.whiteBishopChara.offsetRight = 30.0f;
    Data.whiteBishopChara.offsetBottom = 35.0f;
    Data.whiteBishop.elapsedTime = 0;
    Data.whiteBishop.interval = 0.016f;
    Data.whiteBishop.triggerCnt = 60;
    Data.whiteBishop.triggerInterval = 240;
    Data.whiteBishop.trigger1st = 220;
    Data.whiteBishop.trigger2nd = 225;
    Data.whiteBishop.trigger3rd = 230;
    Data.whiteBishop.trigger4th = 235;
    Data.whiteBishop.bulletCharaId = MAP::BISHOP_BULLET_ID;
    Data.whiteBishop.damageTime = 0;
    Data.whiteBishop.damageInterval = 5 * 0.016f;
    Data.whiteBishop.bulletOffsetX = 20.0f;
    Data.whiteBishop.explosionCharaId = MAP::EXPLOSION_ID;
    Data.whiteBishop.damageColor = COLOR(255, 0, 0, 25);
    Data.whiteBishop.normalColor = COLOR(255, 255, 255);
    //白ナイト
    Data.whiteKnightChara.charaId = MAP::WHITE_KNIGHT_ID;
    Data.whiteKnightChara.hp = 4;
    Data.whiteKnightChara.campId = CHARACTER::WHITE_ID;
    Data.whiteKnightChara.speed = 2.50f * 60;
    Data.whiteKnightChara.groupId = 1;//敵グループは1
    Data.whiteKnightChara.offsetLeft = 10.0f;
    Data.whiteKnightChara.offsetTop = 10.0f;
    Data.whiteKnightChara.offsetRight = 30.0f;
    Data.whiteKnightChara.offsetBottom = 35.0f;
    Data.whiteKnight.jumpTrigger = 10 * 0.16f;
    //move
    Data.whiteKnight.rightAnimId = 0;
    Data.whiteKnight.leftAnimId = 1;
    Data.whiteKnight.jumpFlag = 0;
    Data.whiteKnight.initVecUp = -16.0f;
    Data.whiteKnight.initVecDown = 3.0f;
    Data.whiteKnight.gravity = 48;
    //tama
    Data.whiteKnight.elapsedTime = 0;
    Data.whiteKnight.interval = 0.016f;
    Data.whiteKnight.triggerCnt = 60;
    Data.whiteKnight.triggerInterval = 240;
    Data.whiteKnight.trigger1st = 220;
    Data.whiteKnight.trigger2nd = 225;
    Data.whiteKnight.trigger3rd = 230;
    Data.whiteKnight.trigger4th = 235;
    Data.whiteKnight.bulletCharaId = MAP::KNIGHT_BULLET_ID;
    Data.whiteKnight.damageTime = 0;
    Data.whiteKnight.damageInterval = 5 * 0.016f;
    Data.whiteKnight.bulletOffsetX = 20.0f;
    Data.whiteKnight.explosionCharaId = MAP::EXPLOSION_ID;
    Data.whiteKnight.damageColor = COLOR(255, 0, 0, 25);
    Data.whiteKnight.normalColor = COLOR(255, 255, 255);
    //白クイーン
    Data.whiteQueenChara.charaId = MAP::WHITE_QUEEN_ID;
    Data.whiteQueenChara.groupId = 1;//敵グループは1
    Data.whiteQueenChara.campId = CHARACTER::WHITE_ID;
    Data.whiteQueenChara.hp = 10;
    Data.whiteQueenChara.speed = 1.0f * 60;
    Data.whiteQueenChara.offsetLeft = 10.0f;
    Data.whiteQueenChara.offsetTop = 12.0f;
    Data.whiteQueenChara.offsetRight = 40.0f;
    Data.whiteQueenChara.offsetBottom = 40.0f;
    Data.whiteQueen.rightAnimId = 0;
    Data.whiteQueen.leftAnimId = 1;

    Data.whiteQueen.acInterval = 2.0f * 0.16f;
    Data.whiteQueen.damageInterval = 5 * 0.016f;
    Data.whiteQueen.initVecX = -1;
    Data.whiteQueen.initVecY = 0;
    Data.whiteQueen.initVecUp = -16.0f;
    Data.whiteQueen.initVecDown = 3.0f;
    Data.whiteQueen.gravity = 0.8f * 60;
    Data.whiteQueen.jumpTrigger = 10 * 0.16f;
    Data.whiteQueen.alphaLowVal = 25;
    Data.whiteQueen.damageColor = COLOR(255, 0, 0);
    Data.whiteQueen.explosionCharaId = MAP::EXPLOSION_ID;

    Data.whiteQueen.changeTrigger = 265;
    Data.whiteQueen.triggerCnt = 0;
    Data.whiteQueen.triggerInterval = 270;
    Data.whiteQueen.trigger1st = 65;
    Data.whiteQueen.trigger2nd = 130;
    Data.whiteQueen.trigger3rd = 195;
    Data.whiteQueen.trigger4th = 260;
    Data.whiteQueen.trigger1 = 190;
    Data.whiteQueen.trigger2 = 200;
    Data.whiteQueen.trigger3 = 210;
    Data.whiteQueen.trigger4 = 220;
    Data.whiteQueen.trigger5 = 230;
    Data.whiteQueen.trigger6 = 240;
    Data.whiteQueen.trigger7 = 250;
    Data.whiteQueen.trigger8 = 260;
    Data.whiteQueen.bulletCharaId = MAP::QUEEN_BULLET_ID;
    Data.whiteQueen.bulletOffsetX = 20.0f;
    //白キング
    Data.whiteKingChara.charaId = MAP::WHITE_KING_ID;
    Data.whiteKingChara.groupId = 1;//敵グループは1
    Data.whiteKingChara.campId = CHARACTER::WHITE_ID;
    Data.whiteKingChara.hp = 20;
    Data.whiteKingChara.speed = 1.0f * 60;
    Data.whiteKingChara.offsetLeft = 10.0f;
    Data.whiteKingChara.offsetTop = 12.0f;
    Data.whiteKingChara.offsetRight = 40.0f;
    Data.whiteKingChara.offsetBottom = 40.0f;
    Data.whiteKing.rightAnimId = 0;
    Data.whiteKing.leftAnimId = 1;
    Data.whiteKing.acInterval = 22.5f * 0.16f;
    Data.whiteKing.damageInterval = 5 * 0.016f;
    Data.whiteKing.jumpFlag = 0;
    Data.whiteKing.initVecUp = -16.0f;
    Data.whiteKing.initVecX = -1;
    Data.whiteKing.initVecY = 0;
    Data.whiteKing.gravity = 0.8f * 60;
    Data.whiteKing.alphaLowVal = 25;
    Data.whiteKing.damageColor = COLOR(255, 0, 0);
    Data.whiteKing.explosionCharaId = MAP::EXPLOSION_ID;
    //弾
    Data.playerBulletChara.charaId = MAP::PLAYER_BULLET_ID;
    Data.playerBulletChara.groupId = 0;//敵グループは1
    Data.playerBulletChara.hp = 1;
    Data.playerBulletChara.speed = 4.7f * 60;
    Data.playerBulletChara.offsetLeft = 20.0f;
    Data.playerBulletChara.offsetTop = 20.0f;
    Data.playerBulletChara.offsetRight = 30.0f;
    Data.playerBulletChara.offsetBottom = 30.0f;

    Data.bishopBulletChara.charaId = MAP::BISHOP_BULLET_ID;
    Data.bishopBulletChara.groupId = 1;//敵グループは1
    Data.bishopBulletChara.hp = 1;
    Data.bishopBulletChara.speed = 4.7f*60;
    Data.bishopBulletChara.offsetLeft = 20.0f;
    Data.bishopBulletChara.offsetTop = 20.0f;
    Data.bishopBulletChara.offsetRight = 30.0f;
    Data.bishopBulletChara.offsetBottom = 30.0f;

    Data.queenBulletChara.charaId = MAP::QUEEN_BULLET_ID;
    Data.queenBulletChara.groupId = 1;//敵グループは1
    Data.queenBulletChara.hp = 1;
    Data.queenBulletChara.speed = 4.7f * 60;
    Data.queenBulletChara.offsetLeft = 20.0f;
    Data.queenBulletChara.offsetTop = 20.0f;
    Data.queenBulletChara.offsetRight = 30.0f;
    Data.queenBulletChara.offsetBottom = 30.0f;
    //マネージャー
    Data.charaMng.numBlackPlayer = 1;
    Data.charaMng.numBlackPawn = 10;
    Data.charaMng.numBlackRook = 10;
    Data.charaMng.numBlackBishop = 10;
    Data.charaMng.numBlackKnight = 10;
    Data.charaMng.numBlackQueen = 2;
    Data.charaMng.numBlackKing = 1;
    
    Data.charaMng.numWhitePlayer = 1;
    Data.charaMng.numWhitePawn = 10;
    Data.charaMng.numWhiteRook = 10;
    Data.charaMng.numWhiteBishop = 10;
    Data.charaMng.numWhiteKnight = 10;
    Data.charaMng.numWhiteQueen = 2;
    Data.charaMng.numWhiteKing = 1;

    Data.charaMng.numPlayerBullets = 25;
    Data.charaMng.numBishopBullets = 40;
    Data.charaMng.numQueenBullets = 60;
    //Data.charaMng.numKnightBullets = 40;
    /*
    Data.charaMng.numQueenBullets = 40;
    Data.charaMng.numKingBullets = 40;
    */

    Data.title.backColor = COLOR(255, 255, 255, 255);

    Data.story.px = 0;
    Data.story.px = height / 3 * 2 ;
    Data.story.ofsetx = width;
    Data.story.ofsety = height / 3;
    Data.story.backColor = COLOR(255, 255, 255, 255);
    Data.story.boxColor = COLOR(255,255,255,255);

}
void CONTAINER::LoadGraphics() {
    Data.title.backImg = loadImage("assets\\TITLE.png");
    Data.stage.backImg1 = loadImage("assets\\haikei.png");
    Data.stage.backImg2 = loadImage("assets\\stage2.png");
    Data.stage.backImg3 = loadImage("assets\\stage3.png");

    Data.whiteStage.backImg1 = loadImage("assets\\haikei.png");
    Data.whiteStage.backImg2 = loadImage("assets\\stage2.png");
    Data.whiteStage.backImg3 = loadImage("assets\\stage3.png");

    Data.blackStage.backImg1 = loadImage("assets\\haikei.png");
    Data.blackStage.backImg2 = loadImage("assets\\stage2.png");
    Data.blackStage.backImg3 = loadImage("assets\\stage3.png");

    Data.stage.stageClearImg = loadImage("assets\\StageClear.png");
    Data.stage.pinchImg = loadImage("assets\\GameOver.png");
    Data.stage.gameClearImg = loadImage("assets\\CLEAR.png");
    Data.blackStage.stageClearImg = loadImage("assets\\StageClear.png");
    Data.blackStage.pinchImg = loadImage("assets\\GameOver.png");
    Data.whiteStage.stageClearImg = loadImage("assets\\StageClear.png");
    Data.whiteStage.pinchImg = loadImage("assets\\GameOver.png");
    Data.story.backImage = loadImage("assets\\setumei.jpg");
   
    Data.blackMap.blockImg = loadImage("assets\\block.png");
    Data.blackMap.goalImg = loadImage("assets\\goal.png");

    Data.whiteMap.blockImg = loadImage("assets\\block.png");
    Data.whiteMap.goalImg = loadImage("assets\\goal.png");

    Data.bplayerChara.anims = new ANIMS("assets\\player2");
    Data.bplayerChara.animData.interval = 0.1f;
    Data.blackPawnChara.img = loadImage("assets\\pawn.png");
    Data.blackRookChara.img = loadImage("assets\\blackRook.png");
    Data.blackBishopChara.img = loadImage("assets\\bishop.png");
    Data.blackKnightChara.anims = new ANIMS("assets\\player2");
    Data.blackKnightChara.animData.interval = 0.1f;

    Data.blackQueenChara.img = loadImage("assets\\queen.png");

    Data.blackKingChara.img = loadImage("assets\\black_king.png");

    Data.wplayerChara.anims = new ANIMS("assets\\player2");
    Data.wplayerChara.animData.interval = 0.1f;
    Data.whitePawnChara.img = loadImage("assets\\pawn.png");
    Data.whiteRookChara.img = loadImage("assets\\blackRook.png");
    Data.whiteBishopChara.img = loadImage("assets\\bishop.png");
    Data.whiteKnightChara.anims = new ANIMS("assets\\player2");
    Data.whiteKnightChara.animData.interval = 0.1f;

    Data.whiteQueenChara.img = loadImage("assets\\queen.png");

    Data.whiteKingChara.img = loadImage("assets\\black_king.png");


    Data.bishopBulletChara.img = loadImage("assets\\batBullet.png");
    Data.queenBulletChara.img = loadImage("assets\\batBullet.png");
    Data.playerBulletChara.img = loadImage("assets\\playerBullet.png");
}
