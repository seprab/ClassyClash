#include "BaseCharacter.h"
#include "raymath.h"

BaseCharacter::BaseCharacter()
{

}
BaseCharacter::~BaseCharacter()
{

}
void BaseCharacter::UndoMovement()
{
    worldPos = worldPosLastFrame;
}
Rectangle BaseCharacter::GetCollisionRec()
{
    return Rectangle{
        GetScreenPos().x,
        GetScreenPos().y,
        width * scale,
        height * scale
    };
}
void BaseCharacter::Tick(float deltaTime)
{
    worldPosLastFrame = worldPos;

    if (Vector2Length(velocity) != 0.0)
    {
        worldPos = Vector2Add(worldPos, Vector2Scale(Vector2Normalize(velocity), speed));
        velocity.x < 0.f ? rightLeft = -1.f : rightLeft = 1.f;
        texture = textureRun;
    }
    else
    {
        texture = textureIdle;
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
        GetScreenPos().x,
        GetScreenPos().y,
        width * scale,
        height * scale};
    DrawTexturePro(texture, souce, destination, Vector2{}, 0.0f, WHITE);
    velocity = {};
}
