#include "Character.h"
#include "raymath.h"

void Character::SetScreenPos(float winWidth, float winHeight)
{
    screenPos = {
        (winWidth / 2.0f) - (4.0f * (0.5f * width)),
        (winHeight / 2.0f) - (4.0f * (0.5f * height))};
}
void Character::tick(float deltaTime)
{
    Vector2 direction{0.0, 0.0};
    if (IsKeyDown(KEY_A))
        direction.x -= 1.0;
    if (IsKeyDown(KEY_D))
        direction.x += 1.0;
    if (IsKeyDown(KEY_W))
        direction.y -= 1.0;
    if (IsKeyDown(KEY_S))
        direction.y += 1.0;

    float directionMagnitude = Vector2Length(direction);
    if (directionMagnitude != 0.0)
    {
        direction = Vector2Scale(Vector2Normalize(direction), speed);
        worldPos = Vector2Add(worldPos, direction);
        rightLeft = direction.x < 0 ? -1.f : 1.f;
    }

    runningTime += deltaTime;
    if (runningTime > updateTime)
    {
        frame++;
        runningTime = 0;
        if (frame > maxFrames)
            frame = 0;
    }
    Rectangle souce{
        frame * rightLeft * width,
        0.0f,
        rightLeft * width,
        height};
    Rectangle destination{
        screenPos.x,
        screenPos.y,
        width * 4.0f,
        height * 4.0f};
    DrawTexturePro(directionMagnitude ? textureRun : textureIdle, souce, destination, Vector2{}, 0.0f, WHITE);
}
Character::Character()
{
    width = textureIdle.width / maxFrames;
    height = textureIdle.height;
}
Character::~Character()
{
    UnloadTexture(textureIdle);
    UnloadTexture(textureRun);
}
