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
    if(!GetAlive()) return;
    velocity = Vector2Subtract(target->GetScreenPos(), GetScreenPos());
    if(Vector2Length(velocity)<radiusToStop) velocity={};
    BaseCharacter::Tick(deltaTime);
    if (CheckCollisionRecs(target->GetCollisionRec(), GetCollisionRec()))
    {
        target->TakeDamage(damagePerSecond * deltaTime);
    }
}
Vector2 Enemy::GetScreenPos()
{
    return Vector2Subtract(worldPos, target->GetworldPos());
}