#include "raylib.h"

class Prop
{
public:
    Prop(Texture2D tex, Vector2 pos);
    ~Prop();
    void Render(Vector2 playerPos);
    Rectangle GetCollisionRec(Vector2 playerPos);
    
private:
    Texture2D texture{};
    Vector2 worldPos{};
    float scale{4.f};
};