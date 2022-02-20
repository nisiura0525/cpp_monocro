#include"framework.h"
#include"graphic.h"
#include"window.h"
#include"CONTAINER.h"
#include"BLACK_WORLD.h"
#include"WHITE_WORLD.h"
#include"TITLE.h"
#include"STAGE.h"
#include"BLACK_STAGE.h"
#include"WHITE_STAGE.h"
#include"STORY.h"
#include"FADE.h"
#include"GAME.h"
GAME::GAME() {
    Container = new CONTAINER();
    Title = new TITLE(this);
    Stage = new STAGE(this);
    BlackStage = new BLACK_STAGE(this);
    WhiteStage = new WHITE_STAGE(this);
    Story = new STORY(this);
    Fade = new FADE(this);
    BlackWorld = new BLACK_WORLD(this);
    WhiteWorld = new WHITE_WORLD(this);
    CharacterManager = new CHARACTER_MANAGER(this);
}
GAME::~GAME() {
    delete BlackStage;
    delete WhiteStage;
    delete CharacterManager;
    delete BlackWorld;
    delete WhiteWorld;
    delete Fade;
    delete Stage;
    delete Title;
    delete Story;
    delete Container;
}
void GAME::run() {
    window(1600, 900, full);
    hideCursor();
    
    Container->load();
    
    Title->create();
    Stage->create();
    BlackStage->create();
    WhiteStage->create();
    Story->create();
    Fade->create();
    CharacterManager->create();
    BlackWorld->create();
    WhiteWorld->create();
    
    CurScene = Title;
    CurScene->init();
    initDeltaTime();
    while (notQuit) {
        setDeltaTime();
        CurScene->proc();
    }
}
void GAME::setCurScene(SCENE* scene) { 
    CurScene = scene;
    CurScene->init();
}