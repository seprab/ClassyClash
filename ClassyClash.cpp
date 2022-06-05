#include "raylib.h"
#include "raymath.h"
#include "external/glfw/include/GLFW/glfw3.h"
#include "Character.h"

static const Vector2 windowDimensions{384, 384};
static const char *window_title = "Classy Clasher";
static const Color backgroundColor = BLACK;

int main()
{
    InitWindow(windowDimensions.x, windowDimensions.y, window_title);
    SetTargetFPS(60);

    Texture2D map = LoadTexture("Resources/nature_tileset/WorldMap.png");
    Vector2 mapPos{0.0f, 0.0f};
    Character player;

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(backgroundColor);
        player.SetScreenPos(windowDimensions.x ,windowDimensions.y);
        mapPos = Vector2Scale(player.GetworldPos(), -1.f);
        DrawTextureEx(map, mapPos, 0.0f, 4.0f, WHITE);
        player.tick(GetFrameTime());
        EndDrawing();
        glFinish();
    }
    UnloadTexture(map);
    player.~Character();
    CloseWindow();
    return 0;
}