#ifndef BASE_CHARACTER_H
#define BASE_CHARACTER_H

#include "raylib.h"

class BaseCharacter
{
public:
    BaseCharacter();
    ~BaseCharacter();
    Vector2 GetworldPos() { return worldPos; }
    Rectangle GetCollisionRec();
    void UndoMovement();
    virtual void Tick(float deltaTime);
    virtual Vector2 GetScreenPos() = 0;
    bool GetAlive() {return alive;}
    void SetAlive(bool _alive) {alive = _alive;}

protected:
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
    float updateTime{1.f / 12.f};
    Vector2 velocity{};

    Texture2D textureIdle{};
    Texture2D textureRun{};
    Texture2D texture{};
private:
    bool alive {true};
};
#endif