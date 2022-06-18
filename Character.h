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
    Rectangle GetSwordCollisionRec() {return swordCollisionRec;}
    float GetHealth() const {return health;}
    void TakeDamage(float damage); 
private:
    float windowWidth {};
    float windowHeight {};
    Texture2D sword {LoadTexture("Resources/characters/weapon_sword.png")};
    Rectangle swordCollisionRec {};
    float health {100.f};
};
#endif