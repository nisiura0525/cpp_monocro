#include "CHARACTER_MANAGER.h"
#include"GAME.h"
#include"CONTAINER.h"
#include"CHARACTER.h"
#include"BULLET.h"
#include"BLACK_PLAYER.h"
#include"WHITE_PLAYER.h"
#include"BISHOP_BULLET.h"
#include"QUEEN_BULLET.h"
//#include"EXPLOSION.h"
CHARACTER_MANAGER::CHARACTER_MANAGER(class GAME* game) :
    GAME_OBJECT(game) {
}
CHARACTER_MANAGER::~CHARACTER_MANAGER() {
    for (int i = 0; i < TotalB; i++) {
        delete CharactersB[i];
    }
    delete[] CharactersB;
    for (int i = 0; i < TotalW; i++) {
        delete CharactersW[i];
    }
    delete[] CharactersW;
    
    for (int i = 0; i < BulletTotal; i++) {
        delete Bullets[i];
    }
    delete[] Bullets;
    
}
void CHARACTER_MANAGER::create() {
    CharaMng = game()->container()->data().charaMng;

    TotalB = 0;
    TotalB += CharaMng.numBlackPlayer;
    TotalB += CharaMng.numBlackKing;
    TotalB += CharaMng.numBlackPawn;
    TotalB += CharaMng.numBlackRook;
    TotalB += CharaMng.numBlackBishop;
    TotalB += CharaMng.numBlackKnight;
    TotalB += CharaMng.numBlackQueen;

    TotalW = 0;
    TotalW += CharaMng.numWhitePlayer;
    TotalW += CharaMng.numWhiteKing;
    TotalW += CharaMng.numWhitePawn;
    TotalW += CharaMng.numWhiteBishop;
    TotalW += CharaMng.numWhiteRook;
    TotalW += CharaMng.numWhiteKnight;
    TotalW += CharaMng.numWhiteQueen;

    BulletTotal = 0;
    BulletTotal += CharaMng.numPlayerBullets;
    BulletTotal += CharaMng.numBishopBullets;
    BulletTotal += CharaMng.numQueenBullets;

    CharactersB = new CHARACTER * [TotalB];
    CharactersW = new CHARACTER * [TotalW];
    Bullets = new BULLET * [BulletTotal];

    BlackPlayer = new BLACK_PLAYER(game());
    WhitePlayer = new WHITE_PLAYER(game());
    BlackKing = new BLACK_KING(game());
    WhiteKing = new WHITE_KING(game());
    int i, j = 0;
    for (i = 0; i < CharaMng.numBlackPlayer; i++)  CharactersB[j++] = BlackPlayer;
    for (i = 0; i < CharaMng.numBlackKing; i++)    CharactersB[j++] = BlackKing;
    for (i = 0; i < CharaMng.numBlackPawn; i++)    CharactersB[j++] = new BLACK_PAWN(game());
    for (i = 0; i < CharaMng.numBlackRook; i++)    CharactersB[j++] = new BLACK_ROOK(game());
    for (i = 0; i < CharaMng.numBlackBishop; i++)  CharactersB[j++] = new BLACK_BISHOP(game());
    for (i = 0; i < CharaMng.numBlackKnight; i++)  CharactersB[j++] = new BLACK_KNIGHT(game());
    for (i = 0; i < CharaMng.numBlackQueen; i++)  CharactersB[j++] = new BLACK_QUEEN(game());
    for (int i = 0; i < TotalB; i++) {
        CharactersB[i]->create();
    }
 
    i = 0, j = 0;
    for (i = 0; i < CharaMng.numWhitePlayer; i++)  CharactersW[j++] = WhitePlayer;
    for (i = 0; i < CharaMng.numWhiteKing; i++)    CharactersW[j++] = WhiteKing;
    for (i = 0; i < CharaMng.numWhiteBishop; i++)  CharactersW[j++] = new WHITE_BISHOP(game());
    for (i = 0; i < CharaMng.numWhitePawn; i++)    CharactersW[j++] = new WHITE_PAWN(game());
    for (i = 0; i < CharaMng.numWhiteRook; i++)    CharactersW[j++] = new WHITE_ROOK(game());
    for (i = 0; i < CharaMng.numWhiteKnight; i++)  CharactersW[j++] = new WHITE_KNIGHT(game());
    for (i = 0; i < CharaMng.numWhiteQueen; i++)   CharactersW[j++] = new WHITE_QUEEN(game());
    for (int i = 0; i < TotalW; i++) {
        CharactersW[i]->create();
    }
    i = 0, j = 0;
    for (i = 0;i < CharaMng.numPlayerBullets;i++) Bullets[j++] = new PBULLET(game());
    for (i = 0;i < CharaMng.numBishopBullets;i++) Bullets[j++] = new BISHOP_BULLET(game());
    for (i = 0;i < CharaMng.numQueenBullets;i++) Bullets[j++] = new QUEEN_BULLET(game());
    for (int i = 0; i < BulletTotal; i++) {
        Bullets[i]->create();
    }
}
void CHARACTER_MANAGER::initb() {
    for (int i = 0; i < TotalB; i++) {
        CharactersB[i]->init();
    }
}
void CHARACTER_MANAGER::initw() {
    for (int i = 0; i < TotalW; i++) {
         CharactersW[i]->init();
    }
}
void CHARACTER_MANAGER::appear(char charaId, float wx, float wy, float vx, float vy) {
    // charaIdで指定されたキャラを出現させる
    for (int i = 0; i < TotalB; i++) {
        if (CharactersB[i]->charaId() == charaId) {
            if (CharactersB[i]->hp() <= 0) {
                CharactersB[i]->appear(wx, wy, vx, vy);
                break;
            }
        }
    }
    for (int i = 0; i < TotalW; i++) {
        if (CharactersW[i]->charaId() == charaId) {
            if (CharactersW[i]->hp() <= 0) {
                CharactersW[i]->appear(wx, wy, vx, vy);
                break;
            }
        }
    }
}
void CHARACTER_MANAGER::updateb() {
    for (int i = 0; i < TotalB; i++) {
            if (CharactersB[i]->hp() > 0) {
                CharactersB[i]->update();
            }
    }
    //キャラとキャラの当たり判定---------------------------------------------------
    for (int i = 0; i < TotalB - 1; i++) {
            if (CharactersB[i]->hp() == 0) {
                continue;// ←ここでi++に戻る
            }
            for (int j = i + 1; j < TotalB; j++) {
                if (CharactersB[j]->hp() == 0) {
                    continue;// ←ここでj++に戻る
                }
                //仲間どうしは当たり判定しない
                if (CharactersB[i]->groupId() == CharactersB[j]->groupId()) {
                    continue;// ←ここでj++に戻る
                }
                //当たり判定
                if (CharactersB[i]->wLeft() < CharactersB[j]->wRight() &&
                    CharactersB[j]->wLeft() < CharactersB[i]->wRight() &&
                    CharactersB[i]->wTop() < CharactersB[j]->wBottom() &&
                    CharactersB[j]->wTop() < CharactersB[i]->wBottom()) {
                    //当たった
                    CharactersB[i]->damage();
                    CharactersB[j]->damage();
                }
            }
    }
}
void CHARACTER_MANAGER::updatew() {
    for (int i = 0; i < TotalW; i++) {
            if (CharactersW[i]->hp() > 0) {
                CharactersW[i]->update();
            }
    }
    //キャラとキャラの当たり判定---------------------------------------------------
    for (int i = 0; i < TotalW - 1; i++) {
            if (CharactersW[i]->hp() == 0) {
                continue;// ←ここでi++に戻る
            }
            for (int j = i + 1; j < TotalW; j++) {
                if (CharactersW[j]->hp() == 0) {
                    continue;// ←ここでj++に戻る
                }
                //仲間どうしは当たり判定しない
                if (CharactersW[i]->groupId() == CharactersW[j]->groupId()) {
                    continue;// ←ここでj++に戻る
                }
                //当たり判定
                if (CharactersW[i]->wLeft() < CharactersW[j]->wRight() &&
                    CharactersW[j]->wLeft() < CharactersW[i]->wRight() &&
                    CharactersW[i]->wTop() < CharactersW[j]->wBottom() &&
                    CharactersW[j]->wTop() < CharactersW[i]->wBottom()) {
                    //当たった
                    CharactersW[i]->damage();
                    CharactersW[j]->damage();
                }
            }
        
    }
}
void CHARACTER_MANAGER::drawb() {
    for (int i = 0; i < TotalB; i++) {
            if (CharactersB[i]->hp() > 0) {
                CharactersB[i]->draw();
            }
        
    }
}
void CHARACTER_MANAGER::draww() {
    for (int i = 0; i < TotalW; i++) {
            if (CharactersW[i]->hp() > 0) {
                CharactersW[i]->draw();
            }
        
    }
}
void CHARACTER_MANAGER::bulletDraw() {
    for (int i = 0; i < BulletTotal; i++) {
        if (Bullets[i]->hp() > 0) {
            Bullets[i]->draw();
        }
    }
}
void CHARACTER_MANAGER::bulletAppear(char charaId, float wx, float wy, char campId,
    float vx, float vy,int curbullet) {
    for (int i = 0; i < BulletTotal;i++) {
        if (Bullets[i]->charaId() == charaId) {
            if (Bullets[i]->hp() <= 0) {
                Bullets[i]->appear(wx, wy, vx, vy, campId,curbullet);
                break;
            }
        }
    }
}
void CHARACTER_MANAGER::bulletInit() {
    for (int i = 0; i < BulletTotal; i++) {
        Bullets[i]->init();
    }
}
void CHARACTER_MANAGER::bulletLoopInit(char campId) {
    for (int i = 0; i < BulletTotal; i++) {
        if (Bullets[i]->campId() == campId) {
            Bullets[i]->init();
        }
    }
}
void CHARACTER_MANAGER::bulletUpdate() {
    for (int i = 0; i < BulletTotal; i++) {
        if (Bullets[i]->hp() > 0) {
            Bullets[i]->update();
        }
    }
    //キャラとキャラの当たり判定---------------------------------------------------
    for (int i = 0; i < BulletTotal - 1; i++) {
        if (Bullets[i]->hp() == 0) {
            continue;// ←ここでi++に戻る
        }
        //弾同士
        for (int j = i + 1; j < BulletTotal; j++) {
            if (Bullets[j]->hp() == 0) {
                continue;// ←ここでj++に戻る
            }
            //仲間どうしは当たり判定しない
            if (Bullets[i]->groupId() == Bullets[j]->groupId()) {
                continue;// ←ここでj++に戻る
            }
            //当たり判定
            if (Bullets[i]->wLeft() < Bullets[j]->wRight() &&
                Bullets[j]->wLeft() < Bullets[i]->wRight() &&
                Bullets[i]->wTop() < Bullets[j]->wBottom() &&
                Bullets[j]->wTop() < Bullets[i]->wBottom()) {
                //当たった
                Bullets[i]->damage();
                Bullets[j]->damage();
            }
        }
        if (Bullets[i]->campId() == CHARACTER::CAMP_ID::BLACK_ID) {
            for (int k = 0; k < TotalB; k++) {
                if (CharactersB[k]->hp() == 0) {
                    continue;// ←ここでk++に戻る
                }
                //仲間どうしは当たり判定しない
                if (Bullets[i]->groupId() == CharactersB[k]->groupId()) {
                    continue;// ←ここでk++に戻る
                }
                //当たり判定
                if (Bullets[i]->wLeft() < CharactersB[k]->wRight() &&
                    CharactersB[k]->wLeft() < Bullets[i]->wRight() &&
                    Bullets[i]->wTop() < CharactersB[k]->wBottom() &&
                    CharactersB[k]->wTop() < Bullets[i]->wBottom()) {
                    //当たった
                    Bullets[i]->damage();
                    CharactersB[k]->damage();
                }
            }
        }
        else if(Bullets[i]->campId() == CHARACTER::CAMP_ID::WHITE_ID) {
             for (int l = 0; l < TotalW; l++) {
                if (CharactersW[l]->hp() == 0) {
                    continue;// ←ここでl++に戻る
                }
                //仲間どうしは当たり判定しない
                if (Bullets[i]->groupId() == CharactersW[l]->groupId()) {
                    continue;// ←ここでl++に戻る
                }
                //当たり判定
                if (Bullets[i]->wLeft() < CharactersW[l]->wRight() &&
                    CharactersW[l]->wLeft() < Bullets[i]->wRight() &&
                    Bullets[i]->wTop() < CharactersW[l]->wBottom() &&
                    CharactersW[l]->wTop() < Bullets[i]->wBottom()) {
                    //当たった
                    Bullets[i]->damage();
                    CharactersW[l]->damage();
                }
            }
        }
    }
}