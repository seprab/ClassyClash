#include "Character.h"
#include "raymath.h"


Character::Character(float winWidth, float winHeight) :
windowWidth {winWidth}, windowHeight {winHeight}
{
    textureIdle = LoadTexture("Resources/characters/knight_idle_spritesheet.png");
    textureRun = LoadTexture("Resources/characters/knight_run_spritesheet.png");
    texture = textureIdle;

    width = textureIdle.width / maxFrames;
    height = textureIdle.height;
}
Character::~Character()
{
    UnloadTexture(textureIdle);
    UnloadTexture(textureRun);
}
void Character::Tick(float deltaTime)
{   
    
    if (IsKeyDown(KEY_A))
        velocity.x -= 1.0;
    if (IsKeyDown(KEY_D))
        velocity.x += 1.0;
    if (IsKeyDown(KEY_W))
        velocity.y -= 1.0;
    if (IsKeyDown(KEY_S))
        velocity.y += 1.0;   

    BaseCharacter::Tick(deltaTime);

    Vector2 origin{};
    Vector2 offset{};
    float rotation{};
    if (rightLeft > 0.f)
    {
        origin = {0.f, sword.height * scale};
        offset = {35.f, 55.f};
        swordCollisionRec = {
            GetScreenPos().x + offset.x,
            GetScreenPos().y + offset.y - sword.height * scale,
            sword.width * scale,
            sword.height * scale
        };
        rotation = 35.f;
    }
    else
    {
        origin = {sword.width * scale, sword.height * scale};
        offset = {25.f, 55.f};
        swordCollisionRec = {
            GetScreenPos().x + offset.x - sword.width * scale,
            GetScreenPos().y + offset.y - sword.height * scale,
            sword.width * scale,
            sword.height * scale
        };
        rotation = -35.f;
    }
    Rectangle swordSource = {0.f,0.f, static_cast<float>(sword.width)* rightLeft, static_cast<float>(sword.height)};
    Rectangle swordDest{GetScreenPos().x + offset.x, GetScreenPos().y + offset.y, sword.width * scale, sword.height * scale};
    DrawTexturePro(sword, swordSource, swordDest, origin, rotation, WHITE);

    DrawRectangleLines(
        swordCollisionRec.x,
        swordCollisionRec.y,
        swordCollisionRec.width,
        swordCollisionRec.height,
        RED
    );

}
Vector2 Character::GetScreenPos()
{
    return {
        (windowWidth / 2.0f) - (scale * (0.5f * width)),
        (windowHeight / 2.0f) - (scale * (0.5f * height))};
}