#include "raylib.h"
#include "BaseCharacter.h"
#include "Character.h"

class Enemy : public BaseCharacter
{
public:
    Enemy(Vector2 pos, Texture2D idleTexture, Texture2D runTexture);
    ~Enemy();
    virtual void Tick(float delaTime) override;
    void SetTarget(Character* characterRef) { target = characterRef;}
    virtual Vector2 GetScreenPos() override;


private:
    Character* target;
    float damagePerSecond {10.f};
    float radiusToStop {25.f};
};