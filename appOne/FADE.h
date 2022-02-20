#pragma once
#include"GAME_OBJECT.h"
#include"COLOR.h"
class FADE :
    public GAME_OBJECT {
public:
    struct DATA {
        COLOR color;
        COLOR bcolor;
        COLOR wcolor;
        float speed = 0;
    };
private:
    DATA Fade;
    enum class STATE {
        IN_TRIGGER, IN_NOW, IN_END, 
        OUT_TRIGGER, OUT_NOW, OUT_END,
    };
    enum class HALFBSTATE {
       BLF_IN_TRIGGER, BLF_IN_NOW, BLF_IN_END,
        BLF_OUT_TRIGGER, BLF_OUT_NOW, BLF_OUT_END
    };
    enum class HALFWSTATE {
        WHF_IN_TRIGGER, WHF_IN_NOW, WHF_IN_END,
        WHF_OUT_TRIGGER, WHF_OUT_NOW, WHF_OUT_END,
    };

    STATE State = STATE::OUT_END;
    HALFBSTATE HalfBState = HALFBSTATE::BLF_OUT_END;
    HALFWSTATE HalfWState = HALFWSTATE::WHF_OUT_END;
public:
    FADE(class GAME* game) : GAME_OBJECT(game) {}
    void create();
    void inTrigger();
    void outTrigger();
    void whiteInTrigger();
    void whiteOutTrigger();
    void blackInTrigger();
    void blackOutTrigger();
    void draw();
    void halfBdraw();
    void halfWdraw();
    int blackOutEndFlag();
    int blackInEndFlag();
    int whiteOutEndFlag();
    int whiteInEndFlag();
    //int nextEndFlag();
    int inEndFlag();
    int outEndFlag();
    void setSpeed( float speed );
    void setColor(const COLOR& color);
};