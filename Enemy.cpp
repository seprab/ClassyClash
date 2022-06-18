#include "raylib.h"
#include "Enemy.h"
#include "raymath.h"
#include "Character.h"

Enemy::Enemy(Vector2 pos, Texture2D idleTexture, Texture2D runTexture)
{
    textureIdle = idleTexture;
    textureRun = runTexture;
    texture = textureIdle;
    worldPos = pos;
    width = textureIdle.width / maxFrames;
    height = textureIdle.height;
    speed = 2.5f;
}
Enemy::~Enemy()
{

}
void Enemy::Tick(float deltaTime)
{
    velocity = Vector2Subtract(target->GetScreenPos(), GetScreenPos());
    BaseCharacter::Tick(deltaTime);
}
Vector2 Enemy::GetScreenPos()
{
    return Vector2Subtract(worldPos, target->GetworldPos());
}