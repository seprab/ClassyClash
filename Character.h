#include "raylib.h"

class Character
{
public:
    Character(float winWidth, float winHeight);
    ~Character();
    Vector2 GetworldPos() { return worldPos; }
    void SetScreenPos(float winWidth, float winHeight);
    void tick(float deltaTime);
    void UndoMovement();
    Rectangle GetCollisionRec();

private:
    Texture2D textureIdle{LoadTexture("Resources/characters/knight_idle_spritesheet.png")};
    Texture2D textureRun{LoadTexture("Resources/characters/knight_run_spritesheet.png")};

    Vector2 screenPos{};
    Vector2 worldPos{};
    Vector2 worldPosLastFrame{};

    int frame{};
    int rightLeft{1};
    float runningTime{};
    float speed{4.f};
    float scale{4.f};
    float width{};
    float height{};
    int maxFrames{6};
    float updateTime{1.f / 12.f}; // Update the knightIdle 12 times per frame
};