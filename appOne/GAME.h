#pragma once
class GAME {
//コンテナ
private:
    class CONTAINER* Container = nullptr;
public:
    class CONTAINER* container() { return Container; };
//シーン
private:
    class TITLE* Title = nullptr;
    class STAGE* Stage = nullptr;
    class BLACK_STAGE* BlackStage = nullptr;
    class WHITE_STAGE* WhiteStage = nullptr;
    class STORY* Story = nullptr;
    class SCENE* CurScene = nullptr;
    class FADE* Fade = nullptr;
public:
    class TITLE* title() { 
        return Title; 
    }
    class STAGE* stage() { return Stage; }
    class BLACK_STAGE* blackStage() { return BlackStage; }
    class WHITE_STAGE* whiteStage() { return WhiteStage; }
    class STORY* story() { return Story; }
    class FADE* fade() { return Fade; }
private:
    class MAP* BlackWorld = nullptr;
    class MAP* WhiteWorld = nullptr;
    class CHARACTER_MANAGER* CharacterManager = nullptr;
public:
    class MAP* blackWorld() { return BlackWorld; }
    class MAP* whiteWorld() { return WhiteWorld; }
    class CHARACTER_MANAGER* characterManager() { return CharacterManager; }
public:
    GAME();
    ~GAME();
    void run();
    void setCurScene(SCENE* scene);
};