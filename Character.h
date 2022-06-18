#ifndef CHARACTER_H
#define CHARACTER_H
#include "raylib.h"
#include "BaseCharacter.h"

class Character : public BaseCharacter
{
public:
    Character(float winWidth, float winHeight);
    ~Character();
    void SetScreenPos(float winWidth, float winHeight);
    virtual void Tick(float delaTime) override;
    virtual Vector2 GetScreenPos() override;

private:
    float windowWidth {};
    float windowHeight {};
    Texture2D sword {LoadTexture("Resources/characters/weapon_sword.png")};
    Rectangle swordCollisionRec {};
};
#endif