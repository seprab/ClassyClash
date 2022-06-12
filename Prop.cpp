#include "Prop.h"
#include "raymath.h"

Prop::Prop(Texture2D tex, Vector2 pos) :
texture(tex), worldPos(pos)
{
}
Prop::~Prop()
{
    UnloadTexture(texture);
}
Rectangle Prop::GetCollisionRec(Vector2 playerPos)
{
    Vector2 screenPos = Vector2Add(Vector2Scale(playerPos, -1.f), worldPos);
    return Rectangle{
        screenPos.x,
        screenPos.y,
        texture.width * scale,
        texture.height * scale
    };
}
void Prop::Render(Vector2 playerPos)
{
    Vector2 screenPos = Vector2Add(Vector2Scale(playerPos, -1.f), worldPos);
    DrawTextureEx(texture, screenPos, 0.f, scale, WHITE);
}
